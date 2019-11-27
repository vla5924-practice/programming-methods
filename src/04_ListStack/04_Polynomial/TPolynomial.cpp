#include "TPolynomial.h"

TMonomialList::iterator TPolynomial::findPrevOrderedDegree(unsigned degree) const
{
    TMonomialList::iterator temp = monomials->begin();
    for (TMonomialList::iterator i = monomials->begin(); i != monomials->end(); i++)
    {
        temp = i;
        TMonomialList::iterator j = getNextIterator(temp);
        if ((*j).key < degree)
            return temp;
    }
    return temp;
}

TMonomialList::iterator TPolynomial::getNextIterator(TMonomialList::iterator iterator) const
{
    return iterator++;
}

void TPolynomial::add(double coefficient, unsigned degree)
{
    double* pCoef = new double(coefficient);
    TMonomialList::iterator prevOrdered = findPrevOrderedDegree(degree);
    if (prevOrdered != monomials->end())
        monomials->insertAfter(prevOrdered, degree, pCoef);
    else
        monomials->insertToStart(degree, pCoef);
    delete pCoef;
}

void TPolynomial::add(double* pCoef, unsigned degree)
{
    TMonomialList::iterator prevOrdered = findPrevOrderedDegree(degree);
    if (prevOrdered != monomials->end())
        monomials->insertAfter(prevOrdered, degree, pCoef);
    else
        monomials->insertToStart(degree, pCoef);
}

void TPolynomial::removeNulls()
{
    for (TMonomialList::iterator i = monomials->begin(); i != monomials->end(); i++)
        if (*(*i).pData == 0.)
            monomials->remove(i);
}

void TPolynomial::reduce()
{
    for (TMonomialList::iterator i = monomials->begin(); i != monomials->end(); i++)
    {
        TMonomialP control = *i;
        for (TMonomialList::iterator j = getNextIterator(i); j != monomials->end(); j++)
        {
            TMonomialP monomial = *j;
            if (monomial.key == control.key)
            {
                *control.pData += *monomial.pData;
                monomials->remove(j);
            }
        }
    }
}

void TPolynomial::nullify()
{
    monomials->removeAll();
}

void TPolynomial::parse(const char* const expression)
{
    std::string str = expression;
    str = str.substr(str.find_first_not_of(' '));
    if (str.find_first_not_of("0123456789+-*xyz^. \t\n") < str.size())
        throw SyntaxError();
    bool isEnded = false;
    do
    {
        size_t delta = 0U;
        size_t offset = str.find_first_of(FLOAT_NUM_SYMBOLS);
        size_t offset2 = str.find_first_of("+-", offset + 1);
        size_t offset3 = str.find_first_of("xyz");
        bool hasCoef = true;
        if (offset3 < offset)
        {
            offset = offset3;
            offset2 = str.find_first_of("+-", offset);
            hasCoef = false;
        }
        std::string strMonom;
        if (offset2 >= str.size())
            strMonom = str;
        else
            strMonom = str.substr(0, offset2);
        if (hasCoef && (strMonom[offset + 1] == ' '))
        {
            char symbol = strMonom[offset];
            delta = strMonom.find_first_not_of(' ', offset + 1) - 1;
            strMonom = strMonom.substr(delta + 1);
            strMonom = symbol + strMonom;
        }
        std::string strCoef = hasCoef ? getFirstFloatNumber(strMonom.c_str(), offset) : "1";
        //offset2 = strMonom.find_first_of("xyz");
        //if (offset >= offset2)
        //    strCoef = "1";
        std::string remain = hasCoef ? strMonom.substr(strCoef.size() + offset) : strMonom;
        size_t remainFirstNums = remain.find_first_of("0123456789");
        if (remainFirstNums < remain.find_first_of("xyz"))
            throw SyntaxError(); // like -123 45*x^2*...
        size_t remainVars;
        unsigned degree = 0U;
        while ((remainVars = remain.find_first_of("xyz")) < remain.size())
        {
            std::string strVarArea = remain.substr(remainVars, remain.find_first_of("xyz", remainVars + 1U));
            unsigned factor;
            unsigned addingDegree = getDegreeMask(strVarArea.c_str(), factor);
            unsigned currentDegree = factor == 1U ? DEGZ(degree) : factor == 10U ? DEGY(degree) : DEGX(degree);
            if (currentDegree + addingDegree > 9U)
                throw SyntaxError();
            degree += addingDegree * factor;
            remain = remain.substr(remainVars + strVarArea.size());
        }
        double coefficient = std::stod(strCoef);
        add(coefficient, degree);
        str = str.substr(strMonom.size() + delta);
        if(str.size() > 0)
            str = str.substr(str.find_first_not_of(' '));
    } while (str.size() > 0);
}

const std::string TPolynomial::monomToStr(const TMonomial& monomial) const
{
    std::string str;
    if (*monomial.pData == 0)
        return std::string("0");
    if (*monomial.pData != 1)
        str += std::to_string(*monomial.pData);
    if (monomial.key > 0U)
    {
        if (DEGX(monomial.key) > 0)
            str += "*x";
        if (DEGX(monomial.key) > 1)
        {
            str += '^';
            str += std::to_string(DEGX(monomial.key));
        }
        if (DEGY(monomial.key) > 0)
            str += "*y";
        if (DEGY(monomial.key) > 1)
        {
            str += '^';
            str += std::to_string(DEGY(monomial.key));
        }
        if (DEGZ(monomial.key) > 0)
            str += "*z";
        if (DEGZ(monomial.key) > 1)
        {
            str += '^';
            str += std::to_string(DEGZ(monomial.key));
        }
    }
    return str;
}

const std::string TPolynomial::getFirstFloatNumber(const char* const expression, size_t& offset) const
{
    std::string str = expression;
    offset = str.find_first_of(FLOAT_NUM_SYMBOLS);
    return str.substr(offset, str.find_first_not_of(FLOAT_NUM_SYMBOLS, offset));
}

const std::string TPolynomial::getFirstUIntNumber(const char* const expression, size_t& offset) const
{
    std::string str = expression;
    offset = str.find_first_of(UINT_NUM_SYMBOLS);
    size_t count = str.find_first_not_of(UINT_NUM_SYMBOLS, offset);
    if(count < str.size())
        return str.substr(offset, count);
    else
        return str.substr(offset);
}

unsigned TPolynomial::getDegreeMask(const char* const expression, unsigned& factor) const
{
    std::string str = expression;
    if (str.find_first_of("+-.") < str.size())
        return 1000U;
    size_t varsFound = str.find_first_of("xyz");
    size_t numsFound = str.find_first_of("0123456789");
    if ((numsFound < varsFound) || (varsFound >= str.size()))
        return 1000U;
    factor = 1U;
    if (str[varsFound] == 'x')
        factor = 100U;
    else if (str[varsFound] == 'y')
        factor = 10U;
    if (numsFound >= str.size())
        return 1U;
    size_t offset;
    unsigned degree = static_cast<unsigned>(std::stoul(getFirstUIntNumber(expression, offset)));
    return degree;
}

TPolynomial::TPolynomial()
{
    monomials = new TMonomialList;
}

TPolynomial::TPolynomial(const char* const expression) : TPolynomial()
{
    parse(expression);
}

TPolynomial::TPolynomial(const TMonomial& monomial) : TPolynomial()
{
    if (!Monomial::checkDegrees(monomial.key))
        throw Monomial::DegreeOverflow();
    monomials->insertToStart(monomial.key, monomial.pData);
}

TPolynomial::TPolynomial(const TPolynomial& other)
{
    monomials = new TMonomialList(*other.monomials);
}

TPolynomial::TPolynomial(const TMonomialList& list)
{
    for (TMonomialList::iterator i = list.begin(); i != list.end(); i++)
        if (!Monomial::checkDegrees((*i).key))
            throw Monomial::DegreeOverflow();
    monomials = new TMonomialList(list);
}

TPolynomial::~TPolynomial()
{
    delete monomials;
}

TPolynomial& TPolynomial::operator=(const TPolynomial& other)
{
    delete monomials;
    monomials = new TMonomialList(*other.monomials);
    return *this;
}

TPolynomial TPolynomial::operator+(const TPolynomial& other)
{
    TPolynomial result(*this);
    for (TMonomialList::iterator i = result.monomials->begin(); i != result.monomials->end(); i++)
    {
        TMonomialP current = *i;
        TMonomialP monomial = other.monomials->find(current.key);
        if (monomial)
            *current.pData += *monomial.pData;
        else
            result.add(*current.pData, current.key);
    }
    result.removeNulls();
    return result;
}

TPolynomial TPolynomial::operator+(const TMonomial& monomial)
{
    TPolynomial result(*this);
    TMonomialP needle = result.monomials->find(monomial.key);
    if (needle)
        *needle.pData += *monomial.pData;
    else
        result.add(monomial.pData, monomial.key);
    result.removeNulls();
    return result;
}

TPolynomial TPolynomial::operator+(const TMonomialP& monomial)
{
    return *this + Monomial::make(*monomial.pData, monomial.key);
}

TPolynomial TPolynomial::operator+(double number)
{
    return *this + Monomial::make(number, 0U);
}

TPolynomial TPolynomial::operator-(const TPolynomial& other)
{
    TPolynomial result(*this);
    for (TMonomialList::iterator i = result.monomials->begin(); i != result.monomials->end(); i++)
    {
        TMonomialP current = *i;
        TMonomialP monomial = other.monomials->find(current.key);
        if (monomial)
            *current.pData -= *monomial.pData;
        else
            result.add(*current.pData, current.key);
    }
    result.removeNulls();
    return result;
}

TPolynomial TPolynomial::operator-(const TMonomial& monomial)
{
    TPolynomial result(*this);
    TMonomialP needle = result.monomials->find(monomial.key);
    if (needle)
        *needle.pData -= *monomial.pData;
    else
        result.add(monomial.pData, monomial.key);
    result.removeNulls();
    return result;
}

TPolynomial TPolynomial::operator-(const TMonomialP& monomial)
{
    return *this - Monomial::make(*monomial.pData, monomial.key);
}

TPolynomial TPolynomial::operator-(double number)
{
    return *this - Monomial::make(number, 0U);
}

TPolynomial TPolynomial::operator*(const TPolynomial& other)
{
    TPolynomial result;
    for (TMonomialList::iterator i = monomials->begin(); i != monomials->end(); i++)
    {
        TMonomialP lhs = *i;
        for (TMonomialList::iterator j = other.monomials->begin(); j != other.monomials->end(); j++)
        {
            TMonomialP rhs = *j;
            unsigned x = DEGX(lhs.key) + DEGX(rhs.key);
            unsigned y = DEGY(lhs.key) + DEGY(rhs.key);
            unsigned z = DEGZ(lhs.key) + DEGZ(rhs.key);
            if (!Monomial::checkDegrees(x, y, z))
                throw Monomial::DegreeOverflow();
            unsigned degree = Monomial::rollUp(x, y, z);
            double coefficient = (*lhs.pData) * (*rhs.pData);
            result.add(coefficient, degree);
        }
    }
    result.reduce();
    result.removeNulls();
    return result;
}

TPolynomial TPolynomial::operator*(const TMonomial& monomial)
{
    TPolynomial result(*this);
    for (TMonomialList::iterator i = monomials->begin(); i != monomials->end(); i++)
    {
        TMonomialP current = *i;
        unsigned x = DEGX(current.key) + DEGX(monomial.key);
        unsigned y = DEGY(current.key) + DEGY(monomial.key);
        unsigned z = DEGZ(current.key) + DEGZ(monomial.key);
        if (!Monomial::checkDegrees(x, y, z))
            throw Monomial::DegreeOverflow();
        unsigned degree = Monomial::rollUp(x, y, z);
        double coefficient = (*current.pData) * (*monomial.pData);
        result.add(coefficient, degree);
    }
    result.removeNulls();
    return result;
}

TPolynomial TPolynomial::operator*(const TMonomialP& monomial)
{
    return *this * Monomial::make(*monomial.pData, monomial.key);
}

TPolynomial TPolynomial::operator*(double number)
{
    TPolynomial result(*this);
    for (TMonomialList::iterator i = result.monomials->begin(); i != result.monomials->end(); i++)
    {
        TMonomialP current = *i;
        *current.pData *= number;
    }
    return result;
}

std::ostream& operator<<(std::ostream& stream, const TPolynomial& polynomial)
{
    if (polynomial.monomials->empty())
        return stream;
    TMonomialList::iterator i = polynomial.monomials->begin();
    stream << polynomial.monomToStr(Monomial::make(*(*i).pData, (*i).key));
    for (i++; i != polynomial.monomials->end(); i++)
    {
        if ((*(*i).pData >= 0))
            stream << " + ";
        else
            stream << " - ";
        stream << polynomial.monomToStr(Monomial::make(fabs(*(*i).pData), (*i).key));
    }
    return stream;
}

std::istream& operator>>(std::istream& stream, TPolynomial& polynomial)
{
    std::string str;
    std::getline(stream, str, '\n');
    polynomial.parse(str.c_str());
    return stream;
}

TPolynomial operator""_poly(const char* literal, size_t)
{
    return TPolynomial(literal);
}

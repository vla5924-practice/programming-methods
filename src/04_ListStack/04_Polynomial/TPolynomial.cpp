#include "TPolynomial.h"

TMonomialList::iterator TPolynomial::findPrevOrderedDegree(unsigned degree) const
{
    if (!monomials->empty())
    {
        TMonomial* first = *(monomials->begin());
        if (degree >= first->key)
            return monomials->end();
    }
    TMonomialList::iterator temp = monomials->begin();
    for (TMonomialList::iterator i = monomials->begin(); getNextIterator(i) != monomials->end(); i++)
    {
        temp = i;
        TMonomialList::iterator next = getNextIterator(temp);
        if ((*next)->key <= degree)
            return temp;
    }
    return temp;
}

TMonomialList::iterator TPolynomial::getNextIterator(TMonomialList::iterator iterator) const
{
    return ++iterator;
}

void TPolynomial::add(double coefficient, unsigned degree)
{
    TMonomialList::iterator prevOrdered = findPrevOrderedDegree(degree);
    if (prevOrdered != monomials->end())
        monomials->insertAfter(prevOrdered, degree, coefficient);
    else
        monomials->insertToStart(degree, coefficient);
}

void TPolynomial::addNonzero(TMonomial* primary, const TMonomial* secondary)
{
	if (primary)
	{
        if(secondary)
		    *primary = *primary + *secondary;
		if (primary->data == 0)
			monomials->remove(primary->key);
		return;
	}
	if (secondary && (secondary->data != 0))
		add(secondary->data, secondary->key);
}

void TPolynomial::reduce()
{
    for (TMonomialList::iterator i = monomials->begin(); i != monomials->end(); i++)
    {
        TMonomial* control = *i;
        if (control->data == 0)
        {
            monomials->remove(i);
            continue;
        }
        for (TMonomialList::iterator j = getNextIterator(i); j != monomials->end(); j++)
        {
            TMonomial* monomial = *j;
            if (monomial->key == control->key)
            {
                control->data += monomial->data;
                monomials->remove(j);
            }
        }
    }
}

void TPolynomial::sort()
{
    TPolynomial result;
    if (monomials->empty() || monomials->begin()++ == monomials->end())
        return;
    size_t msize = monomials->size();
    for (size_t n = 1; n <= msize; n++)
    {
        TMonomial* maximal = *(monomials->begin());
        for (TMonomialList::iterator i = monomials->begin()++; i != monomials->end(); i++)
        {
            TMonomial* current = *i;
            if (current->key > maximal->key)
                maximal = current;
        }
        monomials->remove(maximal->key);
        monomials->insertToEnd(maximal->key, maximal->data);
    }
    *monomials = *result.monomials;
}

void TPolynomial::nullify()
{
    monomials->removeAll();
}

void TPolynomial::parse(const char* const expression)
{
    std::string rawStr = expression;
    rawStr = rawStr.substr(rawStr.find_first_not_of(' '));
    if (rawStr.find_first_not_of("0123456789+-*xyz^. \t\n") < rawStr.size())
        throw SyntaxError();
    std::string str;
    for (char symbol : rawStr)
        if (symbol != ' ')
            str += symbol;
    rawStr.clear();
    do
    {
        size_t delta = 0U;
        size_t offset = str.find_first_of("0123456789.+-");
        size_t offset2 = str.find_first_of("+-", offset + 1);
        size_t offset3 = str.find_first_of("xyz");
        if ((offset >= str.size()) && (offset3 >= str.size()))
            throw SyntaxError();
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
        std::string strCoef;
        size_t strCoefSize = 0ULL;
        if (hasCoef)
        {
            strCoef = getFirstFloatNumber(strMonom.c_str(), offset);
            strCoefSize = strCoef.size();
            if (strCoef == "-")
            {
                strCoefSize = 1ULL;
                strCoef = "-1";
            }
            else if (strCoef == "+")
            {
                strCoefSize = 1ULL;
                strCoef = "1";
            }
        }
        else
        {
            strCoef = "1";
        }
        std::string remain = hasCoef ? strMonom.substr(strCoefSize + offset) : strMonom;
        size_t remainFirstNums = remain.find_first_of("0123456789");
        if (remainFirstNums < remain.find_first_of("xyz"))
            throw SyntaxError(); // like -123 45*x^2*...
        size_t remainVars;
        unsigned degree = 0U;
        while ((remainVars = remain.find_first_of("xyz")) < remain.size())
        {
            size_t remainVarsNext = remain.find_first_of("xyz", remainVars + 1U) - 1U;
            std::string strVarArea = remain.substr(remainVars, remainVarsNext > 0ULL ? remainVarsNext : 1ULL);
            unsigned factor;
            unsigned addingDegree = getDegreeMask(strVarArea.c_str(), factor);
            unsigned currentDegree = factor == 1U ? DEGZ(degree) : factor == 10U ? DEGY(degree) : DEGX(degree);
            if (currentDegree + addingDegree > 9U)
                throw SyntaxError();
            degree += addingDegree * factor;
            remain = remain.substr(remainVars + strVarArea.size());
        }
        double coefficient = 0.;
        try
        {
            coefficient = std::stod(strCoef);
        }
        catch (...)
        {
            throw SyntaxError();
        }
        add(coefficient, degree);
        str = str.substr(strMonom.size() + delta);
        if(str.size() > 0)
            str = str.substr(str.find_first_not_of(' '));
    } while (str.size() > 0);
    reduce();
}

const std::string TPolynomial::monomToStr(const TMonomial& monomial) const
{
    constexpr double EPSILON = 1e-4;
    std::string str;
    if (monomial.data == 0)
        return std::string("0");
    if (fabs(monomial.data - (int)monomial.data) < EPSILON)
        str += std::to_string((int)monomial.data);
    else
        str += std::to_string(monomial.data);
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
    offset = str.find_first_of("0123456789.+-");
    return str.substr(offset, str.find_first_not_of("0123456789.+-", offset));
}

const std::string TPolynomial::getFirstUIntNumber(const char* const expression, size_t& offset) const
{
    std::string str = expression;
    offset = str.find_first_of("0123456789+");
    size_t count = str.find_first_not_of("0123456789+", offset);
    if(count < str.size())
        return str.substr(offset, count);
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
    monomials->insertToStart(monomial.key, monomial.data);
}

TPolynomial::TPolynomial(double number)
    : TPolynomial(TMonomial(number, 0U))
{
}

TPolynomial::TPolynomial(const TPolynomial& other)
{
    monomials = new TMonomialList(*other.monomials);
}

TPolynomial::TPolynomial(const TMonomialList& list)
{
    monomials = new TMonomialList(list);
    sort();
    reduce();
}

TPolynomial::~TPolynomial()
{
    delete monomials;
}

TPolynomial& TPolynomial::operator=(const TPolynomial& other)
{
    if (this == &other)
        return *this;
    delete monomials;
    monomials = new TMonomialList(*other.monomials);
    return *this;
}

TPolynomial TPolynomial::operator+(const TPolynomial& other)
{
    TPolynomial result(*this);
    for (TMonomialList::iterator i = other.monomials->begin(); i != other.monomials->end(); i++)
    {
        TMonomial* current = *i;
        TMonomial* monomial = result.monomials->find(current->key);
		result.addNonzero(monomial, current);
    }
    return result;
}

TPolynomial TPolynomial::operator+(const TMonomial& monomial)
{
    TPolynomial result(*this);
    TMonomial* needle = result.monomials->find(monomial.key);
	result.addNonzero(needle, &monomial);
    return result;
}

TPolynomial TPolynomial::operator+(double number)
{
    if (number == 0.)
        return *this;
    return *this + TMonomial(number, 0U);
}

TPolynomial TPolynomial::operator-(const TPolynomial& other)
{
    TPolynomial result(*this);
    for (TMonomialList::iterator i = other.monomials->begin(); i != other.monomials->end(); i++)
    {
        TMonomial* current = *i;
        TMonomial* monomial = result.monomials->find(current->key);
		result.addNonzero(monomial, &-*current);
    }
    return result;
}

TPolynomial TPolynomial::operator-(const TMonomial& monomial)
{
    TPolynomial result(*this);
    TMonomial* needle = result.monomials->find(monomial.key);
	result.addNonzero(needle, &-monomial);
    return result;
}

TPolynomial TPolynomial::operator-(double number)
{
    if (number == 0.)
        return *this;
    return *this - TMonomial(number, 0U);
}

TPolynomial TPolynomial::operator*(const TPolynomial& other)
{
    TPolynomial result;
    for (TMonomialList::iterator i = monomials->begin(); i != monomials->end(); i++)
    {
        for (TMonomialList::iterator j = other.monomials->begin(); j != other.monomials->end(); j++)
        {
            TMonomial* lhs = *i;
            TMonomial* rhs = *j;
            TMonomial monomial = *lhs * (*rhs);
            if(monomial.data)
                result.add(monomial.data, monomial.key);
        }
    }
    result.reduce();
    return result;
}

TPolynomial TPolynomial::operator*(const TMonomial& monomial)
{
    TPolynomial result(*this);
    for (TMonomialList::iterator i = monomials->begin(); i != monomials->end(); i++)
    {
        TMonomial* current = *i;
        TMonomial res = *current * monomial;
        if (res.data)
            result.add(res.data, res.key);
    }
    result.reduce();
    return result;
}

TPolynomial TPolynomial::operator*(double number)
{
    if (number == 0.)
        return TPolynomial();
    TPolynomial result(*this);
    for (TMonomialList::iterator i = result.monomials->begin(); i != result.monomials->end(); i++)
    {
        TMonomial* current = *i;
        current->data *= number;
    }
    return result;
}

TPolynomial& TPolynomial::operator+=(const TPolynomial& other)
{
    *this = *this + other;
    return *this;
}

TPolynomial& TPolynomial::operator+=(const TMonomial& monomial)
{
    *this = *this + monomial;
    return *this;
}

TPolynomial& TPolynomial::operator+=(double number)
{
    *this = *this + number;
    return *this;
}

TPolynomial& TPolynomial::operator-=(const TPolynomial& other)
{
    *this = *this - other;
    return *this;
}

TPolynomial& TPolynomial::operator-=(const TMonomial& monomial)
{
    *this = *this - monomial;
    return *this;
}

TPolynomial& TPolynomial::operator-=(double number)
{
    *this = *this - number;
    return *this;
}

TPolynomial& TPolynomial::operator*=(const TPolynomial& other)
{
    *this = *this * other;
    return *this;
}

TPolynomial& TPolynomial::operator*=(const TMonomial& monomial)
{
    *this = *this * monomial;
    return *this;
}

TPolynomial& TPolynomial::operator*=(double number)
{
    *this = *this * number;
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const TPolynomial& polynomial)
{
    if (polynomial.monomials->empty())
        return stream << "0";
    TMonomialList::iterator i = polynomial.monomials->begin();
    stream << polynomial.monomToStr(TMonomial((*i)->data, (*i)->key));
    for (i++; i != polynomial.monomials->end(); i++)
    {
        TMonomial* monomial = *i;
        if (monomial->data >= 0)
            stream << " + ";
        else
            stream << " - ";
        stream << polynomial.monomToStr(TMonomial(fabs(monomial->data), monomial->key));
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

#include "PostfixFormProcessor.h"

PostfixFormProcessor::TokenType PostfixFormProcessor::checkToken(const char token)
{
	if ((token == ' ') || (token == '\n') || (token == '\t') || (token == '\b'))
		return TokenType::space;
	if (token == ')')
		return TokenType::closingBrace;
	if (((token >= 'a') && (token <= 'z')) || ((token >= 'A') && (token <= 'Z')))
		return TokenType::operand;
	if ((token == '+') || (token == '-') || (token == '*') || (token == '/') || (token == '('))
		return TokenType::operation;
	return TokenType::unknown;
}

size_t PostfixFormProcessor::countPostfixFormLength(const std::string& expression)
{
	size_t count = 0;
	for (std::string::const_iterator token = expression.begin(); token != expression.end(); token++)
	{
		TokenType type = checkToken(*token);
		if (type == TokenType::unknown)
			throw InvalidExpressionError();
		else if ((type == TokenType::operand) || ((type == TokenType::operation) && *token != '('))
			count++;
		else
			continue;
	}
	return count;
}

size_t PostfixFormProcessor::countOperations(const std::string& expression)
{
	size_t count = 0;
	for (std::string::const_iterator token = expression.begin(); token != expression.end(); token++)
	{
		TokenType type = checkToken(*token);
		if (type == TokenType::unknown)
			throw InvalidExpressionError();
		else if (type == TokenType::operation)
			count++;
		else
			continue;
	}
	return count;
}

PostfixFormProcessor::Priority PostfixFormProcessor::checkPriority(const char first, const char second)
{
	if ((checkToken(first) != TokenType::operation) || (checkToken(second) != TokenType::operation))
		return Priority::unknown;
	int numericPriorityFirst  = 0, numericPrioritySecond = 0;
	if ((first == '*') || (first == '/'))
		numericPriorityFirst = 3;
	else if ((first == '+') || (first == '-'))
		numericPriorityFirst = 2;
	else
		numericPriorityFirst = 1;
	if ((second == '*') || (second == '/'))
		numericPrioritySecond = 3;
	else if ((second == '+') || (second == '-'))
		numericPrioritySecond = 2;
	else
		numericPrioritySecond = 1;
	if (numericPriorityFirst >= numericPrioritySecond)
		return Priority::notLower;
	if (numericPriorityFirst <= numericPrioritySecond)
		return Priority::notHigher;
	return Priority::unknown;
}

PostfixFormProcessor::Variable PostfixFormProcessor::findVariableByName(const Variables variables, const char name)
{
	for (size_t i = 0; i < variables.count; i++)
	{
		const Variable& variable = variables.variables[i];
		if (variable.name == name)
			return Variable(variable);
	}
	return Variable();
}

std::string PostfixFormProcessor::findVariables(const std::string& expression)
{
	if (!checkExpression(expression))
		throw InvalidExpressionError();
	std::string variablesNames;
	for (std::string::const_iterator token = expression.begin(); token != expression.end(); token++)
	{
		TokenType type = checkToken(*token);
		if (type == TokenType::operand)
		{
			bool isFirstTime = true;
			for (std::string::const_iterator prevToken = expression.begin(); prevToken != token; prevToken++)
				if (*token == *prevToken)
					isFirstTime = false;
			if (isFirstTime)
				variablesNames += *token;
		}
	}
	return variablesNames;
}

bool PostfixFormProcessor::checkExpression(const std::string& expression)
{
	try
	{
		TokenType prev = TokenType::unknown;
		unsigned openingBracesCount = 0, closingBracesCount = 0;
		for (std::string::const_iterator token = expression.begin(); token != expression.end(); token++)
		{
			TokenType current = checkToken(*token);
			if (current == TokenType::closingBrace)
				closingBracesCount++;
			else if (*token == '(')
				openingBracesCount++;
			if((current == TokenType::operand) || (current == TokenType::operation))
				if ((current == prev) && (*token != '('))
					return false;
			prev = current;
		}
		if (closingBracesCount != openingBracesCount)
			return false;
		if (countPostfixFormLength(expression) && countOperations(expression))
			return true;
		return false;
	}
	catch (InvalidExpressionError&)
	{
		return false;
	}
	return true;
}

std::string PostfixFormProcessor::parse(const std::string& expression, bool testFinally)
{
	if(!checkExpression(expression))
		throw InvalidExpressionError();
	size_t postfixFormLength = countPostfixFormLength(expression);
	size_t operationsCount = countOperations(expression);
	TStack<char> postfixForm(postfixFormLength), operations(operationsCount);
	for (std::string::const_iterator token = expression.begin(); token != expression.end(); token++)
	{
		TokenType type = checkToken(*token);
		if (type == TokenType::space)
			continue;
		if (type == TokenType::operand)
			postfixForm.push(*token);
		else if (*token == '(')
		{
				operations.push(*token);
		}
		else if (type == TokenType::closingBrace)
		{
			while (operations.top() != '(')
			{
					operations.push(operations.top());
			}
			if (!operations.empty())
				operations.pop(); // remove '('
		}
		else if (type == TokenType::operation)
		{
			if(operations.empty() || (checkPriority(operations.top(), *token) == Priority::notHigher))
				operations.push(*token);
			else
			{
				while (!operations.empty() && (checkPriority(operations.top(), *token) == Priority::notLower))
					postfixForm.push(operations.pop());
				operations.push(*token);
			}
		}
		else
			throw InvalidExpressionError(); // something unknown
	}
	while (!operations.empty())
		postfixForm.push(operations.pop());
	std::string result;
	result.resize(postfixForm.height(), 0);
	for (std::string::reverse_iterator i = result.rbegin(); !postfixForm.empty(); i++)
		*i = postfixForm.pop();
	if(testFinally)
		if (!test(result))
			throw InvalidExpressionError();
	return result;
}

bool PostfixFormProcessor::test(const std::string& postfixForm)
{
	TStack<double> calculated(postfixForm.size());
	for (std::string::const_iterator i = postfixForm.begin(); i != postfixForm.end(); i++)
	{
		TokenType type = checkToken(*i);
		if (type == TokenType::operand)
			calculated.push(1.0);
		else if (type == TokenType::operation)
		{
			double first, second;
			try
			{
				second = calculated.pop();
				first = calculated.pop();
			}
			catch (TStack<double>::EmptyError&)
			{
				return false;
			}
			if (*i == '+')
				calculated.push(first + second);
			else if (*i == '-')
				calculated.push(first - second);
			else if (*i == '*')
				calculated.push(first * second);
			else if (*i == '/')
			{
				if (second == 0.0)
					second = 1.0;
				calculated.push(first / second);
			}
			else
				return false;
		}
		else
			return false;
	}
	try
	{
		calculated.pop();
	}
	catch (TStack<double>::EmptyError&)
	{
		return false;
	}
	return true;
}

double PostfixFormProcessor::calculate(const std::string& postfixForm, const Variables variables)
{
	TStack<double> calculated(postfixForm.size());
	for (std::string::const_iterator i = postfixForm.begin(); i != postfixForm.end(); i++)
	{
		TokenType type = checkToken(*i);
		if (type == TokenType::operand)
		{
			Variable variable = findVariableByName(variables, *i);
			if (!variable.name)
				throw UndefinedVariable();
			calculated.push(variable.value);
		}
		else if (type == TokenType::operation)
		{
			double first, second;
			try
			{
				second = calculated.pop();
				first = calculated.pop();
			}
			catch (TStack<double>::EmptyError&)
			{
				throw InvalidPostfixFormError();
			}
			if (*i == '+')
				calculated.push(first + second);
			else if (*i == '-')
				calculated.push(first - second);
			else if (*i == '*')
				calculated.push(first * second);
			else if (*i == '/')
			{
				if (second == 0.0)
					throw DivisionByZero();
				calculated.push(first / second);
			}
			else
				throw InvalidPostfixFormError();
		}
		else
			throw InvalidPostfixFormError();
	}
	double result = 0.0;
	try
	{
		result = calculated.pop();
	}
	catch(TStack<double>::EmptyError&)
	{
		throw InvalidPostfixFormError();
	}
	return result;
}
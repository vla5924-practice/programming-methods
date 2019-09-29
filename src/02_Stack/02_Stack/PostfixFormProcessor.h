#ifndef _POSTFIXFORMPROCESSOR_H_
#define _POSTFIXFORMPROCESSOR_H_

#include "TStack.h"
#include <string>

class PostfixFormProcessor
{
public:
	struct Variable
	{
		char   name  = '\0';
		double value = 0.0;
	};
	struct Variables
	{
		Variable* variables = nullptr;
		size_t    count     = 0U;
	};
private:
	enum class TokenType
	{
		unknown,
		operand,
		operation,
		closingBrace,
		space
	};
	enum class Priority
	{
		equal,
		higher,
		lower,
		unknown
	};
	static TokenType checkToken(const char token);
	static size_t countPostfixFormLength(const std::string& expression);
	static size_t countOperations(const std::string& expression);
	static Priority checkPriority(const char first, const char second);
	static Variable findVariableByName(const Variables variables, const char name);
public:
	static std::string parse(const std::string& expression);
	static double calculate(const std::string& postfixForm, const Variables variables);
};

#endif // !_POSTFIXFORMPROCESSOR_H_
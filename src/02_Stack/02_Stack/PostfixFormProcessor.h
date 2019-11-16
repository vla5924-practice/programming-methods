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
		notLower,
		notHigher,
		unknown
	};
	static TokenType checkToken(const char token);
	static Priority checkPriority(const char first, const char second);
	static Variable findVariableByName(const Variables variables, const char name);
	static bool checkExpression(const std::string& expression);
	static bool test(const std::string& postfixForm);
public:
	static std::string parse(const std::string& expression);
	static std::string findVariables(const std::string& expression);
	static double calculate(const std::string& postfixForm, const Variables variables);

	class InvalidExpressionError : std::exception
	{
		const std::string whatStr = "Expression is invalid.";
	public:
		virtual const char* what() { return whatStr.c_str(); }
	};
	class InvalidPostfixFormError : InvalidExpressionError
	{
		const std::string whatStr = "Postfix form is invalid.";
	public:
		virtual const char* what() { return whatStr.c_str(); }
	};
	class UndefinedVariable : std::exception
	{
		const std::string whatStr = "Variable not defined in variables array.";
	public:
		virtual const char* what() { return whatStr.c_str(); }
	};
	class DivisionByZero : std::exception
	{
		const std::string whatStr = "Cannot divide by zero.";
	public:
		virtual const char* what() { return whatStr.c_str(); }
	};
};

#endif // !_POSTFIXFORMPROCESSOR_H_

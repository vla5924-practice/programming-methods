#ifndef _PNPROCESSOR_H_
#define _PNPROCESSOR_H_

#include "TStack.h"
#include <string>

class PNProcessor
{
	enum class TokenType
	{
		unknown,
		operand,
		operation,
		bracket,
		space
	};
	static TokenType checkToken(char token);
public:
	struct Variable
	{
		char name;
		double value;
	};
	struct Variables
	{
		Variable* variables;
		size_t count;
	};
	static std::string parse(std::string expression);
	static double calculate(std::string parsed, Variables* variables);
};

#endif // !_PNPROCESSOR_H_
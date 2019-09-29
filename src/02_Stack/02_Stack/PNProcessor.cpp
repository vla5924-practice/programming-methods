#include "PNProcessor.h"

PNProcessor::TokenType PNProcessor::checkToken(char token)
{
	if ((token == ' ') || (token == '\n') || (token == '\t') || (token == '\b'))
		return TokenType::space;
	if ((token == '(') || (token == ')'))
		return TokenType::bracket;
	if (((token >= 'a') && (token <= 'z')) || ((token >= 'A') && (token <= 'Z')))
		return TokenType::operand;
	if ((token == '+') || (token == '-') || (token == '*') || (token == '/'))
		return TokenType::operation;
	return TokenType::unknown;
}

std::string PNProcessor::parse(std::string expression)
{
	return std::string();
}

double PNProcessor::calculate(std::string parsed, Variables* variables)
{
	return 0.0;
}

double PNProcessor::calculate(std::string parsed, Variables* variables)
{
	return 0.0;
}

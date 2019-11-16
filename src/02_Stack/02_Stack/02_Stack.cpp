#include <iostream>
#include "PostfixFormProcessor.h"

int main()
{
	std::string expression;
	std::cout << "Enter your expression: ";
	std::getline(std::cin, expression, '\n');
	std::string postfixForm, variablesNames;
	PostfixFormProcessor::Variables variables;
	try
	{
		postfixForm = PostfixFormProcessor::parse(expression);
		variablesNames = PostfixFormProcessor::findVariables(expression);
		std::cout << "Postfix form: " << postfixForm << '\n';
	}
	catch (PostfixFormProcessor::InvalidExpressionError& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	variables.variables = new PostfixFormProcessor::Variable[variables.count = variablesNames.size()];
	size_t i = 0;
	for (std::string::iterator variableName = variablesNames.begin(); variableName != variablesNames.end(); variableName++)
	{
		variables.variables[i].name = *variableName;
		std::cout << "Enter \'" << *variableName << "\' value: ";
		std::cin >> variables.variables[i].value;
		i++;
	}
	try
	{
		double result = PostfixFormProcessor::calculate(postfixForm, variables);
		std::cout << "\nResult of expression calculation: " << result;
	}
	catch (PostfixFormProcessor::InvalidPostfixFormError& e)
	{
		std::cerr << e.what() << '\n';
		return 2;
	}
	catch (PostfixFormProcessor::DivisionByZero& e)
	{
		std::cerr << e.what() << '\n';
		return 3;
	}
	delete[] variables.variables;
	variables.variables = nullptr;
	variables.count = 0ull;
}
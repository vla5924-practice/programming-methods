#include <iostream>
#include "PostfixFormProcessor.h"

int main()
{
	std::string expression;
	std::cout << "Enter your expression: ";
	std::cin >> expression;
	if (!PostfixFormProcessor::checkExpression(expression))
	{
		std::cout << "Invalid expression.\n";
		return 0;
	}
	std::string variablesNames = PostfixFormProcessor::findVariables(expression);
	PostfixFormProcessor::Variables variables;
	variables.variables = new PostfixFormProcessor::Variable[variables.count = variablesNames.size()];
	size_t i = 0;
	for (std::string::iterator variableName = variablesNames.begin(); variableName != variablesNames.end(); variableName++)
	{
		variables.variables[i].name = *variableName;
		std::cout << "Enter \'" << *variableName << "\' value: ";
		std::cin >> variables.variables[i].value;
		i++;
	}
	std::string postfixForm;
	try
	{
		postfixForm = PostfixFormProcessor::parse(expression);
		std::cout << "Postfix form: " << postfixForm;
	}
	catch (...)
	{
		std::cerr << "error\n";
	}
	try
	{
		double result = PostfixFormProcessor::calculate(postfixForm, variables);
		std::cout << "Result of expression calculation: " << result;
	}
	catch (...)
	{
		std::cerr << "error\n";
	}
}
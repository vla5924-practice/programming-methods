#include <iostream>
#include "PostfixFormProcessor.h"

int main()
{
	std::string expression;
	std::cout << "Enter your expression: ";
	std::getline(std::cin, expression, '\n');
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
	catch (PostfixFormProcessor::InvalidExpressionError& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
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
}
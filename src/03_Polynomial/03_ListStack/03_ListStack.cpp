#include <iostream>
#include "TPostfixFormProcessor.h"

int main()
{
    int stackNum;
    std::cout << "Choose stack type (0: TArrayStack, 1: TListStack): ";
    std::cin >> stackNum;
    TPostfixFormProcessor::StackType stackType = stackNum == 1 ? TPostfixFormProcessor::StackType::List : TPostfixFormProcessor::StackType::Array;
    getc(stdin);
    std::string expression;
    std::cout << "Enter your expression: ";
    std::getline(std::cin, expression, '\n');
    std::string postfixForm, variablesNames;
    TPostfixFormProcessor PFP(stackType, expression.size());
    TPostfixFormProcessor::Variables variables;
    try
    {
        postfixForm = PFP.parse(expression);
        variablesNames = TPostfixFormProcessor::findVariables(expression);
        std::cout << "Postfix form: " << postfixForm << '\n';
    }
    catch (TPostfixFormProcessor::InvalidExpressionError& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    variables.variables = new TPostfixFormProcessor::Variable[variables.count = variablesNames.size()];
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
        double result = PFP.calculate(postfixForm, variables);
        std::cout << "\nResult of expression calculation: " << result;
    }
    catch (TPostfixFormProcessor::InvalidPostfixFormError& e)
    {
        std::cerr << e.what() << '\n';
        return 2;
    }
    catch (TPostfixFormProcessor::DivisionByZero& e)
    {
        std::cerr << e.what() << '\n';
        return 3;
    }
    delete[] variables.variables;
    variables.variables = nullptr;
    variables.count = 0ull;
}
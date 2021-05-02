#pragma once
#include <exception>
#include <string>
#define classException(className, whatStr) class className : std::exception { \
const std::string str = whatStr; \
public: const char* what() const { return str.c_str(); }}
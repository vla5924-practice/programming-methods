#ifndef _EXCEPT_H_
#define _EXCEPT_H_

#include <exception>

#define EXCEPT(CLASSNAME, WHATSTRING) class CLASSNAME : public std::exception \
{ public: CLASSNAME() : std::exception(WHATSTRING) {}; }

#endif
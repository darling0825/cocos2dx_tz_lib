#pragma once

#include <string>
#include <sstream>
#include "../config.h"

NS_TZ_BEGIN

inline int atoi(const std::string& str)
{
	return atoi(str.c_str());
}

inline std::string itoa(int _int)
{
	std::string str;
	std::stringstream _str;
	_str<<_int;
	_str>>str;
	return str;
}

#define itoc(_NUM_) lib::itoa(_NUM_).c_str()

NS_TZ_END
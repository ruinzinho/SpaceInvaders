#pragma once

#include <string>

class Log {
public:
	static void Loading(const std::string &message);
	static void Error(const std::string &message);
};


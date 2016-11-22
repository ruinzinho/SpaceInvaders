#include "Log.hpp"

#include <iostream>
#include <string>


void Log::Loading(const std::string &message) {
	std::cout << "Loading: " << message << std::endl;
}


void Log::Error(const std::string &message) {
	std::cerr << "Error: " << message << std::endl;
}
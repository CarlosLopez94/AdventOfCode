#pragma once

#include "vector"
#include "string"

namespace Util {
	std::vector<std::string> ReadFile(std::string fileName);
	std::vector<std::string> Split(std::string stringToSplit, std::string separator);
}
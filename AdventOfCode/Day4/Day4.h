#pragma once

#include "string"
#include "iostream"
#include "vector"

class Day4
{
public:
	int Main();
private:
	std::vector<std::string> ReadFile(std::string fileName);
	bool IsPassphraseValidPart1(std::string passphraseToCheck);
	bool IsPassphraseValidPart2(std::string passphraseToCheck);
};


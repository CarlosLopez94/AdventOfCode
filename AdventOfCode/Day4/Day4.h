#pragma once

#include "string"
#include "iostream"
#include "vector"

class Day4
{
public:
	int Main();
private:
	bool IsPassphraseValidPart1(std::string passphraseToCheck);
	bool IsPassphraseValidPart2(std::string passphraseToCheck);
};


#pragma once

#include "iostream"
#include "vector"

class Day2
{
public:
	int Main();

private:
	std::vector<std::vector<int>> readInput(std::string);
	void printArray(std::vector<std::vector<int>> vector);
	int checksumRow();
};


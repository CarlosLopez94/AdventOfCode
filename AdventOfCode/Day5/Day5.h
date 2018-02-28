#pragma once

#include "vector"

class Day5
{
public:
	int Main();
private:
	void PrintVector(std::vector<int> vector, int currentPos);
	std::vector<int> ReadFile(std::string fileName);

	int EscapeMazePart1(std::vector<int> vector);
	int EscapeMazePart2(std::vector<int> vector);
};


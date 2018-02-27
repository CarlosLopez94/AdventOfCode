#pragma once

#include "iostream"
#include "vector"

class Day2
{
public:
	int Main();

private:
	std::vector<std::vector<int>>ReadInput(std::string input, const int rowNumber, const int columnNumber);
	void PrintArray(std::vector<std::vector<int>> vector);
	int ChecksumRow(std::vector<std::vector<int>> vector, int row);
	int DivideEvenlyRow(std::vector<std::vector<int>> vector, int row);
};


#pragma once
#include "vector"
#include "string"
class Day14
{
public:
	int Main();
private:
	std::vector<std::vector<char>> ConstructSquare(std::string input);
	void ConstructSquareRow(std::vector<std::vector<char>>& squares, std::string key, int row, std::string sequence);
	int GetUsedSquares(std::vector<std::vector<char>> squares);
	int GetRegionNumber(std::vector<std::vector<char>> squares);
	void CompleteRegion(std::vector<std::vector<char>> squares, std::vector<std::vector<int>>& regions, int currentRegionValue, int row, int column);
};


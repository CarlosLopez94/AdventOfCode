#pragma once

#include "vector"

class Day3
{
public:
	int Main();
private:
	int CalculateVectorDimension(int number);
	//Part1
	void CreateSpiralPart1(std::vector<std::vector<int>>& vector);
	void FindCellWithValue(std::vector<std::vector<int>> vector, int value, int& row, int& column);
	
	//Part2
	void CreateSpiralPart2(std::vector<std::vector<int>>& vector, int input, int& greaterResult);
	int SumOfAdyacents(std::vector<std::vector<int>> vector, int row, int column);
};


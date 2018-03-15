#pragma once

#include "vector"
#include "string"

class Day10
{
public:
	int Main();

	std::vector<int> InitCircularList(int length);
	template<typename T>
	void ReverseCircularList(std::vector<T>& list, int currentPos, int posToReverse);
	void ApplyInputToCircularList(std::vector<int>& circularList, std::vector<int> input, int roundsNumber);
	int CheckCorrectOrder(std::vector<int> list);

	std::vector<int> GetDenseHash(std::vector<int> sparseHash);
	std::string ParseDenseHashToHexadecimalString(std::vector<int> sparseHash);

private:
	void PrintVector(std::vector<int> vector, int currentPos, int postToReverse);
};


#pragma once

#include "vector"
#include "string"

class Day10
{
public:
	int Main();
private:
	std::vector<std::string> ReadFile(std::string fileName);
	std::vector<std::string> Split(std::string stringToSplit, std::string separator);
	void PrintVector(std::vector<int> vector, int currentPos, int postToReverse);

	std::vector<int> InitCircularList(int length);
	template<typename T>
	void ReverseCircularList(std::vector<T>& list, int currentPos, int posToReverse);
	void ApplyInputToCircularList(std::vector<int>& circularList, std::vector<int> input, int roundsNumber);
	int CheckCorrectOrder(std::vector<int> list);

	std::vector<int> GetDenseHash(std::vector<int> sparseHash);
	std::string ParseDecimalToHex(int decimal);
	std::string ParseDenseHashToHexadecimalString(std::vector<int> sparseHash);
};


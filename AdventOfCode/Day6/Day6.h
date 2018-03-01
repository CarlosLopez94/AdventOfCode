#pragma once

#include "map"
#include "vector"
#include "string"

class Day6
{
public:
	int Main();
private:
	std::vector<std::string> ReadFile(std::string fileName);
	std::vector<int> StringToIntVector(std::vector<std::string> stringVector);
	void PrintVector(std::vector<int> vector, int currentPos);
	int FindIndexOfGreater(std::vector<int> vector);
	void RedistributeVector(std::vector<int>& vector, int greater);
	bool CheckRepeatedState(std::map <std::vector<int>, int> statesVisited, std::vector<int> stateToCheck);
	bool CompareEqualVectors(std::vector<int> v1, std::vector<int> v2);
};


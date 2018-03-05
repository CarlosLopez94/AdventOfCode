#pragma once
#include "vector"
#include "string"

class Day11
{
public:
	int Main();
private:
	std::vector<std::string> ReadFile(std::string fileName);
	std::vector<std::string> Split(std::string stringToSplit, std::string separator);

	int FollowChildPath(std::vector<std::string> path, int& childPositionX, int& childPositionY);
	int FindLowestPathToReachPoint(int northSteps, int eastSteps);
};


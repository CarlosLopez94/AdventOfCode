#pragma once
#include "vector"
#include "string"

class Day11
{
public:
	int Main();
private:
	int FollowChildPath(std::vector<std::string> path, int& childPositionX, int& childPositionY);
	int FindLowestPathToReachPoint(int northSteps, int eastSteps);
};


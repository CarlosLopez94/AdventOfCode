#pragma once
#include "list"

class Day1
{
public:
	int Main();

private:
	void part1(int it, std::string line, int& current, int& next);
	void part2(int it, std::string line, int& current, int& next);
	void calculateAndPrintResult(std::list<int> resultList);
};


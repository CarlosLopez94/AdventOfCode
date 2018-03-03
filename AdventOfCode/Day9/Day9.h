#pragma once

#include "string"
#include "vector"
#include "queue"

class Day9
{
public:
	int Main();
private:
	std::string ReadFile(std::string fileName);

	void SpecialCharactersOnQueue(std::queue<char>& stack, std::string text, int& garbageCount);
	int CalculateGroups(std::queue<char> queue);
	int CalculateGroupsAux(std::queue<char> queue, int value);
	void PrintQueue(std::queue<char> stack);
};


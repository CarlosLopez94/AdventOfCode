#pragma once
#include "vector"
#include "string"

class Day19
{
public:
	int Main();
private:
	struct Position {
		std::pair<int, int> direction;
		std::pair<int, int> current;
	};

	std::vector<std::pair<int, int>> InitPossibleDirections();
	Position FindEntrance(std::vector<std::string> map);
	bool NextMove(std::vector<std::string> map, std::vector<std::pair<int, int>> posibleDirections, Position& currentPos, std::string& lettersVisited);
	char GetCharacter(std::vector<std::string> map, std::pair<int, int> position);
	bool CheckFinish(std::vector<std::string> map, std::pair<int, int> position);
	bool CheckOutOfBounds(std::vector<std::string> map, std::pair<int, int> position);

	void PrintPosition(std::vector<std::string> map, Position position);
};


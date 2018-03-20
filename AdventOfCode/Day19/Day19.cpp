#include "Day19.h"
#include "../Util.h"
#include "iostream"
#include "utility"

int Day19::Main() {
	std::cout << "Day 19 - Part 1" << std::endl;
	std::vector<std::string> map = Util::ReadFile("../AdventOfCode/Day19/input.txt");

	//Init posible directions
	std::vector<std::pair<int, int>> posibleDirections = InitPossibleDirections();

	std::string lettersVisited = "";

	//Find the first position (entrance of map)
	Position currentPos = FindEntrance(map);
	int movesCont = 0;
	bool moreMoves = true;
	while (moreMoves) {
		moreMoves = NextMove(map, posibleDirections, currentPos, lettersVisited);
		//PrintPosition(map, currentPos);
		movesCont++;
	}

	std::cout << "The letters visited in the path are: " << lettersVisited << std::endl;

	std::cout << "Part 2" << std::endl;

	std::cout << "Number of movements: " << movesCont << std::endl;


	return 0;
}

std::vector<std::pair<int, int>> Day19::InitPossibleDirections() {
	std::vector<std::pair<int, int>> posibleDirections;
	posibleDirections.push_back(std::make_pair(-1, 0)); //North
	posibleDirections.push_back(std::make_pair(1, 0)); //South
	posibleDirections.push_back(std::make_pair(0, -1)); //West
	posibleDirections.push_back(std::make_pair(0, 1)); //East
	return posibleDirections;
}

Day19::Position Day19::FindEntrance(std::vector<std::string> map) {
	Position entrance;
	entrance.direction = std::make_pair(1, 0); //starts top to bottom
	entrance.current = std::make_pair(0, 0);

	while (GetCharacter(map, entrance.current) != '|') { //if there is not entrance, it will throw error
		entrance.current.second++;
	}

	return entrance;
}

bool Day19::NextMove(std::vector<std::string> map, std::vector<std::pair<int, int>> posibleDirections, Position& currentPos, std::string& lettersVisited) {
	bool existNextMove = true;
	char currentChar = GetCharacter(map, currentPos.current);

	if (currentChar == '+') {	//we have to change direction  
		std::pair<int, int> lastPosition;
		lastPosition.first = currentPos.current.first - currentPos.direction.first;
		lastPosition.second = currentPos.current.second - currentPos.direction.second;

		bool foundNewDirection = false;
		int directionsI = 0;
		while (!foundNewDirection && directionsI < posibleDirections.size()) {
			auto newPosCandidate = Util::AddToPair(currentPos.current, posibleDirections[directionsI]);
			if (newPosCandidate != lastPosition && GetCharacter(map, newPosCandidate) != ' ') {
				//enters if the candidate is empty and it wasnt visited in the last position
				currentPos.direction = posibleDirections[directionsI];
				foundNewDirection = true;
			}
			directionsI++;
		}
		existNextMove = foundNewDirection;
	} else if (Util::IsAlphabetic(currentChar)) {
		lettersVisited += currentChar;

		existNextMove = GetCharacter(map, Util::AddToPair(currentPos.current, currentPos.direction)) != ' ';
	}

	//Update position
	if (existNextMove) {
		currentPos.current.first = currentPos.current.first + currentPos.direction.first;
		currentPos.current.second = currentPos.current.second + currentPos.direction.second;
	}
	return existNextMove;
}

char Day19::GetCharacter(std::vector<std::string> map, std::pair<int, int> position) {
	char charResult = ' ';
	if (CheckOutOfBounds(map, position)) {
		charResult = map[position.first][position.second];
	}
	return charResult;
}

bool Day19::CheckFinish(std::vector<std::string> map, std::pair<int, int> position) {
	return CheckOutOfBounds(map, position);
}

bool Day19::CheckOutOfBounds(std::vector<std::string> map, std::pair<int, int> position) {
	return position.first >= 0 && position.first < map.size()
		&& position.second >= 0 && position.second < map[position.first].size();
}

void Day19::PrintPosition(std::vector<std::string> map, Position position) {
	Util::PrintPair(position.current);
	std::cout << " --> ";
	Util::PrintPair(position.direction);
	std::cout << " --> " << GetCharacter(map, position.current) << std::endl;
}

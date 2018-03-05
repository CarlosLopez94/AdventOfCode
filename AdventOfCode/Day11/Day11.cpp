#include "Day11.h"
#include "iostream"
#include "vector"
#include "fstream"
#include "string"

int Day11::Main() {

	std::cout << "Day 11 - Part 1" << std::endl;
	std::vector<std::string> input = ReadFile("../AdventOfCode/Day11/input.txt");

	int childPositionX = 0;
	int childPositionY = 0;
	int numberStepsFurthest = FollowChildPath(input, childPositionX, childPositionY);
	int steps = FindLowestPathToReachPoint(childPositionX, childPositionY);
	std::cout << "Lowest steps number to reach child: " << steps << std::endl;

	//Part 2 
	std::cout << "The furthest steps from starting position: " << numberStepsFurthest << std::endl;

	return 0;
}

std::vector<std::string> Day11::ReadFile(std::string fileName) {
	std::vector<std::string> lines;
	std::string line;
	std::ifstream myfile(fileName);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			lines.push_back(line);
		}
		myfile.close();
	} else {
		std::cout << "Unable to open file\n";
	}
	return lines;
}

std::vector<std::string> Day11::Split(std::string stringToSplit, std::string separator) {
	std::vector<std::string> tokens;
	std::string stringAux = stringToSplit;
	int indexNextToken = 0;
	while (indexNextToken > -1 && indexNextToken < stringToSplit.size()) {
		indexNextToken = stringAux.find(separator);
		if (indexNextToken != -1) {
			tokens.push_back(stringAux.substr(0, indexNextToken));
			stringAux = stringAux.substr(indexNextToken + separator.size(), stringToSplit.size());//we have to jump the separator
		} else {
			tokens.push_back(stringAux);
		}
	}
	return tokens;
}

int Day11::FollowChildPath(std::vector<std::string> coordinates, int& childPositionX, int& childPositionY) {
	int furtherSteps = 0;
	for (std::string line : coordinates) {
		std::vector<std::string> tokens = Split(line, ",");
		for (std::string token : tokens) {
			if (token == "n") {
				childPositionY--;
			} else if (token == "s") {
				childPositionY++;
			} else if (token == "ne") {
				childPositionX++;
				childPositionY--;
			} else if (token == "nw") {
				childPositionX--;
			} else if (token == "se") {
				childPositionX++;
			} else if (token == "sw") {
				childPositionX--;
				childPositionY++;
			}
			int stepsThisIteration = FindLowestPathToReachPoint(childPositionX, childPositionY);
			if (stepsThisIteration > furtherSteps) {
				furtherSteps = stepsThisIteration;
			}
		}
	}
	return furtherSteps;
}

int Day11::FindLowestPathToReachPoint(int x, int y) {
	int steps = 0;
	std::string path = "";
	while (x != 0 || y != 0) {
		if (x == 0 && y > 0) {
			//move to north
			y--;
			path += "-> s";
			steps++;
		} else if (x < 0 && y > 0) {
			//move to northeast
			x++;
			y--;
			path += "-> sw";
			steps++;
		} else if (x < 0 && y == 0) {
			//move to southeast
			x++;
			path += "-> nw";
			steps++;
		} else if (x == 0 && y < 0) {
			//move to south
			y++;
			path += "-> n";
			steps++;
		} else if (x > 0 && y < 0) {
			//move to soutwest
			x--;
			y++;
			path += "-> ne";
			steps++;
		} else if (x > 0 && y == 0) {
			//move to northwest
			x--;
			path += "-> se";
			steps++;
		} else {
			steps = -1;
			x = 0;
			y = 0;
		}

		if (steps % 300) {
			//std::cout << "x:" << x << "\y" << y << "\tSigo vivo:" << steps << std::endl;
		}
	}
	//std::cout << path << std::endl;

	return steps;
}

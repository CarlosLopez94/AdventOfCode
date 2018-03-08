#include "Day5.h"
#include "../Util.h"
#include "iostream"
#include "fstream"
#include "vector"
#include "string"

int Day5::Main() {
	std::cout << "Day 5!" << std::endl;
	std::vector<std::string> inputAux = Util::ReadFile("../AdventOfCode/Day5/input.txt");
	std::vector<int> vector;
	for (std::string line : inputAux) {
		vector.push_back(stoi(line));
	}
	//vector = { 0,3,0,1,-3 };

	//Part 1
	int numberSteps = EscapeMazePart1(vector);
	std::cout << "Number of steps to scape the first maze: " << numberSteps << std::endl;

	//Part 2
	std::cout << "Part 2" << std::endl;
	int numberStepsMaze2 = EscapeMazePart2(vector);
	std::cout << "Number of steps to scape the second maze: " << numberStepsMaze2 << std::endl;

	return 0;
}

int Day5::EscapeMazePart1(std::vector<int> vector) {
	int numberSteps = 0;
	int currentPos = 0;
	//Util::PrintVector(vector, currentPos);
	while (currentPos >= 0 && currentPos < vector.size()) {
		int cellToIncrement = currentPos;
		int currentValue = vector[currentPos];
		currentPos += currentValue;
		vector[cellToIncrement] = vector[cellToIncrement] + 1;
		//Util::PrintVector(vector, currentPos);
		numberSteps++;
	}
	return numberSteps;
}

int Day5::EscapeMazePart2(std::vector<int> vector) {
	int numberSteps = 0;
	int currentPos = 0;
	//Util::PrintVector(vector, currentPos);
	while (currentPos >= 0 && currentPos < vector.size()) {
		int cellToIncrement = currentPos;
		int currentValue = vector[currentPos];
		currentPos += currentValue;
		if (vector[cellToIncrement]>=3) {
			vector[cellToIncrement] = vector[cellToIncrement] - 1;
		} else {
			vector[cellToIncrement] = vector[cellToIncrement] + 1;
		}
		//Util::PrintVector(vector, currentPos);
		numberSteps++;
	}
	return numberSteps;
}

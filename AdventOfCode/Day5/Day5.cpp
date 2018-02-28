#include "Day5.h"
#include "iostream"
#include "fstream"
#include "vector"
#include "string"

int Day5::Main() {
	std::cout << "Day 5!" << std::endl;
	std::vector<int> vector = ReadFile("../AdventOfCode/Day5/input.txt");
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

std::vector<int> Day5::ReadFile(std::string fileName) {
	std::vector<int> vector;
	std::string line;
	std::ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			vector.push_back(std::stoi(line));
		}
		myfile.close();
	} else {
		std::cout << "Unable to open file\n";
	}

	return vector;
}

void Day5::PrintVector(std::vector<int> vector, int currentPos) {
	for (unsigned i = 0; i < vector.size(); i++) {
		if (i == currentPos) {
			std::cout << '(' << vector[i] << ") ";
		} else {
			std::cout << ' ' << vector[i] << "  ";
		}
	}
	std::cout << std::endl;
}

int Day5::EscapeMazePart1(std::vector<int> vector) {
	int numberSteps = 0;
	int currentPos = 0;
	//PrintVector(vector, currentPos);
	while (currentPos >= 0 && currentPos < vector.size()) {
		int cellToIncrement = currentPos;
		int currentValue = vector[currentPos];
		currentPos += currentValue;
		vector[cellToIncrement] = vector[cellToIncrement] + 1;
		//PrintVector(vector, currentPos);
		numberSteps++;
	}
	return numberSteps;
}

int Day5::EscapeMazePart2(std::vector<int> vector) {
	int numberSteps = 0;
	int currentPos = 0;
	//PrintVector(vector, currentPos);
	while (currentPos >= 0 && currentPos < vector.size()) {
		int cellToIncrement = currentPos;
		int currentValue = vector[currentPos];
		currentPos += currentValue;
		if (vector[cellToIncrement]>=3) {
			vector[cellToIncrement] = vector[cellToIncrement] - 1;
		} else {
			vector[cellToIncrement] = vector[cellToIncrement] + 1;
		}
	//	PrintVector(vector, currentPos);
		numberSteps++;
	}
	return numberSteps;
}

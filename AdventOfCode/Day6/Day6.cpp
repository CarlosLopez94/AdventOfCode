#include "Day6.h"
#include "../Util.h"
#include "sstream"  //for std::istringstream
#include "iterator" //for std::istream_iterator
#include "iostream"
#include "fstream"
#include "string"
#include "map"

int Day6::Main() {
	std::cout << "Day 6!" << std::endl;
	std::vector<int> currentState = StringToIntVector(Util::ReadFile("../AdventOfCode/Day6/input.txt"));

	//currentState = { 0, 2, 7, 0 };
	Util::PrintVector(currentState, 2);

	//Part 1
	int steps = 0;
	bool loopFounded = false;
	std::map <std::vector<int>, int> statesVisited;
	while (!loopFounded) {
		steps++;
		int indexOfGreater = FindIndexOfGreater(currentState);
		RedistributeVector(currentState, indexOfGreater);
		loopFounded = CheckRepeatedState(statesVisited, currentState);

		if (!loopFounded) {//we dont want to overwrite the step when the value if found
			statesVisited[currentState] = steps;
		}

		if (steps % 100 == 0) { //prints every 100 states
			Util::PrintVector(currentState, indexOfGreater);
		}
	}
	std::cout << "Part 1. Number of steps to find the loop: " << steps << std::endl;

	//Part 2
	int loopSize = steps - statesVisited[currentState];
	std::cout << "Part 2. The loop has a size of: " << loopSize << std::endl;

	return 0;
}

std::vector<int> Day6::StringToIntVector(std::vector<std::string> stringVector) {
	std::vector<int> numbers;

	for (auto line = stringVector.begin(); line != stringVector.end(); line++) {
		std::istringstream ss(*line);
		std::istream_iterator<std::string> begin(ss), end;

		//putting all the tokens in the vector
		std::vector<std::string> arrayTokens(begin, end);
		for (auto i = 0; i < arrayTokens.size(); i++) {
			numbers.push_back(stoi(arrayTokens[i]));
		}
	}
	return numbers;
}

int Day6::FindIndexOfGreater(std::vector<int> vector) {
	int greaterIndex = 0;
	for (int i = 0; i < vector.size(); i++) {
		if (vector[i] > vector[greaterIndex]) {
			greaterIndex = i;
		}
	}
	return greaterIndex;
}

void Day6::RedistributeVector(std::vector<int>& vector, int greater) {
	int pointsToRedistribute = vector[greater];
	vector[greater] = 0;

	int iterationIndex = greater;
	while (pointsToRedistribute > 0) {
		iterationIndex = (iterationIndex + 1) % vector.size();
		vector[iterationIndex]++;
		pointsToRedistribute--;
	}
}

bool Day6::CheckRepeatedState(std::map <std::vector<int>, int> statesVisited, std::vector<int> stateToCheck) {
	bool foundRepeated = false;
	auto mapIteration = statesVisited.begin();
	while (!foundRepeated && mapIteration != statesVisited.end()) {
		auto state = mapIteration->first;
		foundRepeated = CompareEqualVectors(state, stateToCheck);
		mapIteration++;
	}
	return foundRepeated;
}

//Vectors must have same size
bool Day6::CompareEqualVectors(std::vector<int> v1, std::vector<int> v2) {
	bool areEquals = true;
	for (int i = 0; areEquals && i < v1.size(); i++) {
		if (v1[i] != v2[i]) {
			areEquals = false;
		}
	}
	return areEquals;
}
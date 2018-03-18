#include "Day16.h"
#include "../Util.h"
#include "iostream"
#include "vector"
#include "string"
#include "set"

int Day16::Main() {
	std::cout << "Day 16 - Part 1" << std::endl;
	std::vector<std::string> input = Util::ReadFile("../AdventOfCode/Day16/input.txt");

	const int SIZE = 16;
	std::vector<char> programList = InitProgramsList(SIZE);
	std::cout << "Init order: " << std::endl;
	Util::PrintVector(programList);
	std::vector<std::string> danceMoves;
	for (std::string danceList : input) {
		std::vector<std::string> tokens = Util::Split(danceList, ",");
		for (std::string move : tokens) {
			danceMoves.push_back(move);
		}
	}

	ProcessDance(programList, danceMoves);
	std::cout << "Final order is: " << std::endl;
	Util::PrintVector(programList);

	std::set<std::vector<char>> statesVisited;
	statesVisited.insert(programList); //Add the dance 

	//Part 2
	std::cout << "\nPart 2" << std::endl;

	int greatDanceNumber = 999999999;//	1000000000 times, counting the first one

	//First find a loop
	bool foundDanceLoop = false;
	int i = 0;
	while (!foundDanceLoop && i < greatDanceNumber) {
		//Dance one time!
		ProcessDance(programList, danceMoves);
		//Check if we find the dance loop
		if (statesVisited.find(programList) != statesVisited.end()) {
			//this state has been visited! we have found the loop!
			foundDanceLoop = true;
			std::cout << "\nThe dance loop size is: " << statesVisited.size() << std::endl;
		} else {
			statesVisited.insert(programList);
		}
		i++;
	}

	//Decrease dance (just "jump" the loops)
	greatDanceNumber = (greatDanceNumber - i) % statesVisited.size();
	for (int i = 0; i < greatDanceNumber; i++) {
		ProcessDance(programList, danceMoves);
	}

	std::cout << "\nFinal order after one billion times (1000000000) is: " << std::endl;
	Util::PrintVector(programList);
	return 0;
}

std::vector<char> Day16::InitProgramsList(int size) {
	std::vector<char> programList(size, 'a');

	for (int i = 0; i < size; i++) {
		programList[i] = (char)programList[i] + i;
	}
	return programList;
}

void Day16::ProcessDance(std::vector<char>& programs, std::vector<std::string> dance) {
	for (std::string move : dance) {
		ProcessDanceMove(programs, move);
	}
}

void Day16::ProcessDanceMove(std::vector<char>& programs, std::string danceMovement) {
	//Select correct movement type
	if (danceMovement[0] == 's') { //Spin
		int spinNumber = std::stoi(danceMovement.substr(1, danceMovement.size()));
		Spin(programs, spinNumber); //TO CHECK
	} else if (danceMovement[0] == 'x') { //Exchange
		std::vector<std::string> tokens = Util::Split(danceMovement.substr(1, danceMovement.size()), "/");
		int position1 = std::stoi(tokens[0]);
		int position2 = std::stoi(tokens[1]);
		Exchange(programs, position1, position2);
	} else if (danceMovement[0] == 'p') { //Partner
		std::vector<std::string> tokens = Util::Split(danceMovement.substr(1, danceMovement.size()), "/");
		char progranName1 = tokens[0][0];
		char progranName2 = tokens[1][0];
		Partner(programs, progranName1, progranName2);
	}
}

void Day16::Spin(std::vector<char>& programs, int spinNumber) {
	std::vector<char> original = programs; //TO CHECK
	for (int i = 0; i < programs.size(); i++) {
		programs[(i + spinNumber) % programs.size()] = original[i];
	}
}

void Day16::Exchange(std::vector<char>& programs, int swapIndex1, int swapIndex2) {
	//Just Swap
	Util::Swap(programs, swapIndex1, swapIndex2);
}

void Day16::Partner(std::vector<char>& programs, char swapName1, char swapName2) {
	//Get Index
	int swapIndex1 = Util::IndexOfValue(programs, swapName1);
	int swapIndex2 = Util::IndexOfValue(programs, swapName2);

	//Swap
	Util::Swap(programs, swapIndex1, swapIndex2);
}
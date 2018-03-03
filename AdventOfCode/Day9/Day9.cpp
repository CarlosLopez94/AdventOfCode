#include "Day9.h"
#include "iostream"
#include "string"
#include "vector"
#include "fstream"
#include "queue"

int Day9::Main() {
	std::cout << "Day 9 - Part 1" << std::endl;

	std::string inputText = ReadFile("../AdventOfCode/Day9/input.txt");
	std::queue<char> queue;

	int garbageCont;
	SpecialCharactersOnQueue(queue, inputText, garbageCont);

	PrintQueue(queue);
	int groups = CalculateGroups(queue);
	std::cout << "The total score for all groups is: " << groups << std::endl;

	std::cout << "Part 2" << std::endl;
	std::cout << "The non-canceled characters inside the garbage is: " << garbageCont << std::endl;

	return 0;
}

std::string Day9::ReadFile(std::string fileName) {
	std::string text = "";
	std::string line;
	std::ifstream myfile(fileName);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			text += line;
		}
		myfile.close();
	} else {
		std::cout << "Unable to open file\n";
	}
	return text;
}

void Day9::SpecialCharactersOnQueue(std::queue<char>& queue, std::string text, int& garbageCount) {
	garbageCount = 0;
	bool waitingCloseGarabage = false;
	for (int i = 0; i < text.size(); i++) {
		char currentChar = text[i];
		if (currentChar != '!') {
			if (!waitingCloseGarabage) {
				if (currentChar == '<') {
					waitingCloseGarabage = true;
				} else if (currentChar == '{' || currentChar == '}') {
					queue.push(currentChar);
				}
			} else {
				if (currentChar == '>') {
					waitingCloseGarabage = false; //if we find the '>' the garbage is close, continue saving characters
				} else {
					garbageCount++;
				}
			}
		} else {
			//if the character is a '!' then  ignore the next one
			i++;
		}
	}
}

int Day9::CalculateGroups(std::queue<char> queue) {
	int groupsSum = 0;
	int	currentValue = 0;

	int print = 0;
	while (!queue.empty()) {
		char currentCharacter = queue.front();
		queue.pop();
		if (currentCharacter == '{') {
			currentValue++;
		} else {
			groupsSum += currentValue;
			currentValue--;
		}
	}

	return groupsSum;
}


int Day9::CalculateGroupsAux(std::queue<char> queue, int value) {
	int groups = 0;
	if (!queue.empty()) {
		char nextChar = queue.front();
		queue.pop();

		if (nextChar == '{') {
			groups = CalculateGroupsAux(queue, value + 1);
		} else { //lastChar == '}'
			groups = value + CalculateGroupsAux(queue, value - 1);
		}
	}
	return groups;
}

void Day9::PrintQueue(std::queue<char> queue) {
	while (!queue.empty()) {
		std::cout << queue.front();
		queue.pop();
	}
	std::cout << std::endl;
}

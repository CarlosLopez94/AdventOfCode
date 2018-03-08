#include "Day1.h"
#include "../Util.h"
#include "iostream"
#include "string"

int Day1::Main()
{
	std::cout << "Starting Day 1! " << std::endl;
	std::string readedLine = Util::ReadFile("../AdventOfCode/Day1/input.txt")[0];
		std::cout << "Your input is: " << readedLine << std::endl;
	//Init list
	std::list<int> repeatedNumber;

	//Part1
	std::cout << "Part 1" << std::endl;
	int current;
	int next;
	for (unsigned i = 0; i < readedLine.length(); i++) {
		part1(i, readedLine, current, next);

		if (current == next) {
			repeatedNumber.emplace_back(current);
		}
	}
	calculateAndPrintResult(repeatedNumber);

	//part2
	std::cout << "Part 2" << std::endl;
	repeatedNumber.clear();

	int half;
	for (unsigned i = 0; i < readedLine.length(); i++) {
		part2(i, readedLine, current, half);

		if (current == half) {
			repeatedNumber.emplace_back(current);
		}
	}
	calculateAndPrintResult(repeatedNumber);

	return 0;
}

void Day1::part1(int it, std::string line, int& current, int& next) {
	if (it == line.length() - 1) { //last iteration
		current = (int)line[it] - '0';
		next = (int)line[0] - '0'; //the list is circular so next is the first
	} else {//in the rest of iterations
		current = (int)line[it] - '0';
		next = (int)line[it + 1] - '0';
	}
}

void Day1::part2(int it, std::string line, int& current, int& half) {
	current = (int)line[it] - '0';
	half = (int)line[(it + line.length() / 2) % line.length()] - '0';
}

void Day1::calculateAndPrintResult(std::list<int> resultList) {
	//Sum the content of the list
	int resultSum = 0;
	for (std::list<int>::iterator it = resultList.begin(); it != resultList.end(); it++) {
		resultSum += *it;
	}

	//Show result
	std::cout << "The result is: " << resultSum << std::endl;
}


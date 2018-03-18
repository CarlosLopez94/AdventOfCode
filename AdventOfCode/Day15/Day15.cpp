#include "Day15.h"
#include "../Util.h"
#include "iostream"
#include "vector"
#include "bitset"

int Day15::Main() {
	std::cout << "Day 15 - Part 1" << std::endl;
	//Get factors and values value
	std::vector<std::string> input = Util::ReadFile("../AdventOfCode/Day15/input.txt");

	for (std::string inputLine : input) {
		std::cout << inputLine << std::endl;
	}

	int_fast64_t factorA = 16807;
	int_fast64_t factorB = 48271;

	int_fast64_t valueA = std::stoi(Util::Split(input[0], " ")[4]);
	int_fast64_t valueB = std::stoi(Util::Split(input[1], " ")[4]);

	int matches = 0;
	int numberPairs = 40000000;//40 000 000;
	std::string binaryA;
	std::string binaryB;
	for (int i = 0; i < numberPairs; i++) {
		//Calculate next value
		valueA = GetNextValue(factorA, valueA);
		valueB = GetNextValue(factorB, valueB);

		//Convert to bitset
		std::bitset<16> binaryA(valueA);
		std::bitset<16> binaryB(valueB);

		//Compare and add a match(if they match of course)
		matches += BinariesEqual(binaryA, binaryB) ? 1 : 0;
	}

	std::cout << "Matches: " << matches << std::endl;

	//Part 2
	std::cout << "Part 2 " << std::endl;
	valueA = std::stoi(Util::Split(input[0], " ")[4]);
	valueB = std::stoi(Util::Split(input[1], " ")[4]);
	int multiplesOfA = 4;
	int multiplesOfB = 8;

	matches = 0;
	numberPairs = 5000000;//40 000 000;
	for (int i = 0; i < numberPairs; i++) {
		//Calculate next value
		valueA = GetNextValuePart2(factorA, valueA, multiplesOfA);
		valueB = GetNextValuePart2(factorB, valueB, multiplesOfB);

		//std::cout << "A: " << valueA << "\tB: " << valueB<< std::endl;


		//Convert to bitset
		std::bitset<16> binaryA(valueA);
		std::bitset<16> binaryB(valueB);

		//Compare and add a match (if they match of course)
		matches += BinariesEqual(binaryA, binaryB) ? 1 : 0;
	}

	std::cout << "Matches: " << matches << std::endl;
	return 0;
}

int_fast64_t Day15::GetNextValue(int_fast64_t factor, int_fast64_t lastValue) {
	return (factor*lastValue) % 2147483647;
}

int_fast64_t Day15::GetNextValuePart2(int_fast64_t factor, int_fast64_t lastValue, int multipleOf) {
	int_fast64_t newValue = lastValue;
	do {
		newValue = (factor*newValue) % (2147483647);
	} while (newValue % multipleOf != 0);

	return newValue;
}

bool Day15::BinariesEqual(std::bitset<16> bin1, std::bitset<16> bin2) {
	return bin1 == bin2;
}

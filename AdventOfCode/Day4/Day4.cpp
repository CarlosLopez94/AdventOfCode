#include "Day4.h"
#include "../Util.h"
#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include "algorithm"

int Day4::Main() {
	std::vector<std::string> input = Util::ReadFile("../AdventOfCode/Day4/input.txt");

	//Part 1
	std::cout << "Day 4 - Part1" << std::endl;
	unsigned validCount = 0;
	for (unsigned i = 0; i < input.size(); i++) {
		//std::cout << vector[i];
		if (IsPassphraseValidPart1(input[i])) {
			//std::cout << "\t--> VALID" << std::endl;
			validCount++;
		} else {
			//std::cout << "\t--> INVALID" << std::endl;
		}
	}
	std::cout << "There are " << validCount << " valid passphrases!" << std::endl;

	//Part 2
	std::cout << "Day 4 - Part2" << std::endl;
	validCount = 0;
	for (unsigned i = 0; i < input.size(); i++) {
		//std::cout << vector[i];
		if (IsPassphraseValidPart2(input[i])) {
			//std::cout << "\t--> VALID" << std::endl;
			validCount++;
		} else {
			//std::cout << "\t--> INVALID" << std::endl;
		}
	}
	std::cout << "There are " << validCount << " valid passphrases!" << std::endl;


	return 0;
}

bool Day4::IsPassphraseValidPart1(std::string passphraseToCheck) {
	bool isValid = true;

	//Split into a vector
	std::vector<std::string> vector;
	std::size_t pos = 0, found;
	while ((found = passphraseToCheck.find_first_of(' ', pos)) != std::string::npos) {
		vector.push_back(passphraseToCheck.substr(pos, found - pos));
		pos = found + 1;
	}
	vector.push_back(passphraseToCheck.substr(pos));

	//Sort vector
	std::sort(vector.begin(), vector.end());

	//Check if there are adyacent cells with equal value
	unsigned i = 0;
	while (isValid && i + 1 < vector.size()) {
		if (vector[i] == vector[i + 1]) {
			isValid = false;
		}
		i++;
	}

	return isValid;
}

bool Day4::IsPassphraseValidPart2(std::string passphraseToCheck) {
	bool isValid = true;

	//Split into a vector
	std::vector<std::string> vector;
	std::size_t pos = 0, found;
	while ((found = passphraseToCheck.find_first_of(' ', pos)) != std::string::npos) {
		//Sort characters of string before added to the vector
		std::string sortedString = passphraseToCheck.substr(pos, found - pos);
		std::sort(sortedString.begin(), sortedString.end());

		//Add sorted string to vector and iterate
		vector.push_back(sortedString);
		pos = found + 1;
	}
	//Sort last an added too
	std::string lastString = passphraseToCheck.substr(pos);
	std::sort(lastString.begin(), lastString.end());
	vector.push_back(lastString);

	//Sort vector
	std::sort(vector.begin(), vector.end());

	//Check if there are adyacent cells with equal value
	unsigned i = 0;
	while (isValid && i + 1 < vector.size()) {
		if (vector[i] == vector[i + 1]) {
			isValid = false;
		}
		i++;
	}

	return isValid;
}
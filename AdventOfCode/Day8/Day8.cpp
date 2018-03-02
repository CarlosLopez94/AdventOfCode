#include "Day8.h"
#include "iostream"
#include "fstream"
#include "string"
#include "map"

int Day8::Main() {
	std::cout << "Day 8 - Part 1" << std::endl;
	std::map<std::string, int> registers;

	std::vector<std::string> input = ReadFile("../AdventOfCode/Day8/input.txt");

	//Init registers with 0
	for (std::string line : input) {
		int index = line.find(" ");
		registers[line.substr(0, index)] = 0; //index-1?
	}

	//Read all isntructions
	int greatestValuePossible = std::numeric_limits<int>::min(); //starts in the minimum possible so is overwrite
	for (std::string instruction : input) {
		int greatestValueThisIteration = ReadInstruction(registers, instruction);
		if (greatestValueThisIteration > greatestValuePossible) {
			greatestValuePossible = greatestValueThisIteration;
		}
	}

	std::string greatestRegister = GetRegisterWithGreatestValue(registers);

	std::cout << "The register with greatest value is: " << greatestRegister << " and its value is: " << registers[greatestRegister] << std::endl;

	//Part 2
	std::cout << "Part 2" << std::endl;
	std::cout << "The greatest value possible is: " << greatestValuePossible << std::endl;
	return 0;
}

std::vector<std::string> Day8::ReadFile(std::string fileName) {
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

std::vector<std::string> Day8::Split(std::string stringToSplit, std::string separator) {
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

int Day8::ReadInstruction(std::map<std::string, int>& registers, std::string instruction) {
	std::vector<std::string> tokens = Split(instruction, " ");

	//Get the condition
	std::string condition = "";
	for (int i = 4; i < tokens.size(); i++) {
		condition += tokens[i];
		if (i < tokens.size() - 1) {
			condition += " ";
		}

	}
	//Check condition
	if (CheckCondition(registers, condition)) {

		//Get the rest of tokens
		std::string reg = tokens[0];
		std::string operation = tokens[1];
		int quantity = stoi(tokens[2]);

		if (operation.compare("inc") == 0) {
			IncreaseRegister(registers, reg, quantity);
		} else { //dec operation
			DecreaseRegister(registers, reg, quantity);
		}
	}
	
	return registers[GetRegisterWithGreatestValue(registers)];
}

bool Day8::CheckCondition(std::map<std::string, int> registers, std::string condition) {
	bool isTrue = false;
	std::vector<std::string> tokens = Split(condition, " ");
	std::string regToCheck = tokens[0];
	std::string operation = tokens[1];
	int numberToCheck = stoi(tokens[2]);

	if (operation.compare(">") == 0) {
		isTrue = registers[regToCheck] > numberToCheck;
	} else if (operation.compare(">=") == 0) {
		isTrue = registers[regToCheck] >= numberToCheck;
	} else if (operation.compare("<") == 0) {
		isTrue = registers[regToCheck] < numberToCheck;
	} else if (operation.compare("<=") == 0) {
		isTrue = registers[regToCheck] <= numberToCheck;
	} else if (operation.compare("==") == 0) {
		isTrue = registers[regToCheck] == numberToCheck;
	} else {//!=
		isTrue = registers[regToCheck] != numberToCheck;
	}

	return isTrue;
}

void Day8::IncreaseRegister(std::map<std::string, int>& registers, std::string reg, int quantity) {
	registers[reg] += quantity;
}

void Day8::DecreaseRegister(std::map<std::string, int>& registers, std::string reg, int quantity) {
	registers[reg] -= quantity;
}

std::string Day8::GetRegisterWithGreatestValue(std::map<std::string, int> registers) {
	std::string regWithGreatestValue = registers.begin()->first;

	for (auto it = registers.begin(); it != registers.end(); it++) {
		if (it->second > registers[regWithGreatestValue]) {
			regWithGreatestValue = it->first;
		}
	}
	return regWithGreatestValue;
}

void Day8::PrintRegisters(std::map<std::string, int> registers) {
	for (auto it = registers.begin(); it != registers.end(); it++) {
		std::cout << it->first << " -->" << it->second << std::endl;
	}

}


#include "Day18.h"
#include "../Util.h"
#include "iostream"
#include "queue"
#include "thread"

int Day18::Main() {
	std::cout << "Day 18 - Part 1" << std::endl;
	std::vector<std::string> input = Util::ReadFile("../AdventOfCode/Day18/input.txt");
	std::map<char, int_fast64_t> registers;
	std::map<int, std::string> instructions;
	InitInstructionsAndRegisters(registers, instructions, input);

	bool finish = false;
	int currentindex = 0;
	int sendCont = 0;
	std::queue<int_fast64_t> frequency;
	while (!finish) {
		finish = ProcessInstruction(registers, instructions[currentindex], frequency, currentindex, sendCont, false);
	}
	std::cout << "The first Frequency is: " << frequency.back() << std::endl;
	
	//Part 2
	std::cout << "Part 2" << std::endl;
	
	
	
	//bool deadLock = false;
	//std::map<char, int_fast64_t> registers0;
	//std::map<char, int_fast64_t> registers1;
	//InitInstructionsAndRegisters(registers0, instructions, input);
	//InitInstructionsAndRegisters(registers1, instructions, input);
	//registers1['p'] = 1; // register 'p' has to start with value 1 in program 1

	//bool program0Waiting = false;
	//bool program1Waiting = false;
	//std::queue<int_fast64_t> queue0;
	//std::queue<int_fast64_t> queue1;
	//int index0 = 0;
	//int index1 = 0;
	//int sendCont0 = 0;
	//int sendCont1 = 0;
	//int program1SendCont = 0;
	//while (!deadLock) {
	//	//Process intruction for program 0
	//	if (ProcessInstruction(registers0, instructions[index0], queue1, index0, sendCont0, true)) {
	//		//if we enter here then we have to recover the frequency
	//		if (queue0.empty()) {
	//			//if the queue is empty then we wait
	//			program0Waiting = true;
	//			index0--;//decrease index to remain in the same instruction next iteration
	//		} else {
	//			char regToStore = Util::Split(instructions[index0 - 1], " ")[1][0];
	//			registers0[regToStore] = queue0.front();
	//			queue0.pop();
	//			program0Waiting = false;
	//		}
	//	}

	//	//Process intruction for program 1
	//	if (ProcessInstruction(registers1, instructions[index1], queue0, index1, sendCont1, true)) {
	//		//if we enter here then we have to recover the frequency
	//		if (queue1.empty()) {
	//			//if the queue is empty then we wait
	//			program1Waiting = true;
	//			index1--;//decrease index to remain in the same instruction next iteration
	//		} else {
	//			char regToStore = Util::Split(instructions[index1 - 1], " ")[1][0];
	//			registers1[regToStore] = queue1.front();
	//			queue1.pop();
	//			program1Waiting = false;
	//		}
	//	}
	//	deadLock = program0Waiting && program1Waiting;
	//	//std::cout << "index0: " << index0 << " |||| index1: " << index1 << std::endl;
	//}

	//std::cout << "Program 1 send " << sendCont1 << " frequencies" << std::endl;

	return 0;
}


void Day18::InitInstructionsAndRegisters(std::map<char, int_fast64_t>& registers, std::map<int, std::string>& instructions, std::vector<std::string> input) {
	int cont = 0;
	for (std::string line : input) {
		instructions[cont] = line;
		char reg = Util::Split(line, " ")[1][0];
		if (Util::IsAlphabetic(reg)) {
			registers[reg] = 0;
		}
		cont++;
	}
}

bool Day18::ProcessInstruction(std::map<char, int_fast64_t>& registers, std::string instruction, std::queue<int_fast64_t>& sendFrequency, int& currentIndex, int& sendCont, bool isPart2) {
	std::vector<std::string> inst = Util::Split(instruction, " ");
	std::string instType = inst[0];
	char reg = inst[1][0];
	bool frequencyChecked = false;
	if (instType.compare("snd") == 0) {
		int_fast64_t value = GetValue(registers, inst[1]);
		Snd(registers, sendFrequency, value);
		currentIndex++;
		sendCont++;
	} else if (instType.compare("set") == 0) {
		int_fast64_t value = GetValue(registers, inst[2]);
		Set(registers, reg, value);
		currentIndex++;
	} else if (instType.compare("add") == 0) {
		int_fast64_t value = GetValue(registers, inst[2]);
		Add(registers, reg, value);
		currentIndex++;
	} else if (instType.compare("mul") == 0) {
		int_fast64_t value = GetValue(registers, inst[2]);
		Mul(registers, reg, value);
		currentIndex++;
	} else if (instType.compare("mod") == 0) {
		int_fast64_t value = GetValue(registers, inst[2]);
		Mod(registers, reg, value);
		currentIndex++;
	} else if (instType.compare("rcv") == 0) {
		frequencyChecked = Rcv(registers, reg, isPart2); //if its part2 this return true, and the execution continues 
		currentIndex++;
	} else if (instType.compare("jgz") == 0) {
		int_fast64_t offsetValue = GetValue(registers, inst[2]);
		Jgz(registers, reg, offsetValue, currentIndex);
	}
	return frequencyChecked;
}

void Day18::Snd(std::map<char, int_fast64_t> registers, std::queue<int_fast64_t>& frequency, int_fast64_t value) {
	frequency.push(value);
}

void Day18::Set(std::map<char, int_fast64_t>& registers, char reg, int_fast64_t value) {
	registers[reg] = value;
}

void Day18::Add(std::map<char, int_fast64_t>& registers, char reg, int_fast64_t valueToAdd) {
	registers[reg] = registers[reg] + valueToAdd;
}

void Day18::Mul(std::map<char, int_fast64_t>& registers, char regToStore, int_fast64_t multiplyValue) {
	registers[regToStore] = registers[regToStore] * multiplyValue;
}

void Day18::Mod(std::map<char, int_fast64_t>& registers, char regToDivide, int_fast64_t modValue) {
	if (modValue != 0) {
		registers[regToDivide] = registers[regToDivide] % modValue;
	}
}

bool Day18::Rcv(std::map<char, int_fast64_t> registers, char reg, bool isPart2) {
	bool canReceived = false;
	if (registers[reg] > 0) {
		canReceived = true;
	}
	return canReceived || isPart2;
}

void Day18::Jgz(std::map<char, int_fast64_t> registers, char regCondition, int offsetJump, int & currentIndex) {
	if (registers[regCondition] > 0) {
		currentIndex = currentIndex + offsetJump;
	} else {
		currentIndex++; //if cant jump, then next instruction
	}
}

int_fast64_t Day18::GetValue(std::map<char, int_fast64_t> registers, std::string regOrValue) {
	int_fast64_t valueReturn;
	if (Util::IsAlphabetic(regOrValue[0])) {
		valueReturn = registers[regOrValue[0]];
	} else {
		valueReturn = std::stoi(regOrValue);
	}
	return valueReturn;
}


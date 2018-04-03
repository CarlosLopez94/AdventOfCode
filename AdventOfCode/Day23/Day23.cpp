#include "Day23.h"
#include "../Util.h"
#include "iostream"

int Day23::Main() {
	std::cout << "Day 23 - Part 1" << std::endl;
	std::vector<std::string> input = Util::ReadFile("../AdventOfCode/Day23/input.txt");
	std::map<char, int_fast64_t> registers;
	std::map<int, std::string> instructions;
	InitInstructionsAndRegisters(registers, instructions, input);

	int_fast64_t currentindex = 0;
	int mulInstructionCont = 0;
	while (currentindex >= 0 && currentindex < instructions.size()) {
		currentindex = ProcessInstruction(registers, instructions[currentindex], currentindex, mulInstructionCont);
	}
	std::cout << "The number of 'mul' instruction executed is: " << mulInstructionCont << std::endl;

	std::cout << "Part 2 " << std::endl;
	OptimizedProgram(registers);
	std::cout << "The value left on 'h' is: " << registers['h'] << std::endl;
	return 0;
}

void Day23::InitInstructionsAndRegisters(std::map<char, int_fast64_t>& registers, std::map<int, std::string>& instructions, std::vector<std::string> input) {
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

int Day23::ProcessInstruction(std::map<char, int_fast64_t>& registers, std::string instruction, int_fast64_t& currentIndex, int& mulInstructionCont) {
	std::vector<std::string> inst = Util::Split(instruction, " ");
	std::string instType = inst[0];
	char reg = inst[1][0];

	if (instType.compare("set") == 0) {
		int_fast64_t value = GetValue(registers, inst[2]);
		Set(registers, reg, value);
		currentIndex++;
	} else if (instType.compare("sub") == 0) {
		int_fast64_t value = GetValue(registers, inst[2]);
		Sub(registers, reg, value);
		currentIndex++;
	} else if (instType.compare("mul") == 0) {
		int_fast64_t value = GetValue(registers, inst[2]);
		Mul(registers, reg, value);
		currentIndex++;
		mulInstructionCont++;
	} else if (instType.compare("jnz") == 0) {
		int_fast64_t conditionValue = GetValue(registers, inst[1]);
		int_fast64_t offsetValue = GetValue(registers, inst[2]);
		Jnz(registers, conditionValue, offsetValue, currentIndex);
	}
	return currentIndex;
}

void Day23::Set(std::map<char, int_fast64_t>& registers, char reg, int_fast64_t value) {
	registers[reg] = value;
}

void Day23::Sub(std::map<char, int_fast64_t>& registers, char reg, int_fast64_t valueToAdd) {
	registers[reg] = registers[reg] - valueToAdd;
}

void Day23::Mul(std::map<char, int_fast64_t>& registers, char regToStore, int_fast64_t multiplyValue) {
	registers[regToStore] = registers[regToStore] * multiplyValue;
}

void Day23::Jnz(std::map<char, int_fast64_t>& registers, int_fast64_t conditionValue, int_fast64_t offsetJump, int_fast64_t& currentIndex) {
	if (conditionValue != 0) {
		currentIndex = currentIndex + offsetJump;
	} else {
		currentIndex++; //if cant jump, then next instruction
	}
}

int_fast64_t Day23::GetValue(std::map<char, int_fast64_t> registers, std::string regOrValue) {
	int_fast64_t valueReturn;
	if (Util::IsAlphabetic(regOrValue[0])) {
		valueReturn = registers[regOrValue[0]];
	} else {
		valueReturn = std::stoi(regOrValue);
	}
	return valueReturn;
}

void Day23::OptimizedProgram(std::map<char, int_fast64_t>& registers) {
	registers['b'] = 106500;
	registers['c'] = registers['b'] + 17000;
	registers['h'] = 0;
	for (int i = registers['b']; i < registers['c'] + 1; i += 17) {
		if (!IsPrime(i)) {
			registers['h']++;
		}
	}
}

bool Day23::IsPrime(int_fast64_t n) {
	bool isPrime = true;
	for (int i = 2; i <= n / 2 && isPrime; ++i) {
		if (n % i == 0) {
			isPrime = false;
			break;
		}
	}
	return isPrime;
}



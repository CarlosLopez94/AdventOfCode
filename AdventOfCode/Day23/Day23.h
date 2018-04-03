#pragma once
#include "map"
#include "string"
#include "vector"

class Day23
{
public:
	int Main();
private:
	void InitInstructionsAndRegisters(std::map<char, int_fast64_t>& registers, std::map<int, std::string>& instructions, std::vector<std::string> input);
	int ProcessInstruction(std::map<char, int_fast64_t>& registers, std::string instruction, int_fast64_t& currentIndex, int& mulInstructionCont);
	void Set(std::map<char, int_fast64_t>& registers, char reg, int_fast64_t value);
	void Sub(std::map<char, int_fast64_t>& registers, char reg, int_fast64_t valueToAdd);
	void Mul(std::map<char, int_fast64_t>& registers, char regToStore, int_fast64_t multiplyValue);
	void Jnz(std::map<char, int_fast64_t>& registers, int_fast64_t conditionValue, int_fast64_t offsetJump, int_fast64_t& currentIndex);

	//If is a value return it, if its a alphabetic letter return value inside its register
	int_fast64_t GetValue(std::map<char, int_fast64_t> registers, std::string regOrValue);

	//Part 2
	void OptimizedProgram(std::map<char, int_fast64_t>& registers);
	bool IsPrime(int_fast64_t n);
};


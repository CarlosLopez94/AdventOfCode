#pragma once
#include "map"
#include "string"
#include "vector"
#include "queue"

class Day18
{
public:
	int Main();
private:
	void InitInstructionsAndRegisters(std::map<char, int_fast64_t>& registers, std::map<int, std::string>& instructions, std::vector<std::string> input);
	bool ProcessInstruction(std::map<char, int_fast64_t>& registers, std::string instruction, std::queue<int_fast64_t>& sendFrequency, int_fast64_t& currentIndex, int& sendCont, bool isPart2);
	void Snd(std::map<char, int_fast64_t> registers, std::queue<int_fast64_t>& frequency, int_fast64_t value);
	void Set(std::map<char, int_fast64_t>& registers, char reg, int_fast64_t value);
	void Add(std::map<char, int_fast64_t>& registers, char reg, int_fast64_t valueToAdd);
	void Mul(std::map<char, int_fast64_t>& registers, char regToStore, int_fast64_t multiplyValue);
	void Mod(std::map<char, int_fast64_t>& registers, char regToDivide, int_fast64_t modValue);
	bool Rcv(std::map<char, int_fast64_t> registers, char reg, bool isPart2);
	void Jgz(std::map<char, int_fast64_t> registers, int_fast64_t conditionValue, int_fast64_t offsetJump, int_fast64_t& currentIndex);

	//If is a value return it, if its a alphabetic letter return value inside its register
	int_fast64_t GetValue(std::map<char, int_fast64_t> registers, std::string regOrValue);
};


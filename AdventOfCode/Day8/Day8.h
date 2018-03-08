#pragma once

#include "vector"
#include "string"
#include "map"

class Day8
{
public:
	int Main();
private:
	int ReadInstruction(std::map<std::string, int>& registers, std::string instruction);
	bool CheckCondition(std::map<std::string, int> registers, std::string condition);
	void IncreaseRegister(std::map<std::string, int>& registers, std::string reg, int quantity);
	void DecreaseRegister(std::map<std::string, int>& registers, std::string reg, int quantity);
	std::string GetRegisterWithGreatestValue(std::map<std::string, int> registers);
	void PrintRegisters(std::map<std::string, int> registers);
};
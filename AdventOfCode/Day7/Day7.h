#pragma once

#include "vector"
#include "map"
#include "set"

class Day7
{
public:
	int Main();
private:
	struct Program {
		std::string name;
		std::string fatherName;
		int weight;
		std::vector<std::string> subprograms;
	};
	Program FindRoot(std::map<std::string, Program> programs);
	int CorrectWrongWeight(std::map<std::string, Program> programs, std::map<std::string, int>& weights, Program root);
	int GetSumOfProgram(std::map<std::string, Program> programs, std::map<std::string, int>& weights, std::string programToSum);

	void PrintProgram(std::map<std::string, Program> programs, std::map<std::string, int> weights, Program root);
	void PrintProgramAux(std::map<std::string, Program> programs, std::map<std::string, int> weights, Program root, int deep, std::string indent);
	Program FindNotBalanced(std::map<std::string, Program> programs, std::map<std::string, int> weights,Program programToCheck);
};


#include "Day7.h"
#include "../Util.h"
#include "iostream"
#include "fstream"
#include "string"
#include "algorithm" //sort

int Day7::Main() {
	std::cout << "Day 7! Part 1" << std::endl;

	//Read file
	std::vector<std::string> lines = Util::ReadFile("../AdventOfCode/Day7/input.txt");
	std::map<std::string, Program> programs;

	//Get all programs
	std::string subprogramsSeparator = "-> ";
	for (int i = 0; i < lines.size(); i++) {
		Program newProgram;

		//Get the name and weight of program
		newProgram.name = lines[i].substr(0, lines[i].find(" "));
		newProgram.weight = stoi(lines[i].substr(lines[i].find("(") + 1, lines[i].find(")") - 1));

		//Insert the program in the map
		size_t separatorIndex = lines[i].find(subprogramsSeparator);
		if (separatorIndex != -1) { //it has subprograms
			std::string subprogramList = lines[i].substr(separatorIndex + subprogramsSeparator.size(), lines[i].size() - 1);
			newProgram.subprograms = Util::Split(subprogramList, ", ");
		}
		programs[newProgram.name] = newProgram;
	}

	Program root = FindRoot(programs);
	std::cout << "The root name is: " << root.name << std::endl;

	////Part 2
	std::map<std::string, int> weights;
	std::cout << "Day 7! Part 2" << std::endl;
	int correctWeight = CorrectWrongWeight(programs, weights, root);

	std::cout << "The correct weight is: " << correctWeight << std::endl;

	PrintProgram(programs, weights, root);

	return 0;
}

Day7::Program Day7::FindRoot(std::map<std::string, Program> programs) {
	////Get all the programs names
	std::set<std::string> noSubprograms;
	for (auto it = programs.begin(); it != programs.end(); it++) {
		noSubprograms.insert(it->first);
	}

	////Delete from noSubprogram vector all the subprograms
	for (auto it = programs.begin(); it != programs.end(); it++) {
		Program p = it->second;
		//Delete ONLY the subprograms
		for (int i = 0; i < p.subprograms.size(); i++) {
			noSubprograms.erase(p.subprograms[i]);
		}
	}

	////The last item that remains inside the vector is the root
	Program root = programs[*noSubprograms.begin()];

	return root;
}

int Day7::CorrectWrongWeight(std::map<std::string, Program> programs, std::map<std::string, int>& weights, Program root) {

	//Get sum of subprograms of root
	std::vector<int> sumsVector;
	for (int i = 0; i < root.subprograms.size(); i++) {
		Program subprogram = programs[root.subprograms[i]];
		sumsVector.push_back(GetSumOfProgram(programs, weights, subprogram.name));
	}

	Program programToBalanced = FindNotBalanced(programs, weights, root);

	//Check different value
	std::sort(sumsVector.begin(), sumsVector.end());
	/*Root has minimum 3 subprograms and there is only one different value, the vector is sorted so
	the different value will be the first or the last.*/
	int correctWeight;
	int wrongWeight;
	if (sumsVector[0] == sumsVector[1]) { //the wrong is in the last position
		correctWeight = sumsVector[0];
		wrongWeight = sumsVector[sumsVector.size() - 1];
	} else {
		correctWeight = sumsVector[sumsVector.size() - 1];
		wrongWeight = sumsVector[0];
	}

	std::cout << "The program is: " << programToBalanced.name << " and its wrong is weight: " << programToBalanced.weight << std::endl;

	//PrintProgram(programs, weights, programToBalanced);

	return programToBalanced.weight - (wrongWeight - correctWeight);
}

int Day7::GetSumOfProgram(std::map<std::string, Program> programs, std::map<std::string, int>& weights, std::string programToSumName) {
	Program programToSum = programs[programToSumName];
	int sum = programToSum.weight;
	for (int i = 0; i < programToSum.subprograms.size(); i++) {
		Program subprogram = programs[programToSum.name];

		if (weights.find(subprogram.name) != weights.end()) {
			sum += weights[subprogram.name];
		} else {
			sum += GetSumOfProgram(programs, weights, programToSum.subprograms[i]);
		}
	}
	weights[programToSum.name] = sum;
	return sum;
}

Day7::Program Day7::FindNotBalanced(std::map<std::string, Program> programs, std::map<std::string, int> weights, Program programToCheck) {
	Program programNotBalanced;
	std::map<int, Program> weightsMap;
	std::map<int, int> weightsRepetitions;
	bool found = false;
	for (int i = 0; !found && i < programToCheck.subprograms.size(); i++) {
		Program currentProgram = programs[programToCheck.subprograms[i]];
		int currentTotalWeight = weights[currentProgram.name];
		weightsMap[currentTotalWeight] = currentProgram;
		if (weightsRepetitions.find(currentTotalWeight) != weightsRepetitions.end()) {
			weightsRepetitions[currentTotalWeight] = weightsRepetitions[currentTotalWeight] + 1;
		} else {
			weightsRepetitions[currentTotalWeight] = 1;
		};
	}

	if (weightsRepetitions.size() > 1) {
		auto it = weightsRepetitions.begin();
		if (it->second > 1) { 
			// If its true, the wrong program is the next iteration, if its not then the problem is this program or one of its subprograms
			it++;
		}
		programNotBalanced = FindNotBalanced(programs, weights, weightsMap[it->first]);
	} else {
		programNotBalanced = programToCheck;
	}
	return programNotBalanced;
}


void Day7::PrintProgram(std::map<std::string, Program> programs, std::map<std::string, int> weights, Program root) {
	PrintProgramAux(programs, weights, root, 1, "\t");
}

void Day7::PrintProgramAux(std::map<std::string, Program> programs, std::map<std::string, int> weights, Program program, int deep, std::string indent) {
	std::cout << "- " << program.name << " (" << weights[program.name] << ")" << std::endl;
	for (std::string subprogramName : program.subprograms) {
		Program p = programs[subprogramName];
		for (int i = 0; i < deep; i++) {
			std::cout << indent;
		}
		PrintProgramAux(programs, weights, p, deep + 1, indent);
	}
}


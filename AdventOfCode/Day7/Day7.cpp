#include "Day7.h"
#include "iostream"
#include "fstream"
#include "string"
#include "algorithm" //sort

int Day7::Main() {
	std::cout << "Day 7! Part 1" << std::endl;

	//Read file
	std::vector<std::string> lines = ReadFile("../AdventOfCode/Day7/input.txt");
	std::map<std::string, Program> programs;

	//Get all programs
	std::string subprogramsSeparator = "-> ";
	for (int i = 0; i < lines.size(); i++) {
		Program newProgram;

		//Get the name and weight of program
		newProgram.name = lines[i].substr(0, lines[i].find(" "));
		newProgram.weight = stoi(lines[i].substr(lines[i].find("(") + 1, lines[i].find(")") - 1));

		//Insert the program in the map
		int separatorIndex = lines[i].find(subprogramsSeparator);
		if (separatorIndex != -1) { //it has subprograms
			std::string subprogramList = lines[i].substr(separatorIndex + subprogramsSeparator.size(), lines[i].size() - 1);
			newProgram.subprograms = Split(subprogramList, ", ");
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

std::vector<std::string> Day7::ReadFile(std::string fileName) {
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

std::vector<std::string> Day7::Split(std::string stringToSplit, std::string separator) {
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



	//auto firstPos = weightsMap.begin();
	//auto secondPos = weightsMap.begin()++;
	//auto finalPos = weightsMap.end();

	//if (firstPos == finalPos) {
	//	//If the fist and the last are equal, then the problem is not in the subprograms
	//	programNotBalanced = programToCheck;
	//} else if (firstPos == secondPos) {
	//	//the wrong is in the last position
	//	programNotBalanced = FindNotBalanced(programs, weights, programs[programToCheck.subprograms[programToCheck.subprograms.size() - 1]]);
	//} else {
	//	//The wrong is in the first position
	//	programNotBalanced = FindNotBalanced(programs, weights, programs[programToCheck.subprograms[0]]);
	//}

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


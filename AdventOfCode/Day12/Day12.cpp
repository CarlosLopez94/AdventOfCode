#include "Day12.h"
#include "../Util.h"
#include "iostream"
#include "fstream"
#include "map"
#include "set"

int Day12::Main() {
	std::cout << "Day 12 - Part 1" << std::endl;
	std::vector<std::string> input = Util::ReadFile("../AdventOfCode/Day12/input.txt");

	std::map<int, std::set<int>> connections = GetConnections(input);

	std::set<int> programsInGroup = GetAllConnectionsOfGroup(connections, 0);

	std::cout << "The number of programs inside the group is: " << programsInGroup.size() << ". The group is the next one:" << std::endl;
	Util::PrintSet(programsInGroup);

	std::cout << "Part 2 " << std::endl;
	int numberOfGroups = GetNumberOfGroups(connections);
	std::cout << "The number of groups is: " << numberOfGroups << std::endl;

	return 0;
}

std::map<int, std::set<int>> Day12::GetConnections(std::vector<std::string> connectionsVectorString){
	std::map<int, std::set<int>> connections;

	for (std::string connection : connectionsVectorString) {
		std::vector<std::string> tokens = Util::Split(connection, " <-> ");
		//It always will return 2 tokens
		int programGroup = stoi(tokens[0]); //Get left part
		//Get progrmas (right part)
		std::vector<std::string> programs = Util::Split(tokens[1], ", ");
		for (std::string programS : programs) {
			int program = stoi(programS); //parse to int

			//Insert groups in both directions
			connections[programGroup].insert(program);
			connections[program].insert(programGroup);
		}
	}

	return connections;
}

std::set<int> Day12::GetAllConnectionsOfGroup(std::map<int, std::set<int>> connections, int program) {
	//Init set of programs and add the program we have
	std::set<int> programsInGroup; //empty set of programs

	//Recursive method
	GetAllConnectionsOfGroupAux(connections, program, programsInGroup);

	return programsInGroup;
}

void Day12::GetAllConnectionsOfGroupAux(std::map<int, std::set<int>> connections, int program, std::set<int>& programsInGroup) {
	if (programsInGroup.find(program) == programsInGroup.end()) { // if the program is not in the group yet, we add it and check the programs connected to it
		programsInGroup.insert(program);
		for (int programConnected : connections[program]) {
			GetAllConnectionsOfGroupAux(connections, programConnected, programsInGroup);
		}
	}
}

int Day12::GetNumberOfGroups(std::map<int, std::set<int>> connections){
	//Init set and get all the programs
	std::set<int> programsWithNoGroup;
	for (auto it : connections) {
		int program = it.first;
		programsWithNoGroup.insert(program);
	}

	int numberOfGroups = 0;
	while (!programsWithNoGroup.empty()) {
		//Get the first program remainin in the group
		int programWithouthGroup = *programsWithNoGroup.begin();

		//Get all the programs of that group
		std::set<int> programsWithGroup = GetAllConnectionsOfGroup(connections, programWithouthGroup);

		//Just keep the progams with no group assigned
		for (int program : programsWithGroup) {
			programsWithNoGroup.erase(program);
		}

		//Increase number of groups
		numberOfGroups++;

		//Repeat until is empty
	}
	return numberOfGroups;
}



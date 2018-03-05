#pragma once

#include "vector"
#include "string"
#include "map"
#include "set"

class Day12
{
public:
	int Main();
private:
	std::vector<std::string> ReadFile(std::string fileName);
	std::vector<std::string> Split(std::string stringToSplit, std::string separator);
	std::map<int, std::set<int>> GetConnections(std::vector<std::string> connectionsVectorString);
	std::set<int> GetAllConnectionsOfGroup(std::map<int, std::set<int>> connections, int program);
	void GetAllConnectionsOfGroupAux(std::map<int, std::set<int>> connections, int program, std::set<int>& programsInGroup);
	int GetNumberOfGroups(std::map<int, std::set<int>> connections);
	
	void PrintSet(std::set<int> setToPrint);
};


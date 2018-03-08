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
	std::map<int, std::set<int>> GetConnections(std::vector<std::string> connectionsVectorString);
	std::set<int> GetAllConnectionsOfGroup(std::map<int, std::set<int>> connections, int program);
	void GetAllConnectionsOfGroupAux(std::map<int, std::set<int>> connections, int program, std::set<int>& programsInGroup);
	int GetNumberOfGroups(std::map<int, std::set<int>> connections);
};


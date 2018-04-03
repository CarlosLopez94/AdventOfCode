#pragma once
#include "utility"
#include "vector"

class Day22
{
public:
	int Main();
private:

	enum State {
		CLEAN,
		WEAKENED,
		INFECTED,
		FLAGGED
	};

	struct Virus {
		int currentDirIndex;
		std::pair<int, int> pos;
	};

	void InitCluster(std::vector<std::vector<State>>& cluster, std::pair<int, int>& center, std::vector<std::string> inputCluster);
	void InitDirections(std::vector<std::pair<int, int>>& directions);
	void InitVirus(Virus& virus, std::pair<int,int> center);

	void NextBurst(std::vector<std::vector<State>>& cluster, std::vector<std::pair<int, int>> directions,Virus& virus, int& infectionsCont);
	void NextBurstPart2(std::vector<std::vector<State>>& cluster, std::vector<std::pair<int, int>> directions, Virus& virus, int& infectionsCont);

	bool CheckState(std::vector<std::vector<State>>& cluster, std::pair<int, int> pos, State stateToCheck);
	void ChangeState(std::vector<std::vector<State>>& cluster, std::pair<int, int> pos, State nextState);
	int TurnSides(int currentDirection, bool turnToRight);

	bool CheckOutOfBounds(std::vector<std::vector<State>>& cluster, std::pair<int, int> position);
	void ExtendCluster(std::vector<std::vector<State>>& cluster, std::pair<int, int>& position, int increaseBy);
};


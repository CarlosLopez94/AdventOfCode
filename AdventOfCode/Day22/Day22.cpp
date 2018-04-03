#include "Day22.h"
#include "../Util.h"
#include "iostream"

int Day22::Main() {
	std::cout << "Day 22 - Part 1" << std::endl;
	auto input = Util::ReadFile("../AdventOfCode/Day22/input.txt");

	//Init cluster
	std::vector<std::vector<State>> cluster;
	std::pair<int, int> center;
	InitCluster(cluster, center, input);
	//Init directions
	std::vector<std::pair<int, int>> directions;
	InitDirections(directions);

	//Init virus
	Virus virus;
	InitVirus(virus, center);

	const int BURST_NUMBER = 10000;
	int infectionsCont = 0;
	for (int i = 0; i < BURST_NUMBER; i++) {
		NextBurst(cluster, directions, virus, infectionsCont);
	}
	std::cout << "Number of burst that causes infections after " << BURST_NUMBER << " iterations: " << infectionsCont << std::endl;

	std::cout << "Part 2" << std::endl;
	//Init cluster
	cluster.clear();
	InitCluster(cluster, center, input);
	//Init virus
	InitVirus(virus, center);
	const int BURST_NUMBER_PART_2 = 10000000;
	infectionsCont = 0;
	for (int i = 0; i < BURST_NUMBER_PART_2; i++) {
		if (i % 100000 == 0) {
			std::cout << "Iteration " << i <<"..."<< std::endl;
		}
		NextBurstPart2(cluster, directions, virus, infectionsCont);
	}
	std::cout << "Number of burst that causes infections after "<< BURST_NUMBER_PART_2<<" iterations: " << infectionsCont << std::endl;

	return 0;
}

void Day22::InitCluster(std::vector<std::vector<State>>& cluster, std::pair<int, int>& center, std::vector<std::string> inputCluster) {
	//Init cluster
	cluster = std::vector<std::vector<State>>(inputCluster.size(), std::vector<State>(inputCluster[0].size(), State::CLEAN));

	//Poblate cluster
	for (int i = 0; i < inputCluster.size(); i++) {
		for (int j = 0; j < inputCluster[i].size(); j++) {
			if (inputCluster[i].at(j) == '#') {
				cluster[i][j] = State::INFECTED;
			}
		}
	}

	//Find cluster center
	center.first = (int)inputCluster.size() / 2;
	center.second = (int)inputCluster[inputCluster.size() / 2].size() / 2;
}

void Day22::InitDirections(std::vector<std::pair<int, int>>& directions) {
	directions.push_back(std::make_pair(-1, 0)); //UP
	directions.push_back(std::make_pair(0, 1)); //RIGHT
	directions.push_back(std::make_pair(1, 0)); //DOWN
	directions.push_back(std::make_pair(0, -1)); //LEFT
}

void Day22::InitVirus(Virus& virus, std::pair<int, int> center) {
	virus = Virus();
	virus.currentDirIndex = 0; //UP
	virus.pos.first = center.first;
	virus.pos.second = center.second;
}

void Day22::NextBurst(std::vector<std::vector<State>>& cluster, std::vector<std::pair<int, int>> directions, Virus & virus, int & infectionsCont) {
	bool turnsToRight;
	//infects or clean and turn right or left
	if (CheckState(cluster, virus.pos, INFECTED)) {
		turnsToRight = true;
		ChangeState(cluster, virus.pos, State::CLEAN); //clean node
	} else {
		turnsToRight = false;
		ChangeState(cluster, virus.pos, State::INFECTED); //infects node
		infectionsCont++;
	}
	//update virus
	virus.currentDirIndex = TurnSides(virus.currentDirIndex, turnsToRight);

	auto newDir = directions[virus.currentDirIndex];
	virus.pos.first = virus.pos.first + newDir.first;
	virus.pos.second = virus.pos.second + newDir.second;

	//check bounds and extend if necesary
	if (CheckOutOfBounds(cluster, virus.pos)) {
		ExtendCluster(cluster, virus.pos, 2);
	}
}

void Day22::NextBurstPart2(std::vector<std::vector<State>>& cluster, std::vector<std::pair<int, int>> directions, Virus & virus, int & infectionsCont) {
	bool turnsToRight;
	//infects or clean and turn right or left
	if (CheckState(cluster, virus.pos, CLEAN)) {
		turnsToRight = false;
		ChangeState(cluster, virus.pos, State::WEAKENED);

		//update virus
		virus.currentDirIndex = TurnSides(virus.currentDirIndex, turnsToRight);
	} else if (CheckState(cluster, virus.pos, WEAKENED)) {
		ChangeState(cluster, virus.pos, State::INFECTED);
		infectionsCont++;
		//Not turn
	} else if (CheckState(cluster, virus.pos, INFECTED)) {
		turnsToRight = true;
		ChangeState(cluster, virus.pos, State::FLAGGED);

		//update virus
		virus.currentDirIndex = TurnSides(virus.currentDirIndex, turnsToRight);
	} else { //FLAGGED
		turnsToRight = true;
		ChangeState(cluster, virus.pos, State::CLEAN); //infects node
		virus.currentDirIndex = TurnSides(virus.currentDirIndex, turnsToRight); //Reverse direction
		virus.currentDirIndex = TurnSides(virus.currentDirIndex, turnsToRight);
	}

	//Moves in the new direction
	auto newDir = directions[virus.currentDirIndex];
	virus.pos.first = virus.pos.first + newDir.first;
	virus.pos.second = virus.pos.second + newDir.second;

	//check bounds and extend if necesary
	if (CheckOutOfBounds(cluster, virus.pos)) {
		ExtendCluster(cluster, virus.pos, 2);
	}
}

bool Day22::CheckState(std::vector<std::vector<State>>& cluster, std::pair<int, int> pos, State stateToCheck) {
	return cluster[pos.first][pos.second] == stateToCheck;
}

void Day22::ChangeState(std::vector<std::vector<State>>& cluster, std::pair<int, int> pos, State nextState) {
	cluster[pos.first][pos.second] = nextState;
}

int Day22::TurnSides(int currentDirectionIndex, bool turnToRight) {
	int nextIndex = (currentDirectionIndex + (turnToRight ? 1 : -1)) % 4;
	if (nextIndex < 0) {
		nextIndex = 3; //the direction is the last one (position 3 of directions)
	}
	return nextIndex;
}

bool Day22::CheckOutOfBounds(std::vector<std::vector<State>>& cluster, std::pair<int, int> position) {
	return position.first < 0 || position.first >= cluster.size() || position.second < 0 || position.second >= cluster[0].size();
}

void Day22::ExtendCluster(std::vector<std::vector<State>>& cluster, std::pair<int, int>& position, int increaseBy) {
	std::vector<std::vector<State>> newCluster(cluster.size() + increaseBy * 2, std::vector<State>(cluster[0].size() + increaseBy * 2, State::CLEAN));

	//Populate newCluster
	int increaseSide = increaseBy;
	for (int i = increaseSide; i < increaseSide + cluster.size(); i++) {
		for (int j = increaseSide; j < increaseSide + cluster[0].size(); j++) {
			newCluster[i][j] = cluster[i - increaseSide][j - increaseSide];
		}
	}
	//Update position
	position.first += increaseSide;
	position.second += increaseSide;

	cluster = newCluster;
}
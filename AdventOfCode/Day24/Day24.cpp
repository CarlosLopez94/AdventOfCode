#include "Day24.h"
#include "../Util.h"
#include "iostream"
#include "algorithm"

int Day24::Main() {
	std::cout << "Day 24 - Part 1" << std::endl;
	std::vector<std::string> input = Util::ReadFile("../AdventOfCode/Day24/input.txt");

	//Init Bridges
	std::vector<Bridge> bridges;
	InitBridges(bridges, input);

	int weight = GetMaximumWeight(bridges);
	std::cout << "The maximum weight is: " << weight << std::endl;

	std::cout << "Part 2" << std::endl;
	LonguestBridge longuestWeight = GetWeightOfLongestBridge(bridges);
	std::cout << "The weight of the longuest bridge (" << longuestWeight.size << ") is: " << longuestWeight.weight << std::endl;
	PrintBridges(longuestWeight.bridgeComponents);
	return 0;
}

void Day24::InitBridges(std::vector<Bridge>& bridges, std::vector<std::string> input) {
	for (std::string line : input) {
		auto tokens = Util::Split(line, "/");
		int n0 = std::stoi(tokens[0]);
		int n1 = std::stoi(tokens[1]);

		//Add the same component in both sides
		bridges.push_back(std::make_pair(n0, n1));
		bridges.push_back(std::make_pair(n1, n0));
	}
}

int Day24::GetMaximumWeight(std::vector<Bridge> bridges) {
	if (bridges.empty()) {
		return 0;
	} else {
		return GetMaximumWeightAux(bridges, std::make_pair(0, 0));
	}
}

int Day24::GetMaximumWeightAux(std::vector<Bridge> bridges, Bridge currentBridge) {
	int weight = GetWeight(currentBridge);
	RemoveUsedBridge(bridges, currentBridge);
	if (!bridges.empty()) {
		int maxWeight = 0;
		for (Bridge candidate : GetPossibleConnections(bridges, currentBridge)) {
			int weightCandidate = GetMaximumWeightAux(bridges, candidate);
			if (weightCandidate > maxWeight) {
				maxWeight = weightCandidate;
			}
		}
		weight = weight + maxWeight;
	}
	return weight;
}

Day24::LonguestBridge Day24::GetWeightOfLongestBridge(std::vector<Bridge> bridges) {
	LonguestBridge longuestBridge = LonguestBridge(0, 0);
	return GetWeightOfLongestBridgeAux(bridges, Bridge(0, 0), 1);
}

Day24::LonguestBridge Day24::GetWeightOfLongestBridgeAux(std::vector<Bridge> bridges, Bridge currentBridge, int bridgeSize) {
	LonguestBridge longuestBridge = LonguestBridge(GetWeight(currentBridge), bridgeSize, currentBridge);
	RemoveUsedBridge(bridges, currentBridge);
	if (!bridges.empty()) {
		LonguestBridge longuestCandidate(0, bridgeSize);
		for (Bridge candidate : GetPossibleConnections(bridges, currentBridge)) {
			auto longuestCandidateNextStep = GetWeightOfLongestBridgeAux(bridges, candidate, bridgeSize + 1);
			if (longuestCandidate.size < longuestCandidateNextStep.size || (longuestCandidate.size == longuestCandidateNextStep.size && longuestCandidate.weight < longuestCandidateNextStep.weight)) {
				longuestCandidate = longuestCandidateNextStep;
			}
		}
		longuestBridge.weight += longuestCandidate.weight;
		longuestBridge.size = longuestCandidate.size;
		longuestBridge.bridgeComponents.insert(longuestBridge.bridgeComponents.end(), longuestCandidate.bridgeComponents.begin(), longuestCandidate.bridgeComponents.end());
	}

	return longuestBridge;
}

std::vector<std::pair<int, int>> Day24::GetPossibleConnections(std::vector<Bridge>& bridges, Bridge& currentBridge) {
	std::vector<Bridge>  connections;
	for (Bridge bridgeCandidate : bridges) {
		if (currentBridge.second == bridgeCandidate.first) { //if they connect
			connections.push_back(bridgeCandidate);
		}
	}
	return connections;
}

void Day24::RemoveUsedBridge(std::vector<Bridge>& bridges, Bridge& usedBridge) {
	//When a bridge is used, we delete it and the same swapped bridge 
	bridges.erase(std::remove(bridges.begin(), bridges.end(), usedBridge), bridges.end());

	//delete the swap bridge
	Bridge swapUsedBridge = std::make_pair(usedBridge.second, usedBridge.first);
	bridges.erase(std::remove(bridges.begin(), bridges.end(), swapUsedBridge), bridges.end());
}

int Day24::GetWeight(Bridge bridge) {
	return bridge.first + bridge.second;
}

void Day24::PrintBridges(std::vector<Bridge> bridges) {
	for (int i = 0; i < bridges.size(); i++) {
		std::cout << "[" << bridges[i].first << "/" << bridges[i].second << "]";
		if (i != bridges.size() - 1) {
			std::cout << "--";
		}
	}
	std::cout << std::endl;
}

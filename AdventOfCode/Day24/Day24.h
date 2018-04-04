#pragma once
#include "utility"
#include "vector"
#include "string"

typedef std::pair<int, int> Bridge;

class Day24
{
public:
	int Main();
private:
	struct LonguestBridge {
		int weight = 0;
		int size = 0;
		std::vector<Bridge> bridgeComponents;

		LonguestBridge(int weight, int size) {
			this->weight = weight;
			this->size = size;
		}

		LonguestBridge(int weight, int size, Bridge bridge) {
			this->weight = weight;
			this->size = size;
			bridgeComponents.push_back(bridge);
		}
	};

	void InitBridges(std::vector<Bridge>& bridges, std::vector<std::string> input);

	int GetMaximumWeight(std::vector<std::pair<int, int>> bridges);
	int GetMaximumWeightAux(std::vector<Bridge> bridges, Bridge currentBridge);

	LonguestBridge GetWeightOfLongestBridge(std::vector<Bridge> bridges);
	LonguestBridge GetWeightOfLongestBridgeAux(std::vector<Bridge> bridges, Bridge currentBridge, int bridgeSize);

	std::vector<std::pair<int, int>> GetPossibleConnections(std::vector<Bridge>& bridges, Bridge& currentBridge);
	void RemoveUsedBridge(std::vector<Bridge>& bridges, Bridge& usedBridge);

	int GetWeight(Bridge bridge);

	void PrintBridges(std::vector<Bridge> bridges);
};


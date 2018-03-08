#pragma once

#include "vector"
#include "string"
#include "map"

class Day13
{
	struct ScannerInfo {
		int range;
		int currentPos;
		bool toBottom;
	};

public:
	int Main();
private:
	void InitScanners(std::vector<std::string> input, std::map<int, Day13::ScannerInfo>& scannersInfo, std::vector<std::vector<int>>& scanners);
	int GetSeverity(std::map<int, Day13::ScannerInfo> scannersInfo, std::vector<std::vector<int>> scanners);
	int GetStepsDelayToNotGetCaught(std::map<int, Day13::ScannerInfo> scannersInfo, std::vector<std::vector<int>> scanners);
	bool GetStepsDelayToNotGetCaughtAux(std::map<int, Day13::ScannerInfo> scannersInfo, std::vector<std::vector<int>> scanners);

	void MoveScanners(std::vector<std::vector<int>>& scanners, std::map<int, ScannerInfo>& scannersInfo);
	bool CheckCaught(std::vector<std::vector<int>> scanners, int pos);
	void PrintScanners(std::vector<std::vector<int>> scanners, int pos);
};


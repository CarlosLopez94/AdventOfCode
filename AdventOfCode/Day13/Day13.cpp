#include "Day13.h"
#include "../Util.h"
#include "utility"
#include "iostream"
#include "vector"
#include "string"
#include "fstream"
#include "map"

class Day13::ScannerInfo;

int Day13::Main() {
	std::cout << "Day 13 - Part 1 " << std::endl;
	std::vector<std::string> input = Util::ReadFile("../AdventOfCode/Day13/input.txt");

	std::map<int, Day13::ScannerInfo> scannersInfo;
	std::vector<std::vector<int>> scanners;
	InitScanners(input, scannersInfo, scanners);

	std::cout << "Initial:" << std::endl;
	PrintScanners(scanners, 0);
	std::cout << "_____________________________________________________" << std::endl;

	int severity = GetSeverity(scannersInfo, scanners);
	std::cout << "The severity is: " << severity << std::endl;

	//Part 2
	std::cout << "Part 2" << std::endl;
	int stepsDelay = GetStepsDelayToNotGetCaught(scannersInfo, scanners);
	std::cout << "The fewest number of steps to delay to not get caught is: " << stepsDelay << std::endl;


	return 0;
}

void Day13::InitScanners(std::vector<std::string> input, std::map<int, Day13::ScannerInfo>& scannersInfoReturn, std::vector<std::vector<int>>& scannersReturn) {
	//Get the scanners dimension
	int greaterDepth = 0;
	int greaterRange = 0;
	for (std::string line : input) {
		std::vector<std::string> splitted = Util::Split(line, ": ");
		int depth = stoi(splitted[0]);
		int range = stoi(splitted[1]);
		struct Day13::ScannerInfo info = ScannerInfo();
		std::cout << &info << std::endl;
		info.range = range;
		info.currentPos = 0; //scanners start at 0
		info.toBottom = true; //at the start they go from top to bottom
		scannersInfoReturn[depth] = info; //depth -> (range, currentPos, toBottom)

		if (depth > greaterDepth) {
			greaterDepth = depth;
		}
		if (range > greaterRange) {
			greaterRange = range; //check if necessary
		}
	}
	greaterDepth++; //the input start at 0

					//Create the scanners
	std::vector<std::vector<int>> scanners(greaterDepth, std::vector<int>(greaterRange, 0));
	for (int i = 0; i < greaterDepth; i++) {
		if (scannersInfoReturn.find(i) != scannersInfoReturn.end()) {
			for (int j = 0; j < scannersInfoReturn[i].range; j++) {
				if (j == 0) {
					scanners[i][j] = 2;
				} else {
					scanners[i][j] = 1;
				}
			}
		}
	}
	scannersReturn = scanners;
}

int Day13::GetSeverity(std::map<int, Day13::ScannerInfo> scannersInfo, std::vector<std::vector<int>> scanners) {
	int severity = 0;
	//Try to pass the firewall!
	for (int position = 0; position < scanners.size(); position++) {
		//Move position ('position' variable)
		//std::cout << "Picosecond " << position << " - 0" << std::endl;
		//PrintScanners(scanners, position);
		//Check if caught
		if (CheckCaught(scanners, position)) {
			severity += position * scannersInfo[position].range; //depth*range
		}

		//Move scanners
		MoveScanners(scanners, scannersInfo);
		//Print state
		//std::cout << "_____________________________________________________" << severity << std::endl;
		//std::cout << "Picosecond " << position << " - 1" << std::endl;

		//	PrintScanners(scanners, position);
		//std::cout << "_____________________________________________________" << severity << std::endl;
	}
	return severity;
}

int Day13::GetStepsDelayToNotGetCaught(std::map<int, Day13::ScannerInfo> scannersInfo, std::vector<std::vector<int>> scanners) {
	//This takes a lot of time, its needs to improve
	int delaySteps = 0;
	bool isCaught = true;

	while (isCaught) {
		isCaught = GetStepsDelayToNotGetCaughtAux(scannersInfo, scanners);
		if (isCaught) {
			delaySteps++;
			MoveScanners(scanners, scannersInfo);
		}
	}

	return delaySteps;
}


bool Day13::GetStepsDelayToNotGetCaughtAux(std::map<int, Day13::ScannerInfo> scannersInfo, std::vector<std::vector<int>> scanners) {
	bool isCaught = false;
	//Try to pass the firewall!
	for (int position = 0; !isCaught && position < scanners.size(); position++) {
		//Move position ('position' variable)

		//Check if caught
		isCaught = CheckCaught(scanners, position);

		//Move scanners
		MoveScanners(scanners, scannersInfo);
	}
	return isCaught;
}

void Day13::MoveScanners(std::vector<std::vector<int>>& scanners, std::map<int, ScannerInfo>& scannersInfo) {
	for (int i = 0; i < scanners.size(); i++) {
		if (scannersInfo.find(i) != scannersInfo.end()) { //this scanners has info! its not empty
			ScannerInfo info = scannersInfo[i];
			//set the last position to 1 and the new to 2
			scanners[i][info.currentPos] = 1;
			if (info.toBottom) {
				info.currentPos = info.currentPos + 1;
			} else {
				info.currentPos = info.currentPos - 1;
			}
			scanners[i][info.currentPos] = 2;

			//Change mode of scanner (top to bottom or bottom to top)
			if (info.currentPos == 0 || info.currentPos >= info.range - 1) {
				info.toBottom = !info.toBottom;
			}
			scannersInfo[i] = info;
		}
	}
}

bool Day13::CheckCaught(std::vector<std::vector<int>> scanners, int pos) {
	return scanners[pos][0] == 2;
}

/*
0 --> empty ...
1 --> scanner NO active [ ]
2 --> scanner active [S]
the position 'pos' is represented by '( )'
*/
void Day13::PrintScanners(std::vector<std::vector<int>> scanners, int pos) {
	for (int i = 0; i < scanners.size(); i++) {
		std::cout << "    " << i << "\t--> ";
		for (int j = 0; j < scanners[0].size(); j++) {
			int cell = scanners[i][j];
			if (cell == 0) {
				if (i != pos || j != 0) {
					std::cout << "...";
				} else {
					std::cout << "(.)";
				}
			} else if (cell == 1) {
				if (i != pos || j != 0) {
					std::cout << "[ ]";
				} else {
					std::cout << "( )";
				}
			} else if (cell == 2) {
				if (i != pos || j != 0) {
					std::cout << "[S]";
				} else {
					std::cout << "(S)";
				}
			}
			std::cout << "  ";
		}
		std::cout << std::endl;
	}
}

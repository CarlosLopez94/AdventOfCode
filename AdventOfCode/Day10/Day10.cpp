#include "Day10.h"
#include "../Util.h"
#include "iostream"
#include "fstream"

int Day10::Main() {
	const int LIST_LENGTH = 256;
	std::cout << "Day 10 - Part 1" << std::endl;
	std::vector<std::string> lines = Util::ReadFile("../AdventOfCode/Day10/input.txt");
	//Convert input to int vector
	std::vector<int> input;
	for (std::string line : lines) {
		auto tokens = Util::Split(line, ",");
		for (auto token : tokens) {
			input.push_back(stoi(token));
		}
	}

	std::vector<int> circularList = InitCircularList(LIST_LENGTH);
	PrintVector(circularList, 0, circularList.size());

	//Consume input and reverse the circular list
	ApplyInputToCircularList(circularList, input, 1);
	std::cout << "Result of multyplying the first two numbers of the list: " << CheckCorrectOrder(circularList) << std::endl;


	std::cout << "Part 2" << std::endl;
	//Read input as ascii
	std::vector<int> inputAscii;
	for (std::string line : lines) {
		for (char c : line) {
			inputAscii.push_back((int)c);
		}
	}
	//Add the sequence at the end
	std::vector<std::string> sequence = Util::ReadFile("../AdventOfCode/Day10/sequence.txt");
	for (auto sequenceLine : sequence) {
		auto seqTokens = Util::Split(sequenceLine, ", ");
		for (auto seqToken : seqTokens) {
			inputAscii.push_back(stoi(seqToken));
		}
	}
	std::vector<int> sparsheHash = InitCircularList(256);
	//Calculate the sparseHash
	ApplyInputToCircularList(sparsheHash, inputAscii, 64); //64 rounds
	std::vector<int> denseHash = GetDenseHash(sparsheHash);
	std::string knotHash = ParseDenseHashToHexadecimalString(denseHash);
	std::cout << "The knot hash is: " << knotHash << std::endl;
	return 0;
}

void Day10::PrintVector(std::vector<int> vector, int currentPos, int posToReverse) {
	for (int i = 0; i < vector.size(); i++) {
		if (i == currentPos) {
			std::cout << "([" << vector[i] << "]";
		} else {
			std::cout << vector[i];
		}

		if (i == posToReverse - 1) {
			std::cout << ")";
		}
		std::cout << "\t";
	}
	std::cout << std::endl;
}

void Day10::ApplyInputToCircularList(std::vector<int>& circularList, std::vector<int> input, int roundsNumber) {
	int currentPos = 0;
	int skipSize = 0;
	for (int i = 0; i < roundsNumber; i++) {
		for (int number : input) {
			ReverseCircularList(circularList, currentPos, number);
			//PrintVector(circularList, currentPos, number);
			currentPos = (currentPos + number + skipSize) % circularList.size();
			skipSize++;
		}
	}
}

std::vector<int> Day10::InitCircularList(int length) {
	std::vector<int> circularList;
	for (int i = 0; i < length; i++) {
		circularList.push_back(i);
	}
	return circularList;
}

template<typename T>
void Day10::ReverseCircularList(std::vector<T>& list, int currentPos, int posToReverse) {
	for (int i = 0; i < posToReverse / 2; i++) {
		int auxSwap = list[(currentPos + i) % list.size()];
		list[(currentPos + i) % list.size()] = list[(currentPos + (posToReverse - 1 - i)) % list.size()];
		list[(currentPos + (posToReverse - 1 - i)) % list.size()] = auxSwap;
	}
}

int Day10::CheckCorrectOrder(std::vector<int> list) {
	return list[0] * list[1]; //multiply numbers of two first positions
}

std::vector<int> Day10::GetDenseHash(std::vector<int> sparseHash) {
	std::vector<int> denseHash;
	int blockSize = 16;
	int origin = 0;
	int destiny = blockSize;
	while (destiny <= sparseHash.size()) {
		int xorValue = sparseHash[origin];
		for (int i = origin + 1; i < destiny; i++) {
			xorValue = xorValue ^ sparseHash[i];
		}
		denseHash.push_back(xorValue);
		origin += blockSize;
		destiny += blockSize;
	}

	return denseHash;
}

std::string Day10::ParseDenseHashToHexadecimalString(std::vector<int> sparseHash) {
	std::string knotHash;

	for (int toHex : sparseHash) {
		knotHash += Util::ParseDecimalToHex(toHex);
	}

	return knotHash;
}
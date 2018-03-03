#include "Day10.h"
#include "iostream"
#include "fstream"

int Day10::Main() {
	const int LIST_LENGTH = 256;
	std::cout << "Day 10 - Part 1" << std::endl;
	std::vector<std::string> lines = ReadFile("../AdventOfCode/Day10/input.txt");
	//Convert input to int vector
	std::vector<int> input;
	for (std::string line : lines) {
		auto tokens = Split(line, ",");
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
	std::vector<std::string> sequence = ReadFile("../AdventOfCode/Day10/sequence.txt");
	for (auto sequenceLine : sequence) {
		auto seqTokens = Split(sequenceLine, ", ");
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

std::vector<std::string> Day10::ReadFile(std::string fileName) {
	std::vector<std::string> lines;
	std::string line;
	std::ifstream myfile(fileName);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			lines.push_back(line);

		}
		myfile.close();
	} else {
		std::cout << "Unable to open file\n";
	}
	return lines;
}

std::vector<std::string> Day10::Split(std::string stringToSplit, std::string separator) {
	std::vector<std::string> tokens;
	std::string stringAux = stringToSplit;
	int indexNextToken = 0;
	while (indexNextToken > -1 && indexNextToken < stringToSplit.size()) {
		indexNextToken = stringAux.find(separator);
		if (indexNextToken != -1) {
			tokens.push_back(stringAux.substr(0, indexNextToken));
			stringAux = stringAux.substr(indexNextToken + separator.size(), stringToSplit.size());//we have to jump the separator
		} else {
			tokens.push_back(stringAux);
		}
	}
	return tokens;
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

//Parse from Decimal to Hexadecimal. The hex value always has AT LEAST two digits
std::string Day10::ParseDecimalToHex(int decimal) {
	int const HEX = 16;
	std::string hexNumber = "";
	std::string hexAlphabet = "0123456789abcdef";
	int decimalAux = decimal;
	do {
		int remainder = decimalAux % HEX;
		hexNumber = hexAlphabet[remainder] + hexNumber;
		decimalAux = decimalAux / HEX;
	} while (decimalAux > 0);

	//if the num only has one digits, add a left 0 
	if (hexNumber.size() == 1) {
		hexNumber = "0" + hexNumber;
	}
	return hexNumber;
}

std::string Day10::ParseDenseHashToHexadecimalString(std::vector<int> sparseHash) {
	std::string knotHash;

	for (int toHex : sparseHash) {
		knotHash += ParseDecimalToHex(toHex);
	}

	return knotHash;
}
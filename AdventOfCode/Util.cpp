#include "Util.h"
#include "iostream"
#include "fstream"

namespace Util {

	std::vector<std::string> Util::ReadFile(std::string fileName) {
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

	std::string Util::ReadFileSingleLine(std::string fileName) {
		std::string lineResult = "";
		std::string line;
		std::ifstream myfile(fileName);
		if (myfile.is_open()) {
			while (getline(myfile, line)) {
				lineResult += line;
			}
			myfile.close();
		} else {
			std::cout << "Unable to open file\n";
		}
		return lineResult;
	}

	std::vector<std::string> Split(std::string stringToSplit, std::string separator) {
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

	int Util::ManhattanDistance(int origenX, int originY, int destinyX, int destinyY) {
		return abs(destinyX - origenX) + abs(destinyY - originY);
	}

	//Parse from Decimal to Hexadecimal. The hex value always has AT LEAST two digits
	std::string Util::ParseDecimalToHex(int decimal) {
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

	//Prints
	void Util::PrintMatrix(std::vector<std::vector<int>> vector) {
		for (unsigned i = 0; i < vector.size(); i++) {
			for (unsigned j = 0; j < vector[0].size(); j++) {
				std::cout << vector[i][j] << '\t';
			}
			std::cout << std::endl;
		}
	}

	void Util::PrintVector(std::vector<int> vector) {
		for (unsigned i = 0; i < vector.size(); i++) {
			std::cout << vector[i] << "  ";
		}
		std::cout << std::endl;
	}

	void Util::PrintVector(std::vector<int> vector, int currentPos) {
		for (unsigned i = 0; i < vector.size(); i++) {
			if (i == currentPos) {
				std::cout << '(' << vector[i] << ") ";
			} else {
				std::cout << ' ' << vector[i] << "  ";
			}
		}
		std::cout << std::endl;
	}

	void Util::PrintQueue(std::queue<char> queue) {
		while (!queue.empty()) {
			std::cout << queue.front();
			queue.pop();
		}
		std::cout << std::endl;
	}

	void Util::PrintSet(std::set<int> setToPrint) {
		auto it = setToPrint.begin();
		while (it != setToPrint.end()) {
			std::cout << *it;
			it++;
			//Check if we need ,
			if (it != setToPrint.end()) {
				std::cout << ", ";
			} else {
				std::cout << std::endl;
			}
		}
	}
}
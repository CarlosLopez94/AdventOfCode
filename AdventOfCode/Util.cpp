#include "Util.h"
#include "iostream"
#include "fstream"
#include "sstream"
#include "bitset"

namespace Util {

	std::vector<std::string> ReadFile(std::string fileName) {
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

	std::string ReadFileSingleLine(std::string fileName) {
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
			indexNextToken = (int)stringAux.find(separator);
			if (indexNextToken != -1) {
				tokens.push_back(stringAux.substr(0, indexNextToken));
				stringAux = stringAux.substr(indexNextToken + separator.size(), stringToSplit.size());//we have to jump the separator
			} else {
				tokens.push_back(stringAux);
			}
		}
		return tokens;
	}

	int ManhattanDistance(int origenX, int originY, int destinyX, int destinyY) {
		return abs(destinyX - origenX) + abs(destinyY - originY);
	}

	//Parse from Decimal to Hexadecimal. The hex value always has AT LEAST two digits
	std::string ParseDecimalToHex(int decimal) {
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

	//Parse from Hex to binary. 
	std::string HexToBinary(std::string hex) {
		unsigned int intVaule;
		std::stringstream ss;
		ss << std::hex << hex;
		ss >> intVaule;

		std::bitset<4> b(intVaule);
		//std::cout << b;
		return b.to_string();
	}

	int HexToDecimal(std::string hex) {
		std::istringstream iss(hex);
		int decimalNumber;
		iss >> std::hex >> decimalNumber;

		return decimalNumber;
	}

	std::string DecimalToBinary(int_fast64_t decimal) {
		std::string binary = "";

		while (decimal >= 2) {
			binary = std::to_string(decimal % 2) + binary;
			decimal = decimal / 2;
		}
		binary = std::to_string(decimal) + binary;
		return binary;
	}

	std::string PaddingToLeft(std::string originalChain, std::string stringToAdd, int lengthToMatch) {
		while (originalChain.size() < lengthToMatch) {
			originalChain = stringToAdd + originalChain;
		}
		return originalChain;
	}

	bool IsAlphabetic(char ch) {
		bool isAlphabetic = false;
		if ((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A')) {
			isAlphabetic = true;
		}
		return isAlphabetic;
	}
}
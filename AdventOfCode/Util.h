#pragma once

#include "vector"
#include "string"
#include "queue"
#include "set"

namespace Util {
	std::vector<std::string> ReadFile(std::string fileName);
	std::string ReadFileSingleLine(std::string fileName);
	std::vector<std::string> Split(std::string stringToSplit, std::string separator);


	int ManhattanDistance(int origenX, int originY, int destinyX, int destinyY);
	std::string ParseDecimalToHex(int decimal);
	std::string HexToBinary(std::string hex);
	int HexToDecimal(std::string hex);
	std::string DecimalToBinary(int_fast64_t decimal);
	std::string PaddingToLeft(std::string originalChain, std::string stringToAdd, int lengthToMatch);

	//Prints
	void PrintMatrix(std::vector<std::vector<int>> vector);
	void PrintVector(std::vector<int> vector);
	void PrintVector(std::vector<int> vector, int currentPos);
	void PrintQueue(std::queue<char> stack);
	void PrintSet(std::set<int> setToPrint);
}
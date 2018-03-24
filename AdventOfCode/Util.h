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
	bool IsAlphabetic(char ch);

	//Util templates implementation
	template<typename T>
	void Swap(std::vector<T>& vector, int swapIndex1, int swapIndex2) {
		T aux = vector[swapIndex1];
		vector[swapIndex1] = vector[swapIndex2];
		vector[swapIndex2] = aux;
	}

	template<typename T>
	int IndexOfValue(std::vector<T> vector, char value) {
		int i = 0;
		bool found = false;
		while (!found && i < vector.size()) {
			if (vector[i] == value) {
				found = true;
			} else {
				i++;
			}
		}
		return found ? i : -1;
	}

	template<typename T1, typename T2>
	std::pair<T1, T2> AddToPair(std::pair<T1, T2> pair1, std::pair<T1, T2> pair2) {
		std::pair<T1, T2> result = std::make_pair(pair1.first + pair2.first, pair1.second + pair2.second);
		return result;
	}
	template<typename T>
	void RotateMatrix(std::vector<std::vector<T>>& pattern) {
		std::vector<std::vector<T>> rotated(pattern.size(), std::vector<T>(pattern.size(), ' '));

		for (int i = 0; i < rotated.size(); i++) {
			for (int j = 0; j < rotated.size(); j++) {
				rotated[rotated.size() - 1 - j][i] = pattern[i][j];
			}
		}
		pattern = rotated;
	}

	template<typename T>
	void FlipMatrix(std::vector<std::vector<T>>& pattern) {
		for (int i = 0; i < pattern.size(); i++) {
			for (int j = 0; j < pattern.size() / 2; j++) {
				auto temp = pattern[i][j];
				pattern[i][j] = pattern[i][pattern.size() - 1 - j];
				pattern[i][pattern.size() - 1 - j] = temp;
			}
		}
	}

	template<typename T1, typename T2>
	void PrintPair(std::pair<T1, T2> pair) {
		std::cout << '(' << pair.first << ',' << pair.second << ')';
	}

	template<typename T>
	void PrintMatrix(std::vector<std::vector<T>> vector) {
		for (unsigned i = 0; i < vector.size(); i++) {
			for (unsigned j = 0; j < vector[0].size(); j++) {
				std::cout << vector[i][j] << '\t';
			}
			std::cout << std::endl;
		}
	}

	template<typename T>
	void PrintVector(std::vector<T> vector) {
		for (unsigned i = 0; i < vector.size(); i++) {
			std::cout << vector[i] << "  ";
		}
		std::cout << std::endl;
	}

	template<typename T>
	void PrintVector(std::vector<T> vector, int currentPos) {
		for (unsigned i = 0; i < vector.size(); i++) {
			if (i == currentPos) {
				std::cout << '(' << vector[i] << ") ";
			} else {
				std::cout << ' ' << vector[i] << "  ";
			}
		}
		std::cout << std::endl;
	}

	template<typename T>
	void PrintQueue(std::queue<T> queue) {
		while (!queue.empty()) {
			std::cout << queue.front();
			queue.pop();
		}
		std::cout << std::endl;
	}

	template<typename T>
	void PrintSet(std::set<T> setToPrint) {
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
#include "Day2.h"
#include "../Util.h"
#include "string"
#include <algorithm>    // std::sort
#include <sstream>

int Day2::Main() {
	const unsigned NUMBER_ROWS = 16;
	const unsigned NUMBER_COLUMNS = 16;
	std::string input = Util::ReadFileSingleLine("../AdventOfCode/Day2/input.txt");
	std::vector<std::vector<int>> numbers = ReadAsMatrix(input, NUMBER_ROWS, NUMBER_COLUMNS);
	std::cout << "Day2!! Your Input is: " << std::endl;
	Util::PrintMatrix(numbers);

	//Part 1
	int checkSum = 0;
	for (unsigned i = 0; i < numbers.size(); i++) {
		checkSum += ChecksumRow(numbers, i);
	}
	std::cout << "\n\nPart 1. CheckSum is: " << checkSum;

	//Part 2
	int evenlyDivisorsSum = 0;
	for (unsigned i = 0; i < numbers.size(); i++) {
		evenlyDivisorsSum += DivideEvenlyRow(numbers, i);
	}
	std::cout << "\n\nPart 2. Sum of evenly divisors is: " << evenlyDivisorsSum << std::endl;

	return 0;
}


std::vector<std::vector<int>> Day2::ReadAsMatrix(std::string input, const int rowNumber, const int columnNumber) {
	std::vector<std::vector<int>> matrix(rowNumber, std::vector<int>(columnNumber));
	std::string nextToken = "";
	int currentRow = 0;
	int currentColumn = 0;
	for (unsigned i = 0; i < input.length(); i++) {
		if (input[i] != ' ') {
			nextToken += input[i];
		} else if (nextToken != "") {

			matrix[currentRow][currentColumn] = std::atoi(nextToken.c_str());
			nextToken = "";

			currentColumn++;
			if (currentColumn >= columnNumber) {
				currentColumn = 0;
				currentRow++;
			}
		}
	}
	return matrix;
}

int Day2::ChecksumRow(std::vector<std::vector<int>> vector, int row) {
	int min = vector[row][0];
	int max = vector[row][0];

	for (unsigned i = 0; i < vector[row].size(); i++) {
		int currentValue = vector[row][i];
		if (currentValue < min) {
			min = currentValue;
		}
		if (currentValue > max) {
			max = currentValue;
		}
	}
	return max - min;
}

int Day2::DivideEvenlyRow(std::vector<std::vector<int>> vector, int row) {
	//First sort the vector
	std::sort(vector[row].begin(), vector[row].end());

	int division = 0;
	bool found = false;
	for (unsigned i = 0; !found && i < vector[row].size(); i++) { //the last one is the greater, cant divide any number
		for (unsigned j = i + 1; !found && j < vector[row].size(); j++) {
			if (vector[row][i]!=0 && vector[row][j] % vector[row][i] == 0) {
				division = vector[row][j] / vector[row][i];
				found = true;
			}
		}
	}
	return division;
}


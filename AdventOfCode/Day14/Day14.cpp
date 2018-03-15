#include "Day14.h"
#include "../Day10/Day10.h"
#include "../Util.h"
#include "iostream"

int Day14::Main() {
	std::cout << "Day 14 - Part 1" << std::endl;
	std::string input = Util::ReadFileSingleLine("../AdventOfCode/Day14/input.txt");

	std::vector<std::vector<char>> squares = ConstructSquare(input);
	int usedSquares = GetUsedSquares(squares);
	std::cout << "The number of used squares is: " << usedSquares << std::endl;
	//Part 2
	std::cout << "Part 2" << std::endl;
	int regionSum = GetRegionNumber(squares);
	std::cout << "The regions number is: " << regionSum << std::endl;

	return 0;
}

std::vector<std::vector<char>> Day14::ConstructSquare(std::string input) {
	const int DIMENSION = 128;
	std::vector<std::vector<char>> squares(DIMENSION, std::vector<char>(DIMENSION, '0'));
	std::string sequence = Util::ReadFileSingleLine("../AdventOfCode/Day14/sequence.txt");
	for (int i = 0; i < DIMENSION; i++) {
		ConstructSquareRow(squares, input, i, sequence);
	}
	return squares;
}

void Day14::ConstructSquareRow(std::vector<std::vector<char>>& squares, std::string key, int row, std::string sequence) {
	//key + '-' + rowNumber + endSequence
	std::string keyRow = key + '-' + std::to_string(row);

	//pass to ascii
	std::vector<int> keyAscii;
	for (char c : keyRow) {
		keyAscii.push_back((int)c);
	}

	for (std::string token : Util::Split(sequence, ",")) {
		keyAscii.push_back(stoi(token));
	}


	Day10 day10;
	std::vector<int> sparsheHash = day10.InitCircularList(256);
	//Calculate the sparseHash
	day10.ApplyInputToCircularList(sparsheHash, keyAscii, 64); //64 rounds
	std::vector<int> denseHash = day10.GetDenseHash(sparsheHash);
	std::string knotHash = day10.ParseDenseHashToHexadecimalString(denseHash);
	//std::cout << knotHash << std::endl;
	std::string hexAux;
	int binaryCount = 0;
	for (int i = 0; i < knotHash.size(); i++) {
		char charAuxDeleteMe = knotHash.at(i);
		hexAux = Util::HexToBinary(std::string(1, knotHash.at(i)));

		for (char c : hexAux) {
			squares[row][binaryCount] = c;
			if (c == '0') {
				//std::cout << '.';
			} else if (c == '1') {
				//std::cout << '#';
			}
			binaryCount++;
		}
	}
	//std::cout << std::endl;
}

int Day14::GetUsedSquares(std::vector<std::vector<char>> squares) {
	int usedSquares = 0;
	std::string square;
	for (int i = 0; i < squares.size(); i++) {
		for (int j = 0; j < squares.size(); j++) {
			square = squares[i][j];
			for (char s : square) {
				if (s == '1') {
					usedSquares++;
				}
			}
		}
	}
	return usedSquares;
}

int Day14::GetRegionNumber(std::vector<std::vector<char>> squares) {
	const int DIMENSION = 128;
	std::vector<std::vector<int>> regions(DIMENSION, std::vector<int>(DIMENSION, 0)); //-1 is '.'
	int regionsNumber = 1;
	for (int i = 0; i < squares.size(); i++) {
		for (int j = 0; j < squares[0].size(); j++) {
			if (regions[i][j] == 0 && squares[i][j] == '1') {//not full yet and its not free
				CompleteRegion(squares, regions, regionsNumber, i, j);
				regionsNumber++;
				std::cout << "Calculating regionsNumber... (" << regionsNumber <<")"<< std::endl;
			}
		}
	}
	regionsNumber--;
	return regionsNumber;
}

void Day14::CompleteRegion(std::vector<std::vector<char>> squares, std::vector<std::vector<int>>& regions, int currentRegionValue, int row, int column) {
	if (row >= 0 && row < squares.size() && column >= 0 && column < squares[0].size()) {//check bounds
		if (regions[row][column] == 0 && squares[row][column] == '1') { //check is not a free square and it wasnt visited yet
			//update this square
			regions[row][column] = currentRegionValue;

			//Check adyacents
			CompleteRegion(squares, regions, currentRegionValue, row -1, column); //top
			CompleteRegion(squares, regions, currentRegionValue, row, column - 1); //left
			CompleteRegion(squares, regions, currentRegionValue, row, column + 1); //right
			CompleteRegion(squares, regions, currentRegionValue, row + 1, column); //bottom
		}
	}
}
#include "Day3.h"
#include "../Util.h"
#include "iostream"
#include "stdlib.h"

int Day3::Main() {
	int input = stoi(Util::ReadFileSingleLine("../AdventOfCode/Day3/input.txt")); 277678;
	std::cout << "Day 3 - Part 1. Your input is " << input << std::endl;

	int dimension = CalculateVectorDimension(input);

	std::vector<std::vector<int>> vector(dimension, std::vector<int>(dimension, 0));

	//Create the Spiral
	CreateSpiralPart1(vector);

	//Look for the input value
	int valueRow, valueColumn;
	FindCellWithValue(vector, input, valueRow, valueColumn);

	//Util::PrintMatrix(vector);

	//Calculate Manhattan
	int center = (int)vector.size() / 2;
	int manhattan = Util::ManhattanDistance(center, center, valueRow, valueColumn);
	std::cout << "Steps to carry '" << input << "' to the center: " << manhattan<< std::endl;

	//Part 2
	std::cout << "Part 2. Your input stills " << input << std::endl;
	dimension = CalculateVectorDimension(input);

	std::vector<std::vector<int>> vectorPart2(dimension, std::vector<int>(dimension, 0));
	int greaterValue;
	CreateSpiralPart2(vectorPart2, input, greaterValue);

	//Util::PrintMatrix(vectorPart2);
	std::cout << "First greater Value: " << greaterValue << "\n";

	return 0;
}

int Day3::CalculateVectorDimension(int number) {
	int sum = 0;
	int i = 0;
	while (sum < number) {
		sum = (1 + (2 * i))*(1 + (2 * i));
		//std::cout << "iteration: " << i << "  sum: " << sum << "\n";
		i++;
	}
	i--; //its add once more time when the condition is fulfill
	return i * 2 + 1;
}

//Creates the Spiral until all the cells are different from 0. The values are 1 by 1
void Day3::CreateSpiralPart1(std::vector<std::vector<int>>& vector) {
	int center = (int)vector.size() / 2;
	vector[center][center] = 1;

	int nextNumber = 2;
	int currentRow = center;
	int currentColumn = center;
	bool completed = false;
	int currentDimension = 2;
	bool movementDecided;
	while (!completed) {
		movementDecided = false;

		//Move to right
		if (!movementDecided && abs((currentColumn + 1) - center) < currentDimension && currentColumn + 1 < vector[0].size() && vector[currentRow][currentColumn + 1] == 0) {
			currentColumn++;
			movementDecided = true;
		}

		//Move up
		if (!movementDecided && abs((currentRow - 1) - center) < currentDimension  && currentRow - 1 >= 0 && vector[currentRow - 1][currentColumn] == 0) {
			currentRow--;
			movementDecided = true;
		}

		//Move left
		if (!movementDecided && abs((currentColumn - 1) - center) < currentDimension  && currentColumn - 1 >= 0 && vector[currentRow][currentColumn - 1] == 0) {
			currentColumn--;
			movementDecided = true;
		}

		//Move down
		if (!movementDecided && abs((currentRow + 1) - center) < currentDimension  && currentRow + 1 < vector.size() && vector[currentRow + 1][currentColumn] == 0) {
			currentRow++;
			movementDecided = true;
		}

		//If it didnt moved
		if (!movementDecided) {
			currentDimension++;
		} else {
			vector[currentRow][currentColumn] = nextNumber;
			nextNumber++;
		}

		//Check out of bounds
		if (currentDimension > vector.size()) {
			completed = true;
		}
	}

}

void Day3::FindCellWithValue(std::vector<std::vector<int>> vector, int value, int& row, int& column) {
	bool founded = false;
	for (int i = 0; !founded && i < vector.size(); i++) {
		for (int j = 0; !founded && j < vector[0].size(); j++) {
			if (vector[i][j] == value) {
				row = i;
				column = j;
				founded = true;
			}
		}
	}
}

//Creates the Spiral until all the cells are different from 0. The values are 1 by 1
void Day3::CreateSpiralPart2(std::vector<std::vector<int>>& vector, int input, int& greaterResult) {
	int center = (int)vector.size() / 2;
	vector[center][center] = 1;

	int currentRow = center;
	int currentColumn = center;
	bool completed = false;
	int currentDimension = 2;
	bool movementDecided;
	while (!completed) {
		movementDecided = false;

		//Move to right
		if (!movementDecided && abs((currentColumn + 1) - center) < currentDimension && currentColumn + 1 < vector[0].size() && vector[currentRow][currentColumn + 1] == 0) {
			currentColumn++;
			movementDecided = true;
		}

		//Move up
		if (!movementDecided && abs((currentRow - 1) - center) < currentDimension  && currentRow - 1 >= 0 && vector[currentRow - 1][currentColumn] == 0) {
			currentRow--;
			movementDecided = true;
		}

		//Move left
		if (!movementDecided && abs((currentColumn - 1) - center) < currentDimension  && currentColumn - 1 >= 0 && vector[currentRow][currentColumn - 1] == 0) {
			currentColumn--;
			movementDecided = true;
		}

		//Move down
		if (!movementDecided && abs((currentRow + 1) - center) < currentDimension  && currentRow + 1 < vector.size() && vector[currentRow + 1][currentColumn] == 0) {
			currentRow++;
			movementDecided = true;
		}

		//If it didnt moved
		if (!movementDecided) {
			currentDimension++;
		} else {
			int newValue = SumOfAdyacents(vector, currentRow, currentColumn);
			vector[currentRow][currentColumn] = newValue;
			if (newValue > input) {
				greaterResult = newValue;
				completed = true;
			}
		}

		if (currentDimension > vector.size()) {
			completed = true;
		}
	}
}

int Day3::SumOfAdyacents(std::vector<std::vector<int>> vector, int row, int column) {
	int sumAdyacents = 0;
	for (int i = row - 1; i <= row + 1; i++) {
		for (int j = column - 1; j <= column + 1; j++) {
			if (i >= 0 && i < vector.size() && j >= 0 && j < vector[0].size()) {
				sumAdyacents += vector[i][j];
			}
		}
	}
	return sumAdyacents;
}

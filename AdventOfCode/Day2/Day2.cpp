#include "Day2.h"
#include "string"
#include <algorithm>    // std::sort
#include <sstream>

int Day2::Main() {
	std::string input = "121 59 141 21 120 67 58 49 22 46 56 112 53 111 104 130 "
		"1926 1910 760 2055 28 2242 146 1485 163 976 1842 1982 137 1387 162 789 "
		"4088 258 2060 1014 4420 177 4159 194 2794 4673 4092 681 174 2924 170 3548 "
		"191 407 253 192 207 425 580 231 197 382 404 472 164 571 500 216 "
		"4700 1161 168 5398 5227 5119 252 2552 4887 5060 1152 3297 847 4525 220 262 "
		"2417 992 1445 184 554 2940 209 2574 2262 1911 2923 204 2273 2760 506 157 "
		"644 155 638 78 385 408 152 360 588 618 313 126 172 220 217 161 "
		"227 1047 117 500 1445 222 29 913 190 791 230 1281 1385 226 856 1380 "
		"436 46 141 545 122 86 283 124 249 511 347 502 168 468 117 94 "
		"2949 3286 2492 2145 1615 159 663 1158 154 939 166 2867 141 324 2862 641 "
		"1394 151 90 548 767 1572 150 913 141 1646 154 1351 1506 1510 707 400 "
		"646 178 1228 1229 270 167 161 1134 193 1312 1428 131 1457 719 1288 989 "
		"1108 1042 93 140 822 124 1037 1075 125 941 1125 298 136 94 135 711 "
		"112 2429 1987 2129 2557 1827 477 100 78 634 352 1637 588 77 1624 2500 "
		"514 218 209 185 197 137 393 555 588 569 710 537 48 309 519 138 "
		"1567 3246 4194 151 3112 903 1575 134 150 4184 3718 4077 180 4307 4097 1705 ";

	const int NUMBER_ROWS = 16;
	const int NUMBER_COLUMNS = 16;
	std::vector<std::vector<int>> numbers = ReadInput(input, NUMBER_ROWS, NUMBER_COLUMNS);
	std::cout << "Day2!! Your Input is: " << std::endl;
	PrintVector(numbers);

	//Part 1
	int checkSum = 0;
	for (int i = 0; i < numbers.size(); i++) {
		checkSum += ChecksumRow(numbers, i);
	}
	std::cout << "\n\nPart 1. CheckSum is: " << checkSum;

	//Part 2
	int evenlyDivisorsSum = 0;
	for (int i = 0; i < numbers.size(); i++) {
		evenlyDivisorsSum += DivideEvenlyRow(numbers, i);
	}
	std::cout << "\n\nPart 2. Sum of evenly divisors is: " << evenlyDivisorsSum << std::endl;

	return 0;
}


std::vector<std::vector<int>> Day2::ReadInput(std::string input, const int rowNumber, const int columnNumber) {
	std::vector<std::vector<int>> matrix(rowNumber, std::vector<int>(columnNumber));
	std::string nextToken = "";
	int currentRow = 0;
	int currentColumn = 0;
	for (int i = 0; i < input.length(); i++) {
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

void Day2::PrintVector(std::vector<std::vector<int>> vector) {
	for (int i = 0; i < vector.size(); i++)
	{
		for (int j = 0; j < vector[0].size(); j++)
		{
			std::cout << vector[i][j] << '\t';
		}
		std::cout << std::endl;
	}
}

int Day2::ChecksumRow(std::vector<std::vector<int>> vector, int row) {
	int min = vector[row][0];
	int max = vector[row][0];

	for (int i = 0; i < vector[row].size(); i++) {
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
	for (int i = 0; !found && i < vector[row].size(); i++) { //the last one is the greater, cant divide any number
		for (int j = i + 1; !found && j < vector[row].size(); j++) {
			if (vector[row][j] % vector[row][i] == 0) {
				division = vector[row][j] / vector[row][i];
				found = true;
			}
		}
	}
	return division;
}


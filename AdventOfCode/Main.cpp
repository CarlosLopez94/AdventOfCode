#include "Day1\Day1.h"
#include "Day2\Day2.h"
#include "Day3\Day3.h"
#include "iostream"

int main() {
	//in the future this will be an input
	//int year = 2017;
	int day = 3;
	int resultErrorNumber = 1;
	switch (day) {
	case 1:
		Day1 day1;
		resultErrorNumber = day1.Main();
		break;
	case 2:
		Day2 day2;
		resultErrorNumber = day2.Main();
		break;
	case 3:
		Day3 day3;
		resultErrorNumber = day3.Main();
		break;
	default:
		std::cout << "Oh ooh this day is not finish yet!";
	}

	//Stop execution
	std::cout << "\nPress \"Enter\" to stop execution...\n";
	std::cin.ignore();
	return resultErrorNumber;
}
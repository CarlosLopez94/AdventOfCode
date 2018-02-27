#include "Day1\Day1.h"
#include "Day2\Day2.h"
#include "iostream"

int main() {
	//in the future this will be an input
	//int year = 2017;
	int day = 2;
	int resultErrorNumber;
	switch (day) {
	case 1:
		Day1 day1;
		resultErrorNumber = day1.Main();
		break;
	case 2:
		Day2 day2 = Day2();
		resultErrorNumber = day2.Main();
		break;
	default:
		std::cout << "Oh ooh this day is not finish yet!";
	}

	//Stop execution
	std::cout << "\nPress \"Enter\" to stop execution...\n";
	std::cin.ignore();
	return resultErrorNumber;
}
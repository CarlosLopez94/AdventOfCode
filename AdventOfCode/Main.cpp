#include "Day1\Day1.h"
#include "iostream"

int main() {
	Day1 d;
	int resultErrorNumber = d.Main();


	//Stop execution
	std::cout << "\nPress \"Enter\" to stop execution...\n";
	std::cin.ignore();
	return resultErrorNumber;
}
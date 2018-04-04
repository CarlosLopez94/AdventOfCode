#include "Day1\Day1.h"
#include "Day2\Day2.h"
#include "Day3\Day3.h"
#include "Day4\Day4.h"
#include "Day5\Day5.h"
#include "Day6\Day6.h"
#include "Day7\Day7.h"
#include "Day8\Day8.h"
#include "Day9\Day9.h"
#include "Day10\Day10.h"
#include "Day11\Day11.h"
#include "Day12\Day12.h"
#include "Day13\Day13.h"
#include "Day14\Day14.h"
#include "Day15\Day15.h"
#include "Day16\Day16.h"
#include "Day17\Day17.h"
#include "Day18\Day18.h"
#include "Day19\Day19.h"
#include "Day20\Day20.h"
#include "Day21\Day21.h"
#include "Day22\Day22.h"
#include "Day23\Day23.h"
#include "Day24\Day24.h"
#include "Day25\Day25.h"
#include "iostream"
#include "Util.h"

int main() {
	std::cout << "Welcome to Advent Of Code 2017!!!" << std::endl;
	int day;
	int resultErrorNumber;
	bool finish = false;
	bool askContinue;
	do {
		std::cout << "Select a day from 1 to 25: " << std::endl;
		askContinue = true;
		std::cin >> day;
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
		case 4:
			Day4 day4;
			resultErrorNumber = day4.Main();
			break;
		case 5:
			Day5 day5;
			resultErrorNumber = day5.Main();
			break;
		case 6:
			Day6 day6;
			resultErrorNumber = day6.Main();
			break;
		case 7:
			Day7 day7;
			resultErrorNumber = day7.Main();
			break;
		case 8:
			Day8 day8;
			resultErrorNumber = day8.Main();
			break;
		case 9:
			Day9 day9;
			resultErrorNumber = day9.Main();
			break;
		case 10:
			Day10 day10;
			resultErrorNumber = day10.Main();
			break;
		case 11:
			Day11 day11;
			resultErrorNumber = day11.Main();
			break;
		case 12:
			Day12 day12;
			resultErrorNumber = day12.Main();
			break;
		case 13:
			Day13 day13;
			resultErrorNumber = day13.Main();
			break;
		case 14:
			Day14 day14;
			resultErrorNumber = day14.Main();
			break;
		case 15:
			Day15 day15;
			resultErrorNumber = day15.Main();
			break;
		case 16:
			Day16 day16;
			resultErrorNumber = day16.Main();
			break;
		case 17:
			Day17 day17;
			resultErrorNumber = day17.Main();
			break;
		case 18:
			Day18 day18;
			resultErrorNumber = day18.Main();
			break;
		case 19:
			Day19 day19;
			resultErrorNumber = day19.Main();
			break;
		case 20:
			Day20 day20;
			resultErrorNumber = day20.Main();
			break;
		case 21:
			Day21 day21;
			resultErrorNumber = day21.Main();
			break;
		case 22:
			Day22 day22;
			resultErrorNumber = day22.Main();
			break;
		case 23:
			Day23 day23;
			resultErrorNumber = day23.Main();
			break;
		case 24:
			Day24 day24;
			resultErrorNumber = day24.Main();
			break;
		case 25:
			Day25 day25;
			resultErrorNumber = day25.Main();
			break;
		default:
			std::cout << "Oh ooh this day is not valid!! Remember, from 1 to 25. Try again..." << std::endl;
			askContinue = false;
		}

		if (askContinue) {
			bool wrongCharacter = false;
			char c;
			do {
				if (wrongCharacter) {
					std::cout << "Wrong Character! ";
				}
				std::cout << "Do you want to try another day? [Y/N]" << std::endl;

				std::cin >> c;

				wrongCharacter = true;
			} while (c != 'N' && c != 'n' && c != 'Y' && c != 'y');
			finish = c == 'n' || c == 'N' ? true : false;
		}

	} while (!finish || (day < 1 || day>25));

	std::cout << std::endl << "Goodbye!" << std::endl;
	system("pause");
	return resultErrorNumber;
}
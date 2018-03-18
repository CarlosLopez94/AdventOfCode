#pragma once
#include "vector"

class Day16
{
public:
	int Main();
private:
	std::vector<char> InitProgramsList(int size);
	void ProcessDance(std::vector<char>& programs, std::vector<std::string> dance);
	void ProcessDanceMove(std::vector<char>& programs, std::string danceMovement);

	void Spin(std::vector<char>& programs, int spinNumber);
	void Exchange(std::vector<char>& programs, int swapIndex1, int swapIndex2);
	void Partner(std::vector<char>& programs, char swapName1, char swapName2);

};


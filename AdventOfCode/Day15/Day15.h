#pragma once
#include "string"
#include "bitset"

class Day15
{
public:
	int Main();
private:
	int_fast64_t GetNextValue(int_fast64_t factor, int_fast64_t lastValue);
	int_fast64_t GetNextValuePart2(int_fast64_t factor, int_fast64_t lastValue, int multipleOf);

	bool BinariesEqual(std::bitset<16> bin1, std::bitset<16> bin2);
};


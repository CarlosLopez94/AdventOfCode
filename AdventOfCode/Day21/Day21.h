#pragma once
#include "string"
#include "vector"
#include "map"

class Day21
{
public:
	int Main();
private:
	void InitRules(std::map<std::string, std::string>& rules, std::vector<std::string> rulesInput);
	void InitPattern(std::vector<std::vector<char>>& pattern, std::vector<std::string> patternInput);

	int GetOnPixels(std::map<std::string, std::string>& rules, std::vector<std::vector<char>> pattern, std::map<std::vector<std::vector<char>>, int>& subPatternsPixels, int numberIterations);
	int Increase3X3(std::map<std::string, std::string>& rules, std::vector<std::vector<char>> pattern, std::map<std::vector<std::vector<char>>, int>& subPatternsPixels, int numberIterations, int tabs);
	int Increase4x4(std::map<std::string, std::string>& rules, std::vector<std::vector<char>> pattern, std::map<std::vector<std::vector<char>>, int>& subPatternsPixels, int numberIterations, int tabs);
	int Increase6x6(std::map<std::string, std::string>& rules, std::vector<std::vector<char>> pattern, std::map<std::vector<std::vector<char>>, int>& subPatternsPixels, int numberIterations, int tabs);

	std::vector<std::vector<char>> GetSubmatrix(std::vector<std::vector<char>> pattern, int size, int rowOrigin, int columnOrigin);
	std::vector<std::vector<char>> GetTransformed(std::map<std::string, std::string>& rules, std::vector<std::vector<char>> pattern);
	void MergeMatrix(std::vector<std::vector<char>>& newPattern, std::vector<std::vector<char>> oldPattern, int size, int originRow, int originColumn);
	int CountPixelsOn(std::vector<std::vector<char>>pattern);

	std::string MatrixToString(std::vector<std::vector<char>> pattern);
	std::vector<std::vector<char>> LineToMatrix(std::string patternOneLine);

	void PrintMatrix(std::vector<std::vector<char>> pattern, int tabs);	
};


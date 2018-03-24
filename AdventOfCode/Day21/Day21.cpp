#include "Day21.h"
#include "../Util.h"
#include "iostream"
#include "chrono"

int Day21::Main() {
	std::cout << "Day 21 - Part 1" << std::endl;
	std::vector<std::string> rulesInput = Util::ReadFile("../AdventOfCode/Day21/patternsRules.txt");
	std::vector<std::string> patternInput = Util::ReadFile("../AdventOfCode/Day21/input.txt");

	std::vector<std::vector<char>> aux(3, std::vector<char>(3));

	//Init rules and initial pattern
	std::map<std::string, std::string> rules;
	std::vector<std::vector<char>> pattern;
	InitRules(rules, rulesInput);
	InitPattern(pattern, patternInput);

	std::map<std::vector<std::vector<char>>, int> subPatternsPixels;
	int pixelsOn = GetOnPixels(rules, pattern, subPatternsPixels, 5);
	std::cout << "Numbers of On pixels after 5 iterations: " << pixelsOn << std::endl;

	auto start_time = std::chrono::high_resolution_clock::now();
	pixelsOn = GetOnPixels(rules, pattern, subPatternsPixels, 18);

	auto end_time = std::chrono::high_resolution_clock::now();
	auto time = end_time - start_time;
	std::cout << "fib(100) took " << std::chrono::duration_cast<std::chrono::seconds>(time).count()/60<<":"<< std::chrono::duration_cast<std::chrono::seconds>(time).count()%60 << " to run.\n";
	std::cout << "Numbers of On pixels after 18 iterations: " << pixelsOn << std::endl;
	return 0;
}

void Day21::InitRules(std::map<std::string, std::string>& rules, std::vector<std::string> rulesInput) {
	int overwrite = 0;
	for (std::string rule : rulesInput) {
		auto ruleTokens = Util::Split(rule, " => ");
		auto left = ruleTokens[0];
		auto right = ruleTokens[1];
		rules[left] = right;
	}
}

void Day21::InitPattern(std::vector<std::vector<char>>& pattern, std::vector<std::string> patternInput) {
	pattern = std::vector<std::vector<char>>(patternInput.size(), std::vector<char>(patternInput.size()));

	for (int i = 0; i < patternInput.size(); i++) {
		for (int j = 0; j < patternInput.size(); j++) {
			pattern[i][j] = patternInput[i].at(j);
		}
	}
}

int Day21::GetOnPixels(std::map<std::string, std::string>& rules, std::vector<std::vector<char>> pattern, std::map<std::vector<std::vector<char>>, int>& subPatternsPixels, int numberIterations) {
	return Increase3X3(rules, pattern, subPatternsPixels, numberIterations, 0);
}

int Day21::Increase3X3(std::map<std::string, std::string>& rules, std::vector<std::vector<char>> pattern, std::map<std::vector<std::vector<char>>, int>& subPatternsPixels, int numberIterations, int tabs) {
	if (numberIterations > 0) {
		auto transformed = GetTransformed(rules, pattern);// LineToMatrix(ruleString);// GetTransformed(rules, pattern);//

		return Increase4x4(rules, transformed, subPatternsPixels, numberIterations - 1, tabs + 1);
	} else {
		int pixels = CountPixelsOn(pattern);
		return pixels;
	}
}

int Day21::Increase4x4(std::map<std::string, std::string>& rules, std::vector<std::vector<char>> pattern, std::map<std::vector<std::vector<char>>, int>& subPatternsPixels, int numberIterations, int tabs) {
	if (numberIterations > 0) {
		std::vector<std::vector<char>> nextPattern(6, std::vector<char>(6));

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				auto transform = GetTransformed(rules, GetSubmatrix(pattern, 2, 2 * i, 2 * j));
				MergeMatrix(nextPattern, transform, 3, i, j);
			}
		}
		return Increase6x6(rules, nextPattern, subPatternsPixels, numberIterations - 1, tabs + 1);
	} else {
		return CountPixelsOn(pattern);
	}
}

int Day21::Increase6x6(std::map<std::string, std::string>& rules, std::vector<std::vector<char>> pattern, std::map<std::vector<std::vector<char>>, int>& subPatternsPixels, int numberIterations, int tabs) {
	if (numberIterations > 0) {
		int pixelsTotal = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				auto transformed = GetTransformed(rules, GetSubmatrix(pattern, 2, 2 * i, 2 * j));
				int pixels;
				if (subPatternsPixels.find(transformed) != subPatternsPixels.end()) {
					//if this pattern has been calculated before, copy the result
					pixels = subPatternsPixels[transformed];
				} else {
					//calculate this pattern and save result
					pixels = Increase3X3(rules, transformed, subPatternsPixels, numberIterations - 1, tabs + 1);
					//subPatternsPixels[transformed] = pixels;
				}
				pixelsTotal += pixels;
			}
		}
		return pixelsTotal;
	} else {
		return CountPixelsOn(pattern);
	}
}

std::vector<std::vector<char>> Day21::GetSubmatrix(std::vector<std::vector<char>> originalPattern, int size, int rowOrigin, int columnOrigin) {
	std::vector<std::vector<char>> result(size, std::vector<char>(size));
	for (int i = rowOrigin; i < rowOrigin + size; i++) {
		for (int j = columnOrigin; j < columnOrigin + size; j++) {
			result[i - rowOrigin][j - columnOrigin] = originalPattern[i][j];
		}
	}
	return result;
}

std::vector<std::vector<char>> Day21::GetTransformed(std::map<std::string, std::string>& rules, std::vector<std::vector<char>> pattern) {
	std::string transformed = MatrixToString(pattern);
	bool found = false;
	auto it = rules.begin();
	int rotate = 0;
	while (!found) {
		if (it == rules.end()) {
			it = rules.begin();
			if (rotate > 4) { //flip
				Util::FlipMatrix(pattern);
				rotate = 0;
			} else {//rotate
				Util::RotateMatrix(pattern);
				rotate++;
			}
			transformed = MatrixToString(pattern);
		} else if (transformed.compare(it->first) == 0) {
			transformed = it->second;
			rules[MatrixToString(pattern)] = it->second; //we add the original pattern to the rule chain
			found = true;
		} else {
			it++;
		}
	}
	return LineToMatrix(transformed);
}

void Day21::MergeMatrix(std::vector<std::vector<char>>& nextPattern, std::vector<std::vector<char>> oldPattern, int size, int originRow, int originColumn) {
	for (int i = originRow * size; i < originRow*size + size; i++) {
		for (int j = originColumn * size; j < originColumn*size + size; j++) {
			nextPattern[i][j] = oldPattern[i - originRow * size][j - originColumn * size];
		}
	}
}

int Day21::CountPixelsOn(std::vector<std::vector<char>> pattern) {
	int pixelsOn = 0;
	for (int i = 0; i < pattern.size(); i++) {
		for (int j = 0; j < pattern.size(); j++) {
			if (pattern[i][j] == '#') {
				pixelsOn++;
			}
		}
	}
	return pixelsOn;
}

std::string Day21::MatrixToString(std::vector<std::vector<char>> pattern) {
	std::string oneLine = "";

	for (int i = 0; i < pattern.size(); i++) {
		for (int j = 0; j < pattern[0].size(); j++) {
			oneLine += pattern[i][j];
		}
		if (i < pattern.size() - 1) {
			oneLine += '/';
		}
	}
	return oneLine;
}

std::vector<std::vector<char>> Day21::LineToMatrix(std::string pattern) {
	auto tokens = Util::Split(pattern, "/");
	std::vector<std::vector<char>> result(tokens.size(), std::vector<char>(tokens.size()));

	int row = 0;
	int column = 0;
	for (char character : pattern) {
		if (character == '/') {
			row++;
			column = 0;
		} else {
			result[row][column] = character;
			column++;
		}
	}

	return result;
}

void Day21::PrintMatrix(std::vector<std::vector<char>> pattern, int tabs) {
	std::string tabsAux = "";
	for (int i = 0; i < tabs; i++) {
		tabsAux += '\t';
	}

	for (int i = 0; i < pattern.size(); i++) {
		std::cout << tabsAux;
		for (int j = 0; j < pattern.size(); j++) {
			std::cout << pattern[i][j];
		}
		std::cout << std::endl;
	}
}

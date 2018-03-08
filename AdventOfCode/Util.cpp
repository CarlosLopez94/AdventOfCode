#include "Util.h"
#include "iostream"
#include "fstream"

namespace Util {

	std::vector<std::string> ReadFile(std::string fileName) {
		std::vector<std::string> lines;
		std::string line;
		std::ifstream myfile(fileName);
		if (myfile.is_open()) {
			while (getline(myfile, line)) {
				lines.push_back(line);
			}
			myfile.close();
		} else {
			std::cout << "Unable to open file\n";
		}
		return lines;
	}

	std::vector<std::string> Split(std::string stringToSplit, std::string separator) {
		std::vector<std::string> tokens;
		std::string stringAux = stringToSplit;
		int indexNextToken = 0;
		while (indexNextToken > -1 && indexNextToken < stringToSplit.size()) {
			indexNextToken = stringAux.find(separator);
			if (indexNextToken != -1) {
				tokens.push_back(stringAux.substr(0, indexNextToken));
				stringAux = stringAux.substr(indexNextToken + separator.size(), stringToSplit.size());//we have to jump the separator
			} else {
				tokens.push_back(stringAux);
			}
		}
		return tokens;
	}
}
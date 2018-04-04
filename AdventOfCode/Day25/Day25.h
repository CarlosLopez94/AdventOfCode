#pragma once
#include "map"
#include "vector"
#include "string"

class Day25
{
public:
	int Main();
private:
	struct Behaviour {
		int write;
		bool right;
		char nextState;

		Behaviour() {
			write = 0;
			right = true;
			nextState = '*';
		}

		Behaviour(int write, bool right, char nextState) {
			this->write = write;
			this->right = right;
			this->nextState = nextState;
		}
	};

	struct State {
		char id;
		Behaviour behaviour0;
		Behaviour behaviour1;

		State() {
			this->id = '*';
			this->behaviour0 = Behaviour();
			this->behaviour1 = Behaviour();
		}

		State(char id, Behaviour value0, Behaviour value1) {
			this->id = id;
			this->behaviour0 = value0;
			this->behaviour1 = value1;
		}
	};

	struct Turing {
		std::vector<int> machine;
		int index;
		char currentState;

		Turing() {
			index = 0;
			currentState = '*';
		}

		Turing(std::vector<int> machine, int index, char currentState) {
			this->machine = machine;
			this->index = index;
			this->currentState = currentState;
		}
	};

	void InitStates(std::map<char, State>& states, char& initialState, int& steps, std::vector<std::string> input);
	void InitTuringMachine(Turing& turing, int initSize, char initState);

	void ExecuteState(Turing& turing, std::map<char, State>* states);
	int GetCheckSum(Turing& turing);

	bool CheckOutOfBounds(Turing& turing);
	void ExtendTuring(Turing& turing, int increaseSize);
	void PrintTuring(Turing turing);
};


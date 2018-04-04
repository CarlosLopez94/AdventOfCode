#include "Day25.h"
#include "../Util.h"
#include "iostream"

int Day25::Main() {
	std::cout << "Day 25 - Part 1" << std::endl;
	std::vector<std::string> input = Util::ReadFile("../AdventOfCode/Day25/input.txt");
	//Init States
	std::map<char, State> states;
	char initialState;
	int steps;
	InitStates(states, initialState, steps, input);

	//Init Turing Machine
	Turing turing;
	InitTuringMachine(turing, 6, initialState);

	std::cout << "Init \t";
	PrintTuring(turing);

	//Execute
	for (int i = 1; i <= steps; i++) {
		ExecuteState(turing, &states);
		if (i % 100000 == 0) {
			std::cout << "It: " << i << std::endl;
			//PrintTuring(turing);
		}
	}

	int checksum = GetCheckSum(turing);
	std::cout << "The checksum after " << steps << " steps is: " << checksum << std::endl;
	return 0;
}

void Day25::InitStates(std::map<char, State>& states, char& initialState, int& steps, std::vector<std::string> input) {
	//Get first state
	initialState = Util::Split(input[0], "state ")[1][0];
	//Get steps number
	steps = std::stoi(Util::Split(Util::Split(input[1], "after ")[1], " ")[0]);

	int lineIndex = 2;
	while (lineIndex < input.size()) {
		//Get the id of the new state
		char stateId = Util::Split(input[lineIndex + 1], "state ")[1][0];
		//Behavior when value is 0
		int write0 = Util::Split(input[lineIndex + 3], "value ")[1][0] == '0' ? 0 : 1; //write
		bool right0 = Util::Split(input[lineIndex + 4], "to the ")[1] == "right."; //right or left
		char nextState0 = Util::Split(input[lineIndex + 5], "state ")[1][0]; //next State
		Behaviour behaviour0 = Behaviour(write0, right0, nextState0);

		//Behavior when value is 1
		int write1 = Util::Split(input[lineIndex + 7], "value ")[1][0] == '0' ? 0 : 1; //write
		bool right1 = Util::Split(input[lineIndex + 8], "to the ")[1] == "right."; //right or left
		char nextState1 = Util::Split(input[lineIndex + 9], "state ")[1][0]; //next State
		Behaviour behaviour1 = Behaviour(write1, right1, nextState1);

		State newState = State(stateId, behaviour0, behaviour1);
		states[stateId] = newState;
		lineIndex += 10; //a state is defined in 10 lines
	}
}

void Day25::InitTuringMachine(Turing& turing, int initSize, char initState) {
	std::vector<int> machine(initSize, 0);
	int initIndex = (initSize / 2);//starts at center
	turing = Turing(machine, initIndex, initState);
}

void Day25::ExecuteState(Turing& turing, std::map<char, State>* states) {
	//Choose Behaviour
	int currentValue = turing.machine[turing.index];
	State currentState = (*states)[turing.currentState];
	Behaviour behaviour = currentValue == 0 ? currentState.behaviour0 : currentState.behaviour1;

	//Write new value
	turing.machine[turing.index] = behaviour.write;
	//Move index right or left
	if (behaviour.right) {
		turing.index++;
	} else {//left
		turing.index--;
	}
	//Change current state
	turing.currentState = behaviour.nextState;

	//Extend machine if out of bounds
	if (CheckOutOfBounds(turing)) {
		ExtendTuring(turing, 5);
	}
}

int Day25::GetCheckSum(Turing & turing) {
	int checksum = 0;
	for (int i = 0; i < turing.machine.size(); i++) {
		if (turing.machine[i] == 1) {
			checksum++;
		}
	}
	return checksum;
}

bool Day25::CheckOutOfBounds(Turing& turing) {
	return turing.index < 0 || turing.index >= turing.machine.size();
}

void Day25::ExtendTuring(Turing& turing, int increaseSize) {
	//Create new Turing Machine
	std::vector<int> newMachine(turing.machine.size() + increaseSize * 2, 0);

	//Populate the vlaues on the old machine
	for (int i = increaseSize; i < increaseSize + turing.machine.size(); i++) {
		newMachine[i] = turing.machine[i - increaseSize];
	}

	//save this new machine
	turing.machine = newMachine;
	turing.index += increaseSize;
}

void Day25::PrintTuring(Turing turing) {
	std::cout << "State '" << turing.currentState << "' => ...";

	for (int i = 0; i < turing.machine.size(); i++) {
		if (i == turing.index) {
			std::cout << " [" << turing.machine[i] << ']';
		} else {
			std::cout << "  " << turing.machine[i] << ' ';
		}
	}
	std::cout << " ..." << std::endl;
}

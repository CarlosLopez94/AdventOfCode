#include "Day17.h"
#include "../Util.h"
#include "iostream"
#include "vector"
#include "string"


int Day17::Main() {
	std::cout << "Day 17 - Part 1" << std::endl;
	int stepsNumber = std::stoi(Util::ReadFileSingleLine("../AdventOfCode/Day17/input.txt"));
	std::cout << "Input is: " << stepsNumber << std::endl;
	//Init circular list
	Node* currentNode = InitCircularList();
	int listSize = 1;
	const int MAX_VALUES = 2018;
	for (int i = 1; i < MAX_VALUES; i++) {
		currentNode = SpinlockIteration(currentNode, stepsNumber, i, listSize);
	}

	std::cout << "The value after 2017 is: " << currentNode->after->value << std::endl;
	std::cout << "Part 2" << std::endl;
	currentNode = InitCircularList();
	listSize = 1;
	const int LAST_VALUE = 50000001;
	for (int i = 1; i < LAST_VALUE; i++) {
		currentNode = SpinlockIteration(currentNode, stepsNumber, i, listSize);
	}

	Node* firstNode = FindNode(currentNode, 0);
	std::cout << "The value after 0 is: " << firstNode->after->value << std::endl;

	return 0;
}

Day17::Node* Day17::InitCircularList() {
	Node* circularList = new Node();
	circularList->value = 0;
	circularList->before = circularList;
	circularList->after = circularList;
	return circularList;
}

Day17::Node* Day17::SpinlockIteration(Node* currentNode, int stepsNumber, int currentValue, int& listSize) {
	currentNode = MoveThroughCircularList(currentNode, stepsNumber%listSize);
	AddValueAfter(currentNode, currentValue, listSize);
	currentNode = currentNode->after;
	if (currentValue % 200000 == 0) {
		std::cout << "Iteration " << currentValue << std::endl;
	}

	return currentNode;
}

Day17::Node* Day17::MoveThroughCircularList(Node * origin, int stepsToMove) {
	if (stepsToMove == 0) {
		return origin;
	} else {
		return MoveThroughCircularList(origin->after, stepsToMove - 1);
	}
}

void Day17::AddValueAfter(Node * origin, int value, int& listSize) {
	//we have: origin -> afterOrigin
	//we need: origin -> newNode -> afterOrigin
	Node* newNode = new Node();
	newNode->value = value;
	Node* oldAfter = origin->after;

	newNode->before = origin; //set origin as "before" of the new node
	newNode->after = oldAfter; //Set the previous after to the new node
	origin->after = newNode; //Set the new node as after of origin
	oldAfter->before = newNode; //Set the new node as before of the old after

	listSize++; //increase list size by 1
}

Day17::Node* Day17::FindNode(Node * origin, int valueToFind) {
	while (origin->value != valueToFind) {
		origin = origin->after;
	}
	return origin;
}

void Day17::PrintCircularList(Node* first) {
	PrintCircularListAux(first, first->after);
}

void Day17::PrintCircularListAux(Node* origin, Node* current) {
	if (origin != current) {
		std::cout << current->value << " -> ";
		PrintCircularListAux(origin, current->after);
	}
}

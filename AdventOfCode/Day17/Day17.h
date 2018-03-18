#pragma once
class Day17
{
public:
	int Main();
private:
	struct Node {
		int value;
		Node* before = nullptr;
		Node* after = nullptr;
	};
	Node* InitCircularList();
	Node* SpinlockIteration(Node * currentNode, int stepsNumber, int currentValue, int& listSize);
	Node* MoveThroughCircularList(Node* origin, int stepsToMove);
	void AddValueAfter(Node* origin, int value, int& listSize);
	Node* FindNode(Node* origin, int valueToFind);

	void PrintCircularList(Node* first);
	void PrintCircularListAux(Node* origin, Node* first);

};


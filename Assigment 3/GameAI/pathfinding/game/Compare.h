#pragma once
#include "Node.h"

class Compare
{
public:
	bool operator() (Node* left, Node* right)
	{
		return left->getCost() > right->getCost();
	}
};
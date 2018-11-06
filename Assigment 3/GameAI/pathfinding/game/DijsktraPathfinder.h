#pragma once

#include "GridPathfinder.h"
#include <vector>

using namespace std;
class Path;
class Graph;
class GraphicsBuffer;
class Grid;
class Connection;

class Dijsktra :public GridPathfinder
{
public:
	Dijsktra(Graph* pGraph, bool Astar);
	~Dijsktra();

	Path* findPath(Node* pFrom, Node* pTo);

private:
	bool mApplyAStar = true;

};


#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <vector>
#include <Trackable.h>

class Graph;
class Path;
class Node;
class GraphicsBuffer;
class Grid;

#define VISUALIZE_PATH 1

class Pathfinder :public Trackable
{
public:
	Pathfinder(Graph* pGraph);
	virtual ~Pathfinder();

	virtual Path* findPath(Node* pFrom, Node* pTo) = 0;

protected:
	Graph* mpGraph;

};

#endif // !PATHFINDING_H
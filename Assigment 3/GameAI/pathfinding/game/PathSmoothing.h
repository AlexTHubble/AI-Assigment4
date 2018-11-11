#ifndef PATH_SMOOTHING_H
#define PATH_SMOOTHING_H

#include "GridPathfinder.h"
#include <vector>
#include <map>
#include <Trackable.h>

class Path;
class Graph;
class Grid;

class PathSmoothing : public GridPathfinder
{
public:
	PathSmoothing(Graph* pGraph);
	~PathSmoothing();
	//
	void LoadWallBlocksVector();
	//
	Path* SmoothPath(Graph* pGraph, Path* pPath);
	bool RaycastToTarget(Node* current, Node* target);

private:
	std::vector<Node*> wallBlocks;
};

#endif // !PATH_SMOOTHING_H


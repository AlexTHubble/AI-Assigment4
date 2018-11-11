#ifndef PATH_SMOOTHING_H
#define PATH_SMOOTHING_H

#include "GridPathfinder.h"
#include <Vector2D.h>
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
	//
	bool LineSquareIntersection(Node* current, Node* target, Node* wallNode);
	bool LineLineIntersection(Vector2D p1, Vector2D q1, Vector2D p2, Vector2D q2);
	bool OnSegment(Vector2D p, Vector2D q, Vector2D r);
	int Orientation(Vector2D p, Vector2D q, Vector2D r);

private:
	std::vector<Node*> wallBlocks;
};

#endif // !PATH_SMOOTHING_H


#ifndef PATH_SMOOTHING_H
#define PATH_SMOOTHING_H

#include <map>
#include <Trackable.h>

class Path;
class Graph;
class Grid;

class PathSmoothing : public Trackable
{
public:
	PathSmoothing();
	~PathSmoothing();
	//
	Path* SmoothPath(Graph* pGraph, Path* pPath);
	bool RaycastToTarget(Node* current, Node* target);

private:

};

#endif // !PATH_SMOOTHING_H


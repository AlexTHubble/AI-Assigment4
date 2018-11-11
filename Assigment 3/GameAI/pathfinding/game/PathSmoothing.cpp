#include "PathSmoothing.h"
#include "Path.h"

PathSmoothing::PathSmoothing()
{

}

PathSmoothing::~PathSmoothing()
{

}

Path* PathSmoothing::SmoothPath(Graph * pGraph, Path * pPath)
{
	//If the path is two nodes long, then smoothing is not needed
	//So return the path
	if (pPath->getNumNodes() == 2)
	{
		return pPath;
	}
	//Create output path
	Path* smoothPath = new Path();
	//We start at 3rd nos in cause we assum first two nodes are adjacent
	//and will pass the Raycast
	int pathIndex = 2;
	//Add first node to path
	smoothPath->addNode(pPath->peekNode(0));

	//Loop until we find the last item in the smoothPath
	while (pathIndex < smoothPath->getNumNodes() - 1)
	{
		//Do Raycast
		//If it doesn't pass
		if (!RaycastToTarget(smoothPath->peekNode(smoothPath->getNumNodes() - 1), pPath->peekNode(pathIndex)))
		{
			//If Raycast does not clear, add the last node that
			//passed to the output list
			smoothPath->addNode(pPath->peekNode(pathIndex - 1));
		}
		//Increment to next node
		pathIndex++;
	}	
	//We've reached the end of the path list, ass the
	//end node to the output and return it
	smoothPath->addNode(pPath->peekNode(pPath->getNumNodes() - 1));
	return smoothPath;
}

bool PathSmoothing::RaycastToTarget(Node * current, Node * target)
{
	return false;
}


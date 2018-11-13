#include "PathSmoothing.h"
#include "GameApp.h"
#include "GridGraph.h"
#include "Grid.h"
#include "Path.h"
#include <math.h>

PathSmoothing::PathSmoothing()
{
	//If wallblock have not been loaded
	if (wallBlocks.empty())
	{
		LoadWallBlocksVector();
	}
}

PathSmoothing::~PathSmoothing()
{
	//Clear vector
	wallBlocks.clear();
}

void PathSmoothing::LoadWallBlocksVector()
{
	//Get Grid
	Grid* grid = dynamic_cast<GameApp*>(gpGame)->getGrid();
	Graph* graph = dynamic_cast<GameApp*>(gpGame)->getGridGraph();
	//Get number of indices
	int numGridIndices = grid->getGridWidth() * grid->getGridHeight();
	//Check each indice for if it is blocked or not
	for (int i = 0; i < numGridIndices; i++)
	{
		//If it is equal to the blocking value add it to the list of walls
		if (grid->getValueAtIndex(i) == BLOCKING_VALUE)
		{
			wallBlocks.push_back(graph->getNode(i));
		}
	}

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
	while (pathIndex < pPath->getNumNodes() - 1)
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
	//Loop through all block in wallBlocks vector
	for (int i = 0; i < wallBlocks.size(); i++)
	{
		//If any walls intersect with Raycast between points, return Raycast hit as true
		if (LineSquareIntersection(current, target, wallBlocks[i]))
		{
			return true;
		}
	}
	//If the Raycasts don't intersect with any wall blocks, return Raycast hit as false
	return false;
}

bool PathSmoothing::LineSquareIntersection(Node* current, Node* target, Node* wallNode)
{
	//Get Grid
	Grid* grid = dynamic_cast<GameApp*>(gpGame)->getGrid();
	//Current Node Variables (Center of square)
	Vector2D currentCenter = grid->getULCornerOfSquare(current->getId()) - (grid->getSquareSize() / 2.0f);
	//Target Node Variables (Center of square)
	Vector2D targetCenter = grid->getULCornerOfSquare(target->getId()) - (grid->getSquareSize() / 2.0f);
	//Get wallNode vertices
	Vector2D wallUL = grid->getULCornerOfSquare(wallNode->getId());
	Vector2D wallLL = Vector2D(grid->getULCornerOfSquare(wallNode->getId()).getX(), grid->getULCornerOfSquare(wallNode->getId()).getY() - grid->getSquareSize());
	Vector2D wallUR = Vector2D(grid->getULCornerOfSquare(wallNode->getId()).getX() + grid->getSquareSize(), grid->getULCornerOfSquare(wallNode->getId()).getY());
	Vector2D wallLR = Vector2D(grid->getULCornerOfSquare(wallNode->getId()).getX() + grid->getSquareSize(), grid->getULCornerOfSquare(wallNode->getId()).getY() - grid->getSquareSize());

	//Check intersection between wallNode sides and Raycast between current and target
	//Intersection: current -> target with wallUL -> wallUR
	bool check1 = LineLineIntersection(currentCenter, targetCenter, wallUL, wallUR);
	//Intersection: current -> target with wallUR -> wallLR
	bool check2 = LineLineIntersection(currentCenter, targetCenter, wallUR, wallLR);
	//Intersection: current -> target with wallLR -> wallLL
	bool check3 = LineLineIntersection(currentCenter, targetCenter, wallLR, wallLL);
	//Intersection: current -> target with wallLL -> wallUL
	bool check4 = LineLineIntersection(currentCenter, targetCenter, wallLL, wallUL);

	//If no raycasts intersect, return false for raycast hit
	if (!check1 && !check2 && !check3 && !check4)
	{
		return false;
	}
	//If any raycast intersects, return true for raycast hit
	else
	{
		return true;
	}
}

bool PathSmoothing::LineLineIntersection(Vector2D p1, Vector2D q1, Vector2D p2, Vector2D q2)
{
	//See https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
	// for details of below formula. 

	// Find the four orientations needed for general and 
	// special cases 
	int o1 = Orientation(p1, q1, p2);
	int o2 = Orientation(p1, q1, p2);
	int o3 = Orientation(p1, q1, p2);
	int o4 = Orientation(p1, q1, p2);

	//General case
	if (o1 != o2 && o3 != o4)
		return true;
	// Special Cases 
	// p1, q1 and p2 are colinear and p2 lies on segment p1q1 
	if (o1 == 0 && OnSegment(p1, p2, q1)) return true;

	// p1, q1 and q2 are colinear and q2 lies on segment p1q1 
	if (o2 == 0 && OnSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are colinear and p1 lies on segment p2q2 
	if (o3 == 0 && OnSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are colinear and q1 lies on segment p2q2 
	if (o4 == 0 && OnSegment(p2, q1, q2)) return true;

	// Doesn't fall in any of the above cases
	return false;
}

bool PathSmoothing::OnSegment(Vector2D p, Vector2D q, Vector2D r)
{
	//See https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
	// for details of below formula. 
	if(q.getX() <= std::fmaxf(p.getX(), r.getX()) && q.getX() >= std::fminf(p.getX(), r.getX()) &&
	   q.getY() <= std::fmaxf(p.getY(), r.getY()) && q.getY() >= std::fminf(p.getY(), r.getY()))
	{
		return true;
	}
	return false;
}

int PathSmoothing::Orientation(Vector2D p, Vector2D q, Vector2D r)
{
	// See https://www.geeksforgeeks.org/orientation-3-ordered-points/ 
	// for details of below formula. 
	int val = (q.getY() - p.getY()) * (r.getX() - q.getX()) -
		      (q.getX() - p.getX()) * (r.getY() - q.getY());
	//Colinear
	if (val == 0)
		return 0;
	//Clock or Counterclock wise
	return (val > 0)? 1 : 2;
}

////Get Grid
//Grid* grid = dynamic_cast<GameApp*>(gpGame)->getGrid();
////Get point variables
//float x0 = grid->getULCornerOfSquare(current->getId()).getX();
//float y0 = grid->getULCornerOfSquare(current->getId()).getY();
//float x1 = grid->getULCornerOfSquare(target->getId()).getX();
//float y1 = grid->getULCornerOfSquare(target->getId()).getY();
//
////
//float dx = abs(x1 - x0);
//float dy = abs(y1 - y0);
//float x = x0;
//float y = y0;
//float n = 1 + dx + dy;
//float x_inc = (x1 > x0) ? 1 : -1;
//float y_inc = (y1 > y0) ? 1 : -1;
//float error = dx - dy;
//dx *= 2;
//dy *= 2;
//
//for (; n > 0; --n)

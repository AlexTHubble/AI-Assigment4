#include "PathToMessage.h"
#include "Game.h"
#include "GameApp.h"
#include "GridPathfinder.h"
#include "Grid.h"
#include "GridGraph.h"
#include "UnitManager.h"
#include "SmoothPathFinding.h"

PathToMessage::PathToMessage( const Vector2D& from, const Vector2D& to )
:GameMessage(PATH_TO_MESSAGE)
,mFrom(from)
,mTo(to)
{
}

PathToMessage::~PathToMessage()
{
}

void PathToMessage::process()
{
	GameApp* pGame = dynamic_cast<GameApp*>(gpGame);
	if( pGame != NULL ) 
	{
		//Get map from Gamemanager
		std::map<UnitID, Unit*> unitMap = gpGame->getUnitManager()->getUnitMap();
		//If unitMap contains units
		if (unitMap.size() > 0)
		{
			//Create iterator
			std::map<UnitID, Unit*>::iterator it;
			//Loop through all unit in Unitmanager
			for (it = unitMap.begin(); it!= unitMap.end(); ++it)
			{
				GridPathfinder* pPathfinder = pGame->getPathfinder();
				GridGraph* pGridGraph = pGame->getGridGraph();
				Grid* pGrid = pGame->getGrid();
				int fromIndex = pGrid->getSquareIndexFromPixelXY((int)mFrom.getX(), (int)mFrom.getY());
				int toIndex = pGrid->getSquareIndexFromPixelXY((int)mTo.getX(), (int)mTo.getY());
				Node* pToNode = pGridGraph->getNode(toIndex);
				Node* pFromNode = pGridGraph->getNode(fromIndex);
				//Path
				Path* pPath;
				//SmoothPath
				smoothPath = new SmoothPathFinding(pGridGraph);
				pPath = smoothPath->FindPath(pFromNode, pToNode);
				//Dijsktra* path = new Dijsktra(pGridGraph, true);
				//pPath = path->findPath(pFromNode, pToNode);
				//Set Path
				it->second->setPath(pPath);
				it->second->setToUpdateTarget();
			}
		}
	}
}

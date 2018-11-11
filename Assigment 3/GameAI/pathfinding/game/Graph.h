#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <Trackable.h>
#include <Vector2D.h>
#include "Node.h"

class Connection;

class Graph :public Trackable
{
public:
	Graph();
	virtual ~Graph();

	virtual void init();
	std::vector<Connection*> getConnections(const Node& from);
	std::vector<Connection*> getConnections(const NODE_ID& fromId);
	Node* getNode(int index);

	//Node* getRandomNonWallNode();


protected:
	//a vector of Node pointers
	std::vector<Node*> mNodes;
	//a vector of Connection pointers
	std::vector<Connection*> mConnections;
	//a map of Connection&'s vectors indexed on Node id
	std::map< NODE_ID, std::vector<Connection*> > mConnectionMap;
};

#endif // !GRAPH_H
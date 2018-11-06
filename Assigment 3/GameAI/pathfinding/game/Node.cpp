#include "Node.h"

Node::Node()
:mId(BAD_NODE_ID)
{
	mCost = 0;
}

Node::Node( const NODE_ID& id )
:mId(id)
{
	mCost = 0;
}

Node::~Node()
{
	//delete mConnection;
}

void Node::addFoundPath(NODE_ID toNode, Path * path)
{
	foundPaths.insert(pair<NODE_ID, Path*>(toNode, path));
}

Path * Node::getPreviousPath(NODE_ID toNode)
{

	if (foundPaths.find(toNode) != foundPaths.end())
	{
		Path* returnPath = foundPaths.find(toNode)->second;
		return returnPath;
	}
	else
	{
		return nullptr;
	}

	
}

#include "Node.h"
#include <exception>

int Node::ID_counter = 0;
std::vector< Node* > Node::node_refs;

Node::Node(int numInlets, int numOutlets)
{
	mID = ID_counter;
	ID_counter++;

	node_refs.push_back(this);

	for(int i=0; i<numInlets; i++)
	{
		inlets.push_back(Inlet(this));
	}
	for(int i=0; i<numOutlets; i++)
	{
		outlets.push_back(Outlet(this));
	}
}

Node::~Node(void)
{
	node_refs[getID()] = NULL;
}

int Node::numInlets(void) 
{ 
	return inlets.size(); 
}

int Node::numOutlets(void) 
{
	return outlets.size(); 
}

Outlet& Node::getOutlet(int index) 
{ 
	if(index < numOutlets())
		return outlets[index]; 
	else
		throw std::range_error("Invalid Outlet");
}

Inlet& Node::getInlet(int index) 
{ 
	if(index < numInlets())
		return inlets[index]; 
	else
		throw std::range_error("Invalid Outlet");
}

int Node::getID(void)
{
	return mID;
}

Node* Node::getNodeRef(int nodeID)
{
	if(nodeID < node_refs.size())
	{
		return node_refs[nodeID];
	}
	else
	{
		return NULL;
	}
}
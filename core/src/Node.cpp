#include "Node.h"

Node::Node(int numInlets, int numOutlets)
{
	for(int i=0; i<numInlets; i++)
	{
		inlets.push_back(Inlet(this));
	}
	for(int i=0; i<numOutlets; i++)
	{
		outlets.push_back(Outlet(this));
	}
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
	return outlets[index]; 
}

Inlet& Node::getInlet(int index) 
{ 
	return inlets[index]; 
}


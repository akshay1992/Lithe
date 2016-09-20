#include "Lithe/Node.h"
#include <exception>

int Node::ID_counter = 0;
std::vector< Node* > Node::node_refs;

Node::Node(int numInlets, int numOutlets)
{
	mID = ID_counter;
	ID_counter++;

	set_DSP_method((DSP_Method)& Node::DSP_Mute);

	node_refs.push_back(this);
	mProcessed = false;

	for(int i=0; i<numInlets; i++)
	{
		inlets.push_back(Inlet(this));
	}
	for(int i=0; i<numOutlets; i++)
	{
		outlets.push_back(Outlet(this));
	}
}

void Node::set_DSP_method( DSP_Method new_DSP_Method )
{
	DSP = new_DSP_Method;
}


Node::~Node(void)
{
	node_refs[getID()] = NULL;
}

void Node::Process(void)
{ 
	// Process all dependent nodes
	(this->*DSP)(); 
	doneProceessing(); 
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

void Node::resetAll_ProcessState()
{
	for( int i=0; i<node_refs.size(); ++i)
	{
		if(node_refs[i] != NULL)
		{
			node_refs[i]->resetProcessState();
		}
	}
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

void Node::resetSortParams(int index = -1, int lowLink = -1, bool onStack = false)
{	
	for( int i=0; i<node_refs.size(); ++i)
	{
		if(node_refs[i] != NULL)
		{
			node_refs[i]->index = index;
			node_refs[i]->lowLink = lowLink;
			node_refs[i]->onStack = onStack;
		}
	}
}

void Node::resetSampleDelayState(bool state)
{	
	for( int i=0; i<node_refs.size(); ++i)
	{
		if(node_refs[i] != NULL)
		{
			for(int j=0; j<node_refs[i]->numInlets(); ++j)
			{
				if( state )				
					node_refs[i]->getInlet(j).enableSampleDelay();
				else
					node_refs[i]->getInlet(j).disableSampleDelay();
			}
		}
	}
}
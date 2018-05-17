#include "Lithe/Node.h"
#include "Lithe/Inlet.h"
#include "Lithe/Outlet.h"
#include "Lithe/Exceptions.h"
#include <exception>
#include <iostream>
namespace lithe{ 

int Node::ID_counter = 0;
std::map <int, Node*> Node::activeNodes;

Node::Node(int numInlets, int numOutlets)
{
	mID = NODEID_START_VALUE + ID_counter;
	ID_counter++;
	// node_refs.push_back(this);
	activeNodes[mID] = this;

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

Node::~Node(void)
{
	// disconnect all inlets and outlets
	for (int i=0; i<numInlets(); ++i)
	{
		Inlet& inlet = getInlet(i);
		if(inlet.isConnected())
		{
			Outlet& outlet = *inlet.getConnectedOutlet();
			Patcher::disconnect( inlet, outlet); 
		}
	}
	for (int i=0; i<numOutlets(); ++i)
	{
		Outlet& outlet = getOutlet(i);
		if(outlet.isConnected())
		{
			for(Inlet* inlet : outlet.getConnectedInlets())
			{
				Patcher::disconnect(*inlet, outlet);
			}
		}
	}
	
	// node_refs[getID()] = nullptr;
	activeNodes.erase(this->getID());
}

void Node::Process(void)
{ 
	DSP(); 
	doneProcessing(); 
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
		throw InvalidOutletException(index, getID());
}

Inlet& Node::getInlet(int index) 
{ 
	if(index < numInlets())
		return inlets[index]; 
	else
		throw InvalidInletException(index, getID());
}

int Node::getID(void)
{
	return mID;
}

void Node::resetAll_ProcessState()
{
	// for( int i=0; i<node_refs.size(); ++i)
	// {
	// 	if(node_refs[i] != nullptr)
	// 	{
	// 		node_refs[i]->resetProcessState();
	// 	}
	// }

	for(auto const& node_it : activeNodes) 
	{
		node_it.second->resetProcessState();
	}

}

Node* Node::getNodeRef(int nodeID)
{
	try
	{
		return activeNodes.at(nodeID);
	}
	catch (std::out_of_range e)
	{
		throw NodeNotFoundException(nodeID);
	}
	// if(nodeID < node_refs.size())
	// {
	// 	return node_refs[nodeID];
	// }
	// else
	// {
	// 	return nullptr;
	// }
}

void Node::resetAll_SampleDelayState(bool state)
{	
	for( auto const& node_it : activeNodes )
	{
		for(int i=0; i<node_it.second->numInlets(); ++i)
		{
			if( state ) 
				node_it.second->getInlet(i).enableSampleDelay();
			else
				node_it.second->getInlet(i).disableSampleDelay();			
		}
	}
	// for( int i=0; i<node_refs.size(); ++i)
	// {
	// 	if(node_refs[i] != nullptr)
	// 	{
	// 		for(int j=0; j<node_refs[i]->numInlets(); ++j)
	// 		{
	// 			if( state )				
	// 				node_refs[i]->getInlet(j).enableSampleDelay();
	// 			else
	// 				node_refs[i]->getInlet(j).disableSampleDelay();
	// 		}
	// 	}
	// }
}

}; // namespace lithe
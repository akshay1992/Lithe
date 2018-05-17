#include "Lithe/Outlet.h"
#include "Lithe/Inlet.h"
#include "Lithe/Node.h"
#include "Lithe/Sample.h"
#include "Lithe/Patcher.h"

#include <cassert>

namespace lithe {

Outlet::Outlet(Node* parent_node) :
	parent_node(parent_node)
{

}

void Outlet::connect(Inlet& inlet)
{
	assert(inlet.getConnectedOutlet() != this);
	Patcher::connect(inlet, *this);
}

void Outlet::disconnect(Inlet& inlet)
{
	if( inlet.getConnectedOutlet() == this)
		Patcher::disconnect(inlet, *this);
}

void Outlet::disconnectAll(void)
{
	for(Inlet* pInlet : connected_inlets)
	{
		disconnect(*pInlet);
	}
}

Node* Outlet::getParentNode(void) const
{
	return parent_node;
}

bool Outlet::isConnected(void)
{
	if( connected_inlets.size() != 0 )
		return true;
	else
		return false;
}

std::vector<Inlet*> Outlet::getConnectedInlets(void) const
{ 
	return connected_inlets; 
} 


Sample Outlet::getSample() 
{
	if( parent_node != nullptr )
		if(! parent_node->isDoneProcessing() )
			parent_node->Process();
	return mSample; 
}

void Outlet::setSample(Sample s) 
{ 
	mSample = s; 
}

}; // namespace lithe
#include "Lithe/Outlet.h"
#include "Lithe/Inlet.h"
#include "Lithe/Node.h"
#include "Lithe/Sample.h"
#include "Lithe/Patcher.h"

namespace lithe {

Outlet::Outlet(Node* parent_node) :
	parent_node(parent_node)
{

}


void Outlet::connect(Inlet& inlet)
{
	Patcher::connect(inlet, *this);
}

Node* Outlet::getParentNode(void) const
{
	return parent_node;
}

void Outlet::disconnect(Inlet& inlet)
{
	// if( inlet.getConnectedOutlet() == this)
	// 	Patcher::disconnect(inlet, *this);
	// else
	// 	throw std::runtime_error("I wasn't connected to this inlet");
}

void Outlet::disconnectAll(void)
{
	for( Inlet* inlet : connected_inlets )
	{
		disconnect(*inlet);
	}
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
	if( parent_node != NULL )
		if(! parent_node->isDoneProcessing() )
			parent_node->Process();
	return mSample; 
}

void Outlet::setSample(Sample s) 
{ 
	mSample = s; 
}

}; // namespace lithe
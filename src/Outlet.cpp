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
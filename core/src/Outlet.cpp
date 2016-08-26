#include "Outlet.h"

Outlet::Outlet(Node* parent_node) :
	parent_node(parent_node)
{

}

void Outlet::connect(Inlet& inlet)
{
	Patcher::connect(inlet, *this);
}

Sample Outlet::getSample() 
{ 
	if(! parent_node->isDoneProcessing() )
		parent_node->Process();
	return mSample; 
}

void Outlet::setSample(Sample s) 
{ 
	mSample = s; 
}
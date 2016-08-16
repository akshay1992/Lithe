#include "Outlet.h"

Outlet::Outlet(Node* parent_node) :
	parent_node(parent_node)
{

}

void Outlet::connect(Inlet& inlet)
{
	Patcher::connect(inlet, *this);
}

void Outlet::disconnect()
{ 
	Patcher::disconnect( *connected_inlet, *this );
}

bool Outlet::isConnected(void) 
{ 
	return (connected_inlet != NULL);
}

Sample Outlet::getSample() 
{ 
	return mSample; 
}

void Outlet::setSample(Sample s) 
{ 
	mSample = s; 
}
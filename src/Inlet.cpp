#include "Lithe/Inlet.h"

Inlet::Inlet(Node* parent_node) :
	parent_node(parent_node),
	sampleDelay(false)
{

}

void Inlet::connect(Outlet& outlet) 
{ 
	Patcher::connect( *this, outlet );
}

void Inlet::disconnect() 
{ 
	Patcher::disconnect( *this, *connected_outlet);
}

Sample Inlet::getSample() 
{ 
	
	if( isConnected() )
	{
		if( sampleDelay )
		{
			Sample outSample = sampleBuffer;
			sampleBuffer = connected_outlet->getSample();
			return outSample;
		}
		else
		{
			return connected_outlet->getSample();
		}
	}
	else
	{
		return Sample(); 
	}
}

bool Inlet::isConnected(void)
{
	return (connected_outlet != NULL);
}
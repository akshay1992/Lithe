#include "Lithe/Inlet.h"
#include "Lithe/Patcher.h"
#include "Lithe/Node.h"

namespace lithe{

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

void Inlet::enableSampleDelay(void) 
{ 
	sampleDelay = true; sampleBuffer = Sample(); 
}

void Inlet::disableSampleDelay(void) 
{ 
	sampleDelay = false; sampleBuffer = Sample(-2, -2, -2, -2); 
}

bool Inlet::sampleDelayEnabled(void) 
{ 
	return sampleDelay; 
}

void Inlet::resetProcessState(void)
{
	if( isConnected() )
	{
		connected_outlet->parent_node->resetProcessState();
		for (int i=0; i<connected_outlet->parent_node->numInlets(); ++i)
			connected_outlet->parent_node->getInlet(i).resetProcessState();
	}
	else
		return;
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

}; // namespace lithe
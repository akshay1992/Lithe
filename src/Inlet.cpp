#include "Lithe/Inlet.h"
#include "Lithe/Patcher.h"
#include "Lithe/Node.h"
#include "Lithe/Exceptions.h"

namespace lithe{

Inlet::Inlet(Node* parent_node) :
	parent_node(parent_node),
	sampleDelay(false)
{

}

Outlet* Inlet::getConnectedOutlet(void) const
{
	return connected_outlet;
}

Node* Inlet::getParentNode(void) const 
{
	return parent_node;
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
		connected_outlet->getParentNode()->resetProcessState();
		for (int i=0; i<connected_outlet->getParentNode()->numInlets(); ++i)
			connected_outlet->getParentNode()->getInlet(i).resetProcessState();
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
	return (connected_outlet != nullptr);
}

}; // namespace lithe
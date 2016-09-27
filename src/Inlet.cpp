#include "Lithe/Inlet.h"
#include "Lithe/Patcher.h"

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
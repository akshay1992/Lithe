#include "TemplateSink.h"

TemplateSink::TemplateSink(void) :
	Sink(2)
{
	// Make sure you set it to use the new DSP method you've defined
	set_DSP_method((DSP_Method)& TemplateSink::DSP);
}


void TemplateSink::DSP(void)
{
	// Iterate through each of the inlets
	for(int i=0; i<numInlets(); ++i)
	{
		if( getInlet(i).isConnected() )
		{
			Sample s = getInlet(i).getSample(); 
			// Do something with s

			// Produce an output

		}
	}
}
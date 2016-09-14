#include "TemplateNode.h"

TemplateNode::TemplateNode(void) :
	Node(1, 1)
{
	// Make sure you set it to use the new DSP method you've defined
	set_DSP_method((DSP_Method)& TemplateNode::DSP);
}


void TemplateNode::DSP(void)
{
	// Iterate through each of the inlets (more generic)
	for(int i=0; i<numInlets(); ++i)
	{
		if( getInlet(i).isConnected() )
		{
			Sample s = getInlet(i).getSample(); 
			// Do something with s??

			// Maybe set outlets
			getOutlet(1).setSample(s);
		}
	}
}
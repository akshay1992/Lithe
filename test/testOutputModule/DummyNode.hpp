#ifndef DUMMY_NODE
#define DUMMY_NODE

#include "Node.h"

// To inject samples and check if OutputModule pulls it. 
class DummyNode : public Node
{
public:
	DummyNode() : Node(0, 1) 
	{
		set_DSP_method( (DSP_Method)& DummyNode::DSP);
	}
	
	Sample outSample;
	void inject(Sample sample)
	{
		outSample = sample;
	}

	void DSP(void)
	{
		getOutlet(0).setSample(outSample)	;
	}
};


#endif
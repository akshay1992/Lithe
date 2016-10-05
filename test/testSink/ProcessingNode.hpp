#ifndef PROCESSING_NODE_HPP
#include "Lithe/LitheCore.h"

/// Used to test the set_DSP_method functionality
class ProcessingNode : public Node
{
public:
	ProcessingNode(void) :
		Node(1, 1)
	{
	}

	virtual void DSP() override
	{
		// Simple bypass node
		Sample s = getInlet(0).getSample();
		s.audio = dc_shift_clip<float> ( s.audio, 0.1, Sample::getRange()) ; 
		s.az = dc_shift_clip<float> ( s.az, 0.1, Sample::getRange()) ;
		s.el = dc_shift_clip<float> ( s.el, 0.1, Sample::getRange()) ;
		s.d = dc_shift_clip<float> ( s.d, 0.1, Sample::getRange()) ;
		getOutlet(0).setSample(s);
	}
};

class SourceNode : public Node
{
public:
	SourceNode(void) :
		Node(1, 1)
	{
	}

	void inject(Sample s)
	{
		injected_sample = s;
	}

	virtual void DSP() override
	{
		// Simple bypass node
		getOutlet(0).setSample(injected_sample);
	}

	Sample injected_sample;
};


#endif
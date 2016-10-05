#ifndef INHERITED_NODE_HPP
#include "Lithe/LitheCore.h"

/// Used to test the set_DSP_method functionality
class InheritedNode : public Node
{
public:
	InheritedNode(void) :
		Node(1, 1)
	{
	}

	virtual void DSP() override
	{
		// Simple bypass node
		Sample s = getInlet(0).getSample();
		getOutlet(0).setSample(s);
	}
};


#endif
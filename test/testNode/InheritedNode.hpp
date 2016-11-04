#ifndef INHERITED_NODE_HPP
#include "Lithe/LitheCore.h"
using namespace lithe;

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
		// add 0.01 to all input samples
		Sample s = getInlet(0).getSample();
		s.audio+= 0.01;
		s.az+= 0.01;
		s.el+= 0.01;
		s.d+= 0.01;
		getOutlet(0).setSample(s);
	}
};


#endif
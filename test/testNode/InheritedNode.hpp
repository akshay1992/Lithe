#ifndef INHERITED_NODE_HPP
#include "Lithe/Node.h"

/// Used to test the set_DSP_method functionality
class InheritedNode : public Node
{
public:
	InheritedNode(void) :
		Node(1, 1)
	{
		set_DSP_method((DSP_Method)& InheritedNode::customDSP);
	}

	void customDSP()
	{
		// Simple bypass node
		Sample s = getInlet(0).getSample();
		getOutlet(0).setSample(s);
	}
};


#endif
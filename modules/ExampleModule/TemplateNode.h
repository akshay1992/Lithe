#ifndef TEMPLATE_NODE_H
#define TEMPLATE_NODE_H

#include "LitheCore.h"

/** @brief An example on how to define a Node module

	A node is something that has both inlets and outlets, and is usually in the middle of a graph. 
	In most cases the Node is Processed automatically if it is connected to something. This is 
	usually instigated by the Sink module present in the graph.  

	This example produces the bare minimum by-pass output

	@ingroup LitheModules
*/
class TemplateNode : public Node
{
public:
	/**
		This example doesn't allow the setting of number of inlets and outlets upon 
		creation. But there is no reason why this can't be allowed if needed. This is 
		a module design decision that is left to the developer

		This node has 1 inlets and 1 outlet (see TemplateNode.cpp for more details on how this
		was set)
	*/ 
	TemplateNode(void);

	/// Implement your custom DSP here
	void DSP(void);
};

#endif //TEMPLATE_NODE_H
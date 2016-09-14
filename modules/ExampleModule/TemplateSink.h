#ifndef TEMPLATE_NODE_H
#define TEMPLATE_NODE_H

#include "LitheCore.h"

/** @brief An example module on how to define a Sink module

	Note that a Sink module is one that a graph flows into. Hence it has no outlets. 
	This is probably where audio rendering is done and speaker outputs are generated 
	to be fed into the soundcard. It is up to the developer to implement this, in addition
	to implementing the mechanism to deliver this to the soundcard.

	To process the graph and obtain one sample of outputs, call Process() on this instance

	@ingroup LitheModules
*/
class TemplateSink : public Sink
{
public:
	/**
		This example doesn't allow the setting of number of inlets and outlets upon 
		creation. But there is no reason why this can't be allowed if needed. This is 
		a module design decision that is left to the developer

		This sink has only 2 inlets (see TemplateSink.cpp for more details on how this
		was set)
	*/ 
	TemplateSink(void);

	/// Implement your custom DSP here
	void DSP(void);
};

#endif //TEMPLATE_NODE_H
#ifndef OUTLET_H
#define OUTLET_H

#include "Lithe/Inlet.h"
#include "Lithe/Node.h"
#include "Lithe/Sample.h"
#include "Lithe/Patcher.h"

class Node;
class Inlet;

/** @brief An outlet terminal of a graph Node. 

 	Processed sample is dumped into an Outlet which can then be read by a connected inlet.
 	An Outlet is passive and unaware of any inlets connected to it. Therefore, any number of inlets may
 	be reading from the same outlet. This is the patch cable equivalent of mult-ing.
	
	@ingroup GraphElements 
 */
class Outlet
{
public:
	Outlet(Node* parent_node);

	void connect(Inlet& inlet);
	
	void disconnect();

	Sample getSample();
	void setSample(Sample s);

	Node* parent_node;
private:
	Sample mSample;
};


#endif // OUTLET_H
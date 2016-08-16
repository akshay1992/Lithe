#ifndef INLET_H
#define INLET_H

#include "Outlet.h"
#include "Node.h"
#include "Sample.h"

class Outlet;
class Node;

/** An inlet is inherited from TERMINAL and can get() samples from it's connected outlet. (to be used for processing within the block)
It also contains the mechanism for 1-sample delay of the input signal
*/
class Inlet 
{
public:
	Inlet(Node* parent_node);

	void connect(Outlet& outlet);
	void disconnect();
	bool isConnected();

	Sample getSample();

	Node* parent_node;

	Outlet* connected_outlet = NULL;
};


#endif //INLET_H
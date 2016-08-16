#ifndef OUTLET_H
#define OUTLET_H

#include "allocore/types/al_Buffer.hpp"

#include "Inlet.h"
#include "Node.h"
#include "Sample.h"
#include "Patcher.h"

class Node;
class Inlet;

// An outlet is something into which processed samples are dumped into. 
// An outlet is passive. 
// It gives a connected inlet a value when asked. 
// Add a buffer?

class Outlet
{
public:
	Outlet(Node* parent_node);

	void connect(Inlet& inlet);
	
	void disconnect();

	bool isConnected(void);

	Sample getSample();
	void setSample(Sample s);

	Node* parent_node;
	Inlet* connected_inlet = NULL;
private:
	Sample mSample;
};


#endif // OUTLET_H
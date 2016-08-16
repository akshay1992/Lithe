#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Inlet.h"
#include "Outlet.h"

class Inlet;
class Outlet;

// A node is something that has inlets and outlets, and is part of an audio graph
class Node
{
public:
	Node(int numInlets, int numOutlets);

	int numInlets(void);
	int numOutlets(void);

	// TODO: FIX THIS
	Outlet& getOutlet(int index = 0);
	Inlet& getInlet(int index = 0);

private:
	std::vector<Inlet> inlets;
	std::vector<Outlet> outlets;
};


#endif	// NODE_H 
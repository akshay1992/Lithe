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
	~Node();

	int numInlets(void);
	int numOutlets(void);

	Outlet& getOutlet(int index = 0);
	Inlet& getInlet(int index = 0);

	int getID();

	static Node* getNodeRef(int nodeID);


private:
	std::vector<Inlet> inlets;
	std::vector<Outlet> outlets;
	static int ID_counter;
	static std::vector< Node* > node_refs;
	int mID;
};



#endif	// NODE_H 
#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Inlet.h"
#include "Outlet.h"
#include "Sample.h"

class Inlet;
class Outlet;

/** @brief An audiograph node that has inlets and outlets. 

	This is a base class on top of which a Module is built

*/
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

	/// Tick audio sample. Remember to fill the Outlets with respective values
	virtual void Process() { doneProceessing(); }

	/// This is called by the Sink
	void doneProceessing() { mProcessed = true; }
	void resetProcessState() { mProcessed = false; }
	bool hasProcessed() { return mProcessed; }

	static void resetAll_ProcessState();
	static Node* getNodeRef(int nodeID);

	/// Graph node parameter for pre-processing a graph. Used by Sorter.h
	int index; 

	/// Graph node parameter for pre-processing a graph. Used by Sorter.h
	int lowLink;
	
	/// Graph node parameter for pre-processing a graph. Used by Sorter.h 
	bool onStack;

	/// Used to reset the sort parameters index, lowLink and onStack for all available Nodes
	static void resetSortParams(int index, int lowLink, bool onStack);

	/// Used to set the sample delay for Inlets in all available Node instances. Used by Sorter.h  
	static void resetSampleDelayState(bool state = false);

private:
	std::vector<Inlet> inlets;
	std::vector<Outlet> outlets;
	static int ID_counter;
	static std::vector< Node* > node_refs;
	int mID;
	bool mProcessed;
};

#endif	// NODE_H 
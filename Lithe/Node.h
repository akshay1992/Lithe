#ifndef NODE_H
#define NODE_H

#include <vector>

namespace lithe {

class Inlet;
class Outlet;
class Node;

/** @brief An audiograph node that has inlets and outlets. 

	This is a base class on top of which a Module is built

	@ingroup GraphElements 
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

	/// This is the default DSP mode of a Node (Outputs all zeroes) Change this using SET_DSP_METHOD
	virtual void DSP(void) {};

	/// Tick audio sample. Remember to fill the Outlets with respective values
	virtual void Process();

	bool isDoneProcessing() { return mProcessed; }

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

protected:
	void doneProceessing() { mProcessed = true; }
	void resetProcessState() { mProcessed = false; }

	std::vector<Inlet> inlets;
	std::vector<Outlet> outlets;
	static int ID_counter;
	static std::vector< Node* > node_refs;
	int mID;
	bool mProcessed;
};

}; // namespace lithe

#endif	// NODE_H 
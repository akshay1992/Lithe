#ifndef NODE_H
#define NODE_H

#include <vector>
#include <map>

namespace lithe {

class Inlet;
class Outlet;
class Node;

/** @brief An audiograph node that has inlets and outlets. 

	This is a base class on top of which a Module is built

	@ingroup AudioGraph 
*/
class Node
{
public:
	Node(int numInlets, int numOutlets=0);
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
	static void resetAll_SampleDelayState(bool state = false);

	friend Inlet;

protected:
	void doneProcessing() { mProcessed = true; }
	void resetProcessState() { mProcessed = false; }

	std::vector<Inlet> inlets;
	std::vector<Outlet> outlets;
	// static std::vector< Node* > node_refs;
	static std::map<int, Node*> activeNodes;

	static int ID_counter;
	/// @brief NodeIDs are alotted starting from this value
	const int NODEID_START_VALUE = 0;

	int mID;
	bool mProcessed;
};

}; // namespace lithe

#endif	// NODE_H 
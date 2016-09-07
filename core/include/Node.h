#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Inlet.h"
#include "Outlet.h"
#include "Sample.h"

class Inlet;
class Outlet;
class Node;

/** A pointer to a DSP method. This is used by Node::set_DSP_method to set the current DSP function. 
*/
typedef void(Node::* DSP_Method) (void);

#define SET_DSP_METHOD(methodName) set_DSP_method( (DSP_Method)& thisClass::method)

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

	/// This is the default DSP mode of a Node (Outputs all zeroes) Change this using SET_DSP_METHOD
	void DSP_Mute()  {}

	/// Tick audio sample. Remember to fill the Outlets with respective values
	void Process() ;

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
	/** @brief Use this to set the DSP method (which may be re-defined within a derived class). 
		This is merely a way to do function overriding without using virtual (makes it C compatible)
	*/
	void set_DSP_method( DSP_Method new_DSP_Method );

	void doneProceessing() { mProcessed = true; }
	void resetProcessState() { mProcessed = false; }

	DSP_Method DSP;
	std::vector<Inlet> inlets;
	std::vector<Outlet> outlets;
	static int ID_counter;
	static std::vector< Node* > node_refs;
	int mID;
	bool mProcessed;
};

#endif	// NODE_H 
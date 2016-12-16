#ifndef OUTLET_H
#define OUTLET_H

#include "Lithe/Sample.h"
#include "Lithe/Patcher.h"
#include <vector>

namespace lithe {

class Node;
class Inlet;

/** @brief An outlet terminal of a graph Node. 

 	Processed sample is dumped into an Outlet which can then be read by a connected inlet.
 	An Outlet is passive and unaware of any inlets connected to it. Therefore, any number of inlets may
 	be reading from the same outlet. This is the patch cable equivalent of mult-ing.
	
	@ingroup AudioGraph 
 */
class Outlet
{
public:
	Outlet(Node* parent_node);

	/// @brief Connects the outlet to an inlet. It allows fanned connections (i.e., multiple inlets connected to the same outlet)
	void connect(Inlet& inlet);	

	/// @brief Cisonnects the outlet from a specific inlet. If inlet wasn't connected to it, it throws an exception.
	void disconnect(Inlet& inlet);	

	/** @brief Disconnects from all connected inlets

		Since the Lithe audiograph allows fanned outlet connections, it currently 
		isn't possible to disconnect a specific patch from an outlet.
	*/
	void disconnectAll(); 	

	Node* getParentNode(void) const;

	bool isConnected(void);
	std::vector<Inlet*> getConnectedInlets(void) const;

	Sample getSample();
	void setSample(Sample s);

	friend class Patcher;
private:
	Node* parent_node;
	std::vector<Inlet*> connected_inlets;
	Sample mSample;
};

}; // namespace lithe


#endif // OUTLET_H
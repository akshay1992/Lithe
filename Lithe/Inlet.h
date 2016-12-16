#ifndef INLET_H
#define INLET_H

#include "Lithe/Sample.h"
#include "Lithe/Patcher.h"

namespace lithe {
	
class Outlet;
class Node;

/** @brief An inlet terminal of a graph Node

	An inlet can get samples getSamples() from it's connected outlet. 
	It contains a mechanism to add 1-sample delay on an incoming input signal. Further, an inlet is _active_
	in the sense that it can instigate processing of any connected blocks via the 'pull' mechanism.

	@ingroup AudioGraph 
*/
class Inlet 
{
public:
	Inlet(Node* parent_node);

	void connect(Outlet& outlet);
	void disconnect();
	bool isConnected();

	Outlet* getConnectedOutlet(void) const;

	Sample getSample();

	void resetProcessState();

	Node* getParentNode(void) const;

	void enableSampleDelay(void);
	void disableSampleDelay(void);
	bool sampleDelayEnabled(void);

	friend class Patcher;
	friend class BFS;
	friend class TarjanSort;

private:
	Node* parent_node;
	Outlet* connected_outlet = NULL;
	bool sampleDelay;
	Sample sampleBuffer;
};

}; // namespace lithe

#endif //INLET_H
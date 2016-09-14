#ifndef INLET_H
#define INLET_H

#include "Outlet.h"
#include "Node.h"
#include "Sample.h"

class Outlet;
class Node;

/** @brief An inlet terminal of a graph Node

	An inlet can get samples getSamples() from it's connected outlet. 
	It contains a mechanism to add 1-sample delay on an incoming input signal. Further, an inlet is _active_
	in the sense that it can instigate processing of any connected blocks via the 'pull' mechanism.

	@ingroup GraphElements 
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

	void enableSampleDelay(void) { sampleDelay = true; sampleBuffer = Sample(); }
	void disableSampleDelay(void) { sampleDelay = false; sampleBuffer = Sample(-2, -2, -2, -2); }
	bool sampleDelayEnabled(void) { return sampleDelay; }

	Outlet* connected_outlet = NULL;
private:
	bool sampleDelay;
	Sample sampleBuffer;
};


#endif //INLET_H
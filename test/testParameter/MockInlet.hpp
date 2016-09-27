#ifndef MOCK_INLET_HPP
#define MOCK_INLET_HPP

#include "Lithe/LitheCore.h"

// Used to inject custom values and see what the modulation does. 
class MockInlet : public Inlet
{
public:
	/// Initialize with some dummy node to make it connected to something
	MockInlet() : Inlet(NULL) { connected_outlet = new Outlet(NULL);}

	using Inlet::Inlet;
	Sample getSample() { return injected_value; }
	void injectSampleValue(Sample val) { injected_value = val; }
	Sample injected_value;

};

#endif
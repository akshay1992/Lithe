#include "Lithe/Patcher.h"
#include <cassert>

using namespace std;
namespace lithe {

void Patcher::connect(Inlet& inlet, Outlet& outlet)
{
	if( inlet.isConnected() )	
		Patcher::disconnect(inlet, *inlet.getConnectedOutlet());

	assert(inlet.connected_outlet == nullptr);
	inlet.connected_outlet = &outlet;
	outlet.connected_inlets.push_back(&inlet);
}

void Patcher::disconnect(Inlet& inlet, Outlet& outlet)
{
	assert(inlet.connected_outlet == &outlet);
	assert(outlet.connected_inlets.size() != 0);
	inlet.connected_outlet = NULL;

	auto it = std::find(outlet.connected_inlets.begin(), outlet.connected_inlets.end(), &inlet);
	if(it != outlet.connected_inlets.end())
	{
		std::swap(*it, outlet.connected_inlets.back());
	    outlet.connected_inlets.pop_back();
	}
	else
	{
		// Outlet not found, nothing to do
		return;
	}

	inlet.connected_outlet = nullptr;
}

}; 
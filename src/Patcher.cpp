#include "Lithe/Patcher.h"
#include <cassert>
#include <stdio.h>

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
	auto it = std::find(outlet.connected_inlets.begin(), outlet.connected_inlets.end(), &inlet);
	if(it != outlet.connected_inlets.end())
	{
		std::swap(*it, outlet.connected_inlets.back());
	    outlet.connected_inlets.pop_back();
	}
	else
	{
		std::runtime_error("Not found");
	}
	// outlet.connected_inlet = nullptr;

	inlet.connected_outlet = nullptr;
}

}; 
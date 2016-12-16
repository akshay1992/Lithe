#include "Lithe/Patcher.h"
#include <iostream> 
using namespace std;
namespace lithe {

void Patcher::connect(Inlet& inlet, Outlet& outlet)
{
	if( inlet.isConnected() )	inlet.disconnect();
	// if( outlet.isConnected() ) outlet.disconnect();

	inlet.connected_outlet = &outlet;
	outlet.connected_inlets.push_back(&inlet);
}

void Patcher::disconnect(Inlet& inlet, Outlet& outlet)
{
	inlet.connected_outlet = NULL;

	auto it = std::find(outlet.connected_inlets.begin(), outlet.connected_inlets.end(), &inlet);
	if(it != outlet.connected_inlets.end())
	{
		using std::swap;
		swap(*it, outlet.connected_inlets.back());
	    outlet.connected_inlets.pop_back();
	}
	else
	{
		std::runtime_error("Not found");
	}
	// outlet.connected_inlet = NULL;
}

}; 
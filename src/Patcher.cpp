#include "Lithe/Patcher.h"

void Patcher::connect(Inlet& inlet, Outlet& outlet)
{
	if( inlet.isConnected() )	inlet.disconnect();
	// if( outlet.isConnected() ) outlet.disconnect();

	inlet.connected_outlet = &outlet;
	// outlet.connected_inlet = &inlet;
}

void Patcher::disconnect(Inlet& inlet, Outlet& outlet)
{
	inlet.connected_outlet = NULL;
	// outlet.connected_inlet = NULL;
}
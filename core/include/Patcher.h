#ifndef PATCHING_UTILS_H
#define PATCHING_UTILS_H

#include "Inlet.h"
#include "Outlet.h"

class Inlet;
class Outlet;

/// @brief Utility class for all patching and unpacthing
/// All NodeBase instances internally call these methods within their connect or disconnect methods. 
class Patcher
{
public:
	static void connect(Inlet& inlet, Outlet& outlet);
	static void disconnect(Inlet& inlet, Outlet& outlet);
};

#endif
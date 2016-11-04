#ifndef PATCHING_UTILS_H
#define PATCHING_UTILS_H


#include "Lithe/Inlet.h"
#include "Lithe/Outlet.h"

namespace lithe {

class Inlet;
class Outlet;

/** @brief Utility class for all patching and unpacthing
	All Node instances internally call these methods within their connect or disconnect methods. 
	
	@ingroup GraphUtils 
*/
class Patcher
{
public:
	static void connect(Inlet& inlet, Outlet& outlet);
	static void disconnect(Inlet& inlet, Outlet& outlet);
};

}; // namespace lithe

#endif
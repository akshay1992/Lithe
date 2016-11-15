#include "Lithe/Atlas.h"
#include <stdexcept>

namespace lithe{

AtlasBase::AtlasBase(Range u_range, Range v_range) :
	u_range(u_range),
	v_range(v_range)
{
	// u_range = u_high - u_low;
	// v_range = v_high - v_low;

	// u_half_range = u_range / 2;
	// v_half_range = v_range / 2;

	// u_mid = u_low + ( u_range * 0.5 );
	// v_mid = v_low + ( v_range * 0.5 );
}

}; // namespace lithe
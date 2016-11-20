#ifndef SPHERICAL_TEST_ATLAS_HPP
#define SPHERICAL_TEST_ATLAS_HPP
#include "Lithe/SphericalAtlas.h"

using namespace lithe;

/// Merely exposes all parameters for testing.
class SphericalTestAtlas : public SphericalAtlas
{
public:
	SphericalTestAtlas(float u_low = -1, float u_high = 1, float v_low = -1, float v_high = 1, float radius = 1):
		SphericalAtlas(radius, Range(u_low, u_high), Range(v_low, v_high)) 
	{	}

	void setRadius(float radius) {_radius = radius;}

	using SphericalAtlas::u_range;
	using SphericalAtlas::v_range;
	using SphericalAtlas::_radius;
};

#endif //SPHERICAL_TEST_ATLAS_HPP
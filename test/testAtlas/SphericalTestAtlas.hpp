#ifndef SPHERICAL_TEST_ATLAS_HPP
#define SPHERICAL_TEST_ATLAS_HPP
#include "Atlas.h"

/// Merely exposes all parameters for testing.
class SphericalTestAtlas : public SphericalAtlas
{
public:
	using SphericalAtlas::SphericalAtlas;

	using SphericalAtlas::init;
	using SphericalAtlas::u_low;
	using SphericalAtlas::u_high;
	using SphericalAtlas::v_low;
	using SphericalAtlas::v_high;
	using SphericalAtlas::_radius;

	using SphericalAtlas::u_range;
	using SphericalAtlas::v_range;
	using SphericalAtlas::u_half_range;
	using SphericalAtlas::v_half_range;
	using SphericalAtlas::u_mid;
	using SphericalAtlas::v_mid;
};

#endif //SPHERICAL_TEST_ATLAS_HPP
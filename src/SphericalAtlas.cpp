#include "Lithe/SphericalAtlas.h"
#include <stdexcept>

namespace lithe {

SphericalAtlas::SphericalAtlas(float radius, Range u_range, Range v_range) :
	AtlasBase(u_range, v_range),
	_radius(radius),
	type(AtlasType::SPHERICAL)
{
	is_riemannian = true;
	reflect_constant = u_range.mid * u_range.half_range - (u_range.half_range * u_range.half_range) - u_range.mid;
}

float SphericalAtlas::u_cart(float x, float y, float z)
{
	float theta = atan2(y, x);
	return u_sph(theta, 0, _radius); // Passing dummy values to phi and radius since they don't affect u
}

float SphericalAtlas::v_cart(float x, float y, float z)
{
	float phi = acos(z / radius(x, y, z));
	return v_sph(0, phi, _radius); // Passing dummy values to theta and radius since they don't affect v
}

float SphericalAtlas::radius(float x, float y, float z)
{
	return sqrt(x*x + y*y + z*z);
}

float SphericalAtlas::u_sph(float theta, float phi, float r)
{
	check_sph_range(theta, phi, r);
	return ( theta / M_PI * u_range.half_range ) + u_range.mid;
}

float SphericalAtlas::v_sph(float theta, float phi, float r)
{
	check_sph_range(theta, phi, r);
	return ( phi / M_PI_2 * v_range.half_range ) + v_range.mid;
}

float SphericalAtlas::theta(float u, float v)
{
	check_uv_range(u, v);
	return (u-u_range.mid) / u_range.half_range * M_PI;
}

float SphericalAtlas::phi(float u, float v)
{
	check_uv_range(u, v);
	return (v-v_range.mid) / v_range.half_range * M_PI_2;
}

float SphericalAtlas::x(float u, float v)
{
	check_uv_range(u, v);
	return _radius * cos( theta(u, v) ) * cos( phi(u, v) ) ;
}

float SphericalAtlas::y(float u, float v)
{
	check_uv_range(u, v);
	return _radius * sin( theta(u, v) ) * cos( phi(u, v) ) ;
}

float SphericalAtlas::z(float u, float v)
{
	check_uv_range(u, v);
	return _radius * sin( phi(u, v) ) ;
}

float SphericalAtlas::distanceFunction(float u1, float v1, float u2, float v2)
{
	return acos( sin(phi(u1, v1))*sin(phi(u2, v2)) + cos(phi(u1, v1))*cos(phi(u2, v2))* cos(theta(u1, v1) - theta(u2, v2)) );
}

void SphericalAtlas::reflect(float u_in, float v_in, float& u_out, float& v_out)
{
	v_out = -v_in + 2.0 * v_range.mid;
	u_out =  reflect_constant + u_in;
	
	/// u = u_mid maps to -u_half_range; hence there is a tendancy for it to go negative
	if( u_out < u_range.minVal ) u_out += u_range.range;	//< This takes care of that condition
	check_uv_range(u_out, v_out);
}

/// Custom epsilon for comparisons in check_uv_range and check_sph_range
#define EPS_ATLAS 0.000001

void AtlasBase::check_uv_range(float u, float v)
{
	if( u < u_range.minVal || u > u_range.maxVal )
		throw std::range_error("U value out of range");

	if( v < v_range.minVal || v > v_range.maxVal ) 
		throw std::range_error("V value out of range");
}

void SphericalAtlas::check_sph_range(float theta, float phi, float r)
{
	if( (theta+M_PI) < -EPS_ATLAS || (theta-M_PI) > EPS_ATLAS )
		throw std::range_error("theta out of range");		
	if( (phi+M_PI_2) < -EPS_ATLAS || (phi-M_PI_2) > EPS_ATLAS )
		throw std::range_error("phi out of range");
}


}; //namespace lithe
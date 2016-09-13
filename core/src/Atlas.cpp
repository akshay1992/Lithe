#include "Atlas.h"
#include <stdexcept>

SphericalAtlas::SphericalAtlas(float u_low, float u_high, float v_low, float v_high, float radius) :
	u_low (u_low),
	u_high(u_high), 
	v_low(v_low), 
	v_high(v_high), 
	_radius(radius),
	type(ATLAS_TYPE_SPHERICAL)
{
	init();
}

void SphericalAtlas::init()
{
	u_range = u_high - u_low;
	v_range = v_high - v_low;

	u_mid = ( u_high - u_low ) * 0.5;
	v_mid = ( v_high - v_low ) * 0.5;
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
	return ( theta / M_PI * u_range ) + u_range;
}

float SphericalAtlas::v_sph(float theta, float phi, float r)
{
	check_sph_range(theta, phi, r);
	return ( phi / M_PI * 2.0 * v_range ) + v_mid;
}

float SphericalAtlas::theta(float u, float v)
{
	check_uv_range(u, v);
	return (u-u_mid) / u_range * M_PI;
}

float SphericalAtlas::phi( float u, float v)
{
	check_uv_range(u, v);
	return (v-v_mid) / v_range * M_PI * 0.5;
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
	/// TODO

}

void SphericalAtlas::check_uv_range(float u, float v)
{
	if( u < u_low || u > u_high )
		throw std::range_error("U value out of range");

	if( v < v_low || v > v_high ) 
		throw std::range_error("V value out of range");
}

void SphericalAtlas::check_sph_range(float theta, float phi, float r)
{
	if( theta < -M_PI || theta > M_PI )
		throw std::range_error("theta out of range");		
	if( phi < (-M_PI*0.5) || phi > (M_PI*0.5) )
		throw std::range_error("phi out of range");
}
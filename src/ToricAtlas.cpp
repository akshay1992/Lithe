#include "Lithe/ToricAtlas.h"
#include <stdexcept>

namespace lithe{

ToricAtlas::ToricAtlas(float R, float r, Range u_range, Range v_range) :
	AtlasBase(u_range, v_range),
	_r(r),
	_R(R)
{
	is_riemannian = true;
	if (R < 0 )
		throw std::range_error("Invalid torus. R is < 0 ");
	if (r < 0 )
		throw std::range_error("Invalid torus. r is < 0 ");
}

float ToricAtlas::u_cart(float x, float y, float z)
{
	float theta = atan2( y ,x);
	return theta / M_PI;
}

float ToricAtlas::v_cart(float x, float y, float z)
{
	float theta = u_cart(x, y, z) * M_PI;
	float x1 = _R * cos( theta) ;
	float y1 = _R * sin( theta) ;
	float z1 = 0;
	float dx = x-x1;
	float dy = y-y1;
	float dz = z-z1;
	// From the center of the 'tube' portion
	float dist_from_r_center = sqrt( dx*dx + dy*dy + dz*dz );
	float angle = asin((float) z / dist_from_r_center );

	// Offset angle if within _R
	float dist_of_xyz = sqrt( x*x + y*y + z*z );
	if(dist_of_xyz > _R)
		return angle / M_PI;
	else 
		return (M_PI - angle) / M_PI;
}

float ToricAtlas::x(float u, float v)
{
	check_uv_range(u, v);
	return ( _R + _r * cos(M_PI*v) ) * cos (M_PI * u);
}

float ToricAtlas::y(float u, float v)
{
	check_uv_range( u, v);
	return (_R + _r * cos(M_PI*v) ) * sin (M_PI * u);
}

float ToricAtlas::z(float u, float v)
{
	check_uv_range(u, v) ;
	return _r * sin(M_PI * v) ;
}

float ToricAtlas::distanceFunction(float u1, float v1, float u2, float v2)
{
	// No closed form expression available because inner ring has negative curvature and outer has positive.
	//  Need to use conditionals? 
	return -1;
}

}; // namespace lithe

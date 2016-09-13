#ifndef ATLAS_H
#define ATLAS_H

#include <cmath>

enum ATLAS_TYPE
{
	ATLAS_TYPE_SPHERICAL,
	ATLAS_TYPE_UNKOWN
};

/** @brief A utility class for working with a spherical surface
	
	This class can be used to map a rectangular surface in (u, v) to a 
	spherical surface in R3. By default it maps to a unit sphere, but can be 
	extended to a sphere of any radius. 

	Cartesian conventions followed:
		+x is forward
		+y is right
		+z is up

	Mappings: 
		[u_low, u_high] --> [-pi, pi] (Azimuth)
		[v_low, v_high] --> [-pi/2, pi/2] (Elevation)

*/
class SphericalAtlas
{
public:
	/// Defines a spherical atlas based on range of (U, V) surface and radius of sphere
	SphericalAtlas( float u_low = -1, float u_high = 1, float v_low = -1, float v_high = 1, float radius = 1);

	/// Returns u co-ordinate for a given cartesian co-ordinate (x, y, z)
	float u_cart(float x, float y, float z);

	/// Returns the v co-ordinate for a given spherical co-ordinate (x, y, z)
	float v_cart(float x, float y, float z);

	/// Returns the radius of the sphere for a given cartesian co-ordinate (x, y, z)
	float radius(float x, float y, float z);

	/// Returns u co-ordinate for a given cartesian co-ordinate (theta, phi, r)
	float u_sph(float theta, float phi, float r);

	/// Returns the v co-ordinate for a given spherical co-ordinate (theta, phi, r)
	float v_sph(float theta, float phi, float r);

	/// Returns the azimuthal angle mapped to the sphere.
	float theta(float u, float v);

	/// Returns the elevation angle mapped to the sphere.
	float phi( float u, float v);

	/// Returns the cartesian co-ordinate x. For conventions see SphericalAtlas
	float x(float u, float v); 

	/// Returns the cartesian co-ordinate y. For conventions see SphericalAtlas
	float y(float u, float v); 

	/// Returns the cartesian co-ordinate z. For conventions see SphericalAtlas
	float z(float u, float v); 

	/// Returns distance between (u1, v1) and (u2, v2) as mapped onto the sphereical surface
	float distanceFunction(float u1, float v1, float u2, float v2);

	/// Reflects (u_in, v_in) antipodally on the sphere. 
	void reflect(float u_in, float v_in, float& u_out, float& v_out);

	/// Throws an exception if the input co-ordinates are out of range. For conventions see SphericalAtlas
	void check_uv_range(float u, float v);

	/// Throws an exception if input co-ordinates are out of range. For conventions see SphericalAtlas
	void check_sph_range(float theta, float phi, float r);

	ATLAS_TYPE type;

protected:
	void init();

	float u_low, u_high, v_low, v_high;
	float _radius;

	float u_range, v_range;
	float u_mid, v_mid;
};




// Sample signal_to_sphere(Sample s)
// {
// 	if( s.az > +1 || s.az < -1)
// 		throw std::range_error("Az out of range");
// 	if( s.el > +1 || s.el < -1)
// 		throw std::range_error("El out of range");
// 	if( s.d > +1 || s.d < -1)
// 		throw std::range_error("d out of range");

// 	float az_sph = s.az * M_PI;
// 	float el_sph = s.el * M_PI/2.0;	
// 	float r_sph = Sample::getGlobalRadius() * (1.0 - d); 
// 	return Sample(audio, az_sph, el_sph, r_sph);
// }

/** @brief Converts a sample's signals to cartesian co-ordinate values
	Signal co-ordinate convention (inherently spherical)
	az: {-1, +1} -> { -180, +180 } (0 = front; +/- 180 = back)
	el: {-1, +1} -> { -90, +90 }  ( +90 = directly above, -90 directly below)
	d: ?? (TODO)

	Cartesian co-ordinate convention
	+x is forward
	+y is left
	+z is up
*/
// void signal_to_cartesian(float& x, float& y, float& z)
// {
// 	Sample sph = to_spherical();		
// 	x = sph.d * cos( sph.az ) * cos( sph.el );
// 	y = sph.d * -sin( sph.az) * cos( sph.el );
// 	z = sph.d * sin( sph.el );
// }


#endif //ATLAS_H
#ifndef SPHERICAL_ATLAS_H
#define SPHERICAL_ATLAS_H

#include "Lithe/Atlas.h"

namespace lithe{


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

	@ingroup Atlas	

*/
	
class SphericalAtlas : public AtlasBase
{
public:
	/// Defines a spherical atlas based on range of (U, V) surface and radius of sphere
	SphericalAtlas(float radius = 1, Range u_range = Range(-1, 1), Range v_range = Range(-1, 1));

	float getRadius(void) { return _radius;}

	/// Returns u co-ordinate for a given cartesian co-ordinate (x, y, z)
	virtual float u_cart(float x, float y, float z) override;

	/// Returns the v co-ordinate for a given spherical co-ordinate (x, y, z)
	virtual float v_cart(float x, float y, float z) override;

	/// Returns the radius of the sphere for a given cartesian co-ordinate (x, y, z)
	static float radius(float x, float y, float z);

	/// Returns u co-ordinate for a given cartesian co-ordinate (theta, phi, r)
	float u_sph(float theta, float phi, float r);

	/// Returns the v co-ordinate for a given spherical co-ordinate (theta, phi, r)
	float v_sph(float theta, float phi, float r);

	/// Returns the azimuthal angle mapped to the sphere.
	float theta(float u, float v);

	/// Returns the elevation angle mapped to the sphere.
	float phi( float u, float v);

	/// Returns the cartesian co-ordinate x. For conventions see SphericalAtlas
	virtual float x(float u, float v) override; 

	/// Returns the cartesian co-ordinate y. For conventions see SphericalAtlas
	virtual float y(float u, float v) override; 

	/// Returns the cartesian co-ordinate z. For conventions see SphericalAtlas
	virtual float z(float u, float v) override; 

	/// Returns distance between (u1, v1) and (u2, v2) as mapped onto the sphereical surface
	virtual float distanceFunction(float u1, float v1, float u2, float v2) override;

	/// Reflects (u_in, v_in) antipodally on the sphere. 
	void reflect(float u_in, float v_in, float& u_out, float& v_out);

	/// Throws an exception if input co-ordinates are out of range. For conventions see SphericalAtlas
	void check_sph_range(float theta, float phi, float r);

	virtual AtlasType getType(void) override {return AtlasType::SPHERICAL; }

protected:
	using AtlasBase::AtlasBase;
	/** @brief The radius of the sphere that (u, v) is mapped to. 
		For consistancy, this can only be set upon instantiation and new instances of the Atlas must be 
		instantiated for manifolds of different radii.
	*/
	float _radius;

	/// This constant is used to compute the antipodal reflection
	float reflect_constant;
};

}; // namespace lithe

#endif
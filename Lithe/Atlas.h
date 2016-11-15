#ifndef ATLAS_H
#define ATLAS_H

#include <cmath>

#include "Lithe/Utils.h"

namespace lithe {

/** @brief Used to identify the type of Atlas
	Contains all atals types provided by lithe
	@ingroup Atlas
*/

enum class AtlasType : unsigned int
{
	DEFAULT, 
	SPHERICAL,
	TORIC,
	UNKOWN
};

/** @brief Abstract base class for defining an Atlas
	
	Please see descriptions the pure virtual methods to override in order to use this class.
	Also see SphericalAtlas as an example.

	@ingroup Atlas
*/

class AtlasBase
{
public:
	AtlasBase(Range u_range = Range(-1,1), Range v_range=Range(-1,1));

	/// Returns u co-ordinate for a given cartesian co-ordinate (x, y, z)
	virtual float u_cart(float x, float y, float z)=0;

	/// Returns v co-ordinate for a given spherical co-ordinate (x, y, z)
	virtual float v_cart(float x, float y, float z)=0;

	/// Returns the cartesian co-ordinate x for given manifold co-ordinates (u, v). 
	virtual float x(float u, float v)=0;

	/// Returns the cartesian co-ordinate y for given manifold co-ordinates (u, v). 
	virtual float y(float u, float v)=0;

	/// Returns the cartesian co-ordinate z for given manifold co-ordinates (u, v). 
	virtual float z(float u, float v)=0;

	/// Returns distance between (u1, v1) and (u2, v2) as mapped onto the manifold
	virtual float distanceFunction(float u1, float v1, float u2, float v2)=0;

	/// Throws an exception if the input co-ordinates are out of range. 
	void check_uv_range(float u, float v);

	/// @brief Returns true if the manifold is a riemannian manifold (i.e., it has a valid distance function)
	bool isRiemannian(void) { return is_riemannian; }

protected:
	float _radius;
	Range u_range;
	Range v_range;

	bool is_riemannian;
};


}; //namespace lithe

/// @}


#endif //ATLAS_H
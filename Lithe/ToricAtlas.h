#ifndef TORIC_ATLAS_H
#define TORIC_ATLAS_H

#include "Lithe/Atlas.h"

namespace lithe{

/** @brief 
	

	@ingroup Atlas

*/

class ToricAtlas : public AtlasBase
{
	ToricAtlas(float R, float r, float u_low = -1, float u_high = 1, float v_low = -1, float v_high = 1);

	/// Returns u co-ordinate for a given cartesian co-ordinate (x, y, z)
	virtual float u_cart(float x, float y, float z) override;

	/// Returns v co-ordinate for a given spherical co-ordinate (x, y, z)
	virtual float v_cart(float x, float y, float z) override;

	/// Returns the cartesian co-ordinate x for given manifold co-ordinates (u, v). 
	virtual float x(float u, float v) override;

	/// Returns the cartesian co-ordinate y for given manifold co-ordinates (u, v). 
	virtual float y(float u, float v) override;

	/// Returns the cartesian co-ordinate z for given manifold co-ordinates (u, v). 
	virtual float z(float u, float v) override;

	/// Returns distance between (u1, v1) and (u2, v2) as mapped onto the manifold
	virtual float distanceFunction(float u1, float v1, float u2, float v2) override;

	/// Throws an exception if the input co-ordinates are out of range. 
	void check_uv_range(float u, float v);

	/// @brief Returns true if the manifold is a riemannian manifold (i.e., it has a valid distance function)
	bool isRiemannian(void) { return is_riemannian; }

protected:
	float u_low, u_high, v_low, v_high;
	float _radius;

	float u_range, v_range;
	float u_half_range, v_half_range;
	float u_mid, v_mid;

	bool is_riemannian;

	/// @brief R is the distance from the center of the tube to the center of the torus,
	float _R;
	
	/// @bried r is the radius of the tube.
	float _r;
};


}; // namespace lithe


#endif //TORIC_ATLAS_H
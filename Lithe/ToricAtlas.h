#ifndef TORIC_ATLAS_H
#define TORIC_ATLAS_H

#include "Lithe/Atlas.h"

namespace lithe{

/** @brief Used to map from a rectangle to a Torus. 
	@param R is the distance from the center of the tube to the center of the torus,
	@param r is the radius of the tube.
	@param u_range is the range of the u dimension of the rectangle (deafults to [-1,1])
	@param v_range is the range of the v dimension of the rectangle (deafults to [-1,1])

	Cartesian conventions followed:
		+x is forward
		+y is right
		+z is up

	Mappings: 
		[u_low, u_high] --> [-pi, pi] ("Azimuth" - measured from centre of torus, with respect to +x axis)
		[v_low, v_high] --> [-pi, pi] ("Elevation" - measured slong the girth of the torus)		


	@ingroup Atlas

*/

class ToricAtlas : public AtlasBase
{
public:
	ToricAtlas(float R, float r, Range u_range = Range(-1, 1), Range v_range = Range(-1, 1));

	/// @brief Returns u co-ordinate for a given cartesian co-ordinate (x, y, z)
	virtual float u_cart(float x, float y, float z) override;

	/// Returns v co-ordinate for a given spherical co-ordinate (x, y, z)
	virtual float v_cart(float x, float y, float z) override;

	/// @brief Returns the cartesian co-ordinate x for given manifold co-ordinates (u, v). 
	virtual float x(float u, float v) override;

	/// @brief Returns the cartesian co-ordinate y for given manifold co-ordinates (u, v). 
	virtual float y(float u, float v) override;

	/// @brief Returns the cartesian co-ordinate z for given manifold co-ordinates (u, v). 
	virtual float z(float u, float v) override;

	/// @brief Returns distance between (u1, v1) and (u2, v2) as mapped onto the manifold
	virtual float distanceFunction(float u1, float v1, float u2, float v2) override;

	/// @brief Returns the type of Atlas.
	virtual AtlasType getType(void) override { return AtlasType::TORIC; }

protected:
	using AtlasBase::AtlasBase;
	/// @brief R is the distance from the center of the tube to the center of the torus,
	float _R;
	
	/// @bried r is the radius of the tube.
	float _r;
};


}; // namespace lithe


#endif //TORIC_ATLAS_H
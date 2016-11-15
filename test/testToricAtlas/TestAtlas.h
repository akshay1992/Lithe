#ifndef TEST_TORIC_ATLAS_H
#define TEST_TORIC_ATLAS_H

#include "Lithe/LitheCore.h"

using namespace lithe;

class ToricTestAtlas : public ToricAtlas {
public:

	ToricTestAtlas(float R, float r, lithe::Range u_range = lithe::Range(-1, 1), lithe::Range v_range = lithe::Range(-1, 1)) 
	: ToricAtlas(R, r, u_range, v_range)
	{

	}

	Range& getURange(void) {return u_range;}
	Range& getVRange(void) {return v_range;}
	float getR(void) {return _R; }
	float getr(void) {return _r;}

	using ToricAtlas::u_range;
	using ToricAtlas::v_range;
	using ToricAtlas::_r;
	using ToricAtlas::_R;
};

#endif
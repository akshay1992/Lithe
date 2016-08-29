#ifndef SAMPLE_H
#define SAMPLE_H

#include "math.h"
#include <stdexcept>

typedef float sample_t;

class Sample
{
public:
	Sample(sample_t audio=0, sample_t az=0, sample_t el=0, sample_t d=0) :
		audio(audio), 
		az(az), 
		el(el),
		d(d)		
	{	}

	Sample to_spherical(void)
	{
		if( az > +1 || az < -1)
			throw std::range_error("Az out of range");
		if( el > +1 || el < -1)
			throw std::range_error("El out of range");
		if( d > +1 || d < -1)
			throw std::range_error("d out of range");

		float az_sph = az * M_PI;
		float el_sph = el * M_PI/2.0;	
		float r_sph = r();
		return Sample(audio, az_sph, el_sph, d);
	}

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
	void to_cartesian(float& x, float& y, float& z)
	{
		Sample sph = to_spherical();
		x = sph.r() * cos( sph.az ) * sin( sph.el );
		y = sph.r() * -sin( sph.az) * sin( sph.el );
		z = sph.r() * cos( sph.el );
	}

	sample_t audio;
	sample_t az;
	sample_t el;
	sample_t d;

	static void setGlobalRadius(float r) { mRadius = r; }
	static float getGlobalRadius(void) { return mRadius; }

private:
	float r(void)
	{
		if ( d > +1 || d < -1 )
			throw std::range_error("d out of range");
		if (mRadius < 0 )
			throw std::range_error("mRadius must always be positive");
		
		// Linear map 
		float r = mRadius * (1-d); 

		return r;
	}

	/// Radius of imaginary sphere upon which the signals are mapped (defaults to unit sphere)
	static float mRadius;
};

#endif //SAMPLE_H
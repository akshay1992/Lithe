#ifndef SAMPLE_H
#define SAMPLE_H

#include "math.h"
#include <exception>
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
		return Sample(audio, az_sph, el_sph, d);
	}

	Sample to_cartesian(void)
	{
		Sample sph = to_spherical();
		float x = sph.d * sin( sph.el );
		float y = sph.d * sin( sph.el );
		float z = sph.d * cos( sph.el );
		return Sample();
	}

	sample_t audio;
	sample_t az;
	sample_t el;
	sample_t d;
};


#endif //SAMPLE_H
#ifndef ATLAS_H
#define ATLAS_H

#include "Sample.h"

/** @brief Abstract class for defining a co-ordinate map

*/
class Atlas
{

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
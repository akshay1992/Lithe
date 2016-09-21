#ifndef SAMPLE_H
#define SAMPLE_H

#include "math.h"
#include <stdexcept>

#include "Lithe/Atlas.h"

/** @brief A single audio sample as defined by Lithe
	
	@ingroup Other
*/
template<typename T = float>
class SampleT
{
public:
	SampleT(T audio=0, T az=0, T el=0, T d=0, AtlasType preferred_atlas = ATLAS_TYPE_DEFAULT) :
		audio(audio), 
		az(az), 
		el(el),
		d(d), 
		preferred_atlas(preferred_atlas)
	{	}

	/// @brief A single sample of audio. This is in mono only. 
	T audio;
	/// @brief An elevation-like parameter. Usually, this will be the u parameter in an Atlas
	T az;
	/// @brief The second spatial parameter. Usually, this will be the v parameter in an Atlas
	T el;
	/// @brief The third parameter. Usually this is used to denote distance. However, the metric is defined by downstream modules.
	T d;

	/** @brief Used to communicate a preferred atlas to downstream Node instances. Does not enforce.
	*/
	AtlasType preferred_atlas;
};

typedef SampleT<float> Sample;

#endif //SAMPLE_H
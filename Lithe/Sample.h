#ifndef SAMPLE_H
#define SAMPLE_H


#include "Lithe/Utils.h"
#include "Lithe/Atlas.h"

namespace lithe{

/** @brief A single audio sample as defined by Lithe
	
	@ingroup Utilities
*/
template<typename T = float>
class SampleT
{
public:
	SampleT(T audio=0, T az=0, T el=0, T d=0, AtlasType preferred_atlas = AtlasType::DEFAULT) :
		audio(audio), 
		az(az), 
		el(el),
		d(d), 
		preferred_atlas(preferred_atlas)
	{	}
	~SampleT() {}

	/// @brief A single sample of audio. This is in mono only. 
	T audio;
	/// @brief An elevation-like parameter. Usually, this will be the u parameter in an Atlas
	T az;
	/// @brief The second spatial parameter. Usually, this will be the v parameter in an Atlas
	T el;
	/// @brief The third parameter. Usually this is used to denote distance. However, the metric is defined by downstream modules.
	T d;

	/// @brief For the convenience of accessing using an index
	T operator[](int index)
	{
		switch(index)
		{	
			case 0: return audio;
			case 1: return az;
			case 2: return el;
			case 3: return d;
			default: throw std::range_error("Invalid index for accessing Sample");
		}
	}

	/** @brief Used to set the range of the values of the values in Sample

		Warning: This sets it for all SampleT instances in the program. 
	*/
	static void setRange(RangeT<T> newRange) { SampleRange = newRange; }

	/// @brief Returns the default ranges for SampleT
	static inline RangeT<T> getRange(void) { return SampleRange; }

	/** @brief Used to communicate a preferred atlas to downstream Node instances. Does not enforce.
	*/
	AtlasType preferred_atlas;

private:
	/// @brief specifies the of a sample's values (applied the same to audio, az, el, and d)
	static RangeT<T> SampleRange;
};

// Allocating SampleRange
template< typename T >
RangeT<T> SampleT<T>::SampleRange;

/// @brief A shorthand for a Sample with float
typedef SampleT<float> Sample;

}; // namespace lithe

#endif //SAMPLE_H
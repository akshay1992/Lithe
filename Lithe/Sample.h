#ifndef SAMPLE_H
#define SAMPLE_H

#include "math.h"
#include <stdexcept>

#include "Lithe/Atlas.h"

/** @brief A convenience struct to specify the range of a parameter.

	Defaults to a float in (-1, 1)

	@ingroup Other
*/
template< typename T = float >
struct RangeT
{
	RangeT( T min = -1, T max = 1) : minVal(min), maxVal(max) 
	{ 
		range = maxVal - minVal; 
		half_range =  (T) range / 2.0;
		if( range <=0 )
			throw std::range_error("RangeT invalid. Is <= 0" );
	};

	T minVal;
	T maxVal;
	T range;
	T half_range;

	/// @brief Checks if a value is within the specified range. 
	void check(T val)
	{
		if( val > maxVal )
			throw std::range_error("RangeT value exceeds range");
		if( val < minVal )
			throw std::range_error("RangeT value beneath range");
	}
};

/// @brief Shorthand for a float RangeT
typedef RangeT<float> Range;

/// @brief Utility function for mapping from one range to another
template<typename T >
T map(T value, RangeT<T> fromRange, RangeT<T> toRange)
{
	/// Linear mapping function (for now)
	return ( (value-fromRange.minVal)*(toRange.maxVal-toRange.minVal)/(fromRange.maxVal-fromRange.minVal) ) + toRange.minVal;
}

/// @brief Wraps a value to the other side if out of range. 
template<typename T> 
T wrap(T value, RangeT<T> wrapRange)
{
	if( value > wrapRange.maxVal )
	{
		return wrap<T>(value-wrapRange.range, wrapRange);
	}
	else if( value < wrapRange.minVal )
	{
		return wrap<T>(value+wrapRange.range, wrapRange);
	}
	else
	{	
		return value;
	}
}

/// @brief DC Shifts an input value by a an amount specified. Wraps if the shift puts it out of range.
template< typename T> 
T dc_shift(T value, T shift, RangeT<T> range)
{
	return wrap<T>(value + wrap<T>(shift, range), range);
}

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

#endif //SAMPLE_H
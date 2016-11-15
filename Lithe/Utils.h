#ifndef LITHE_UTILS_H
#define LITHE_UTILS_H

#include "math.h"
#include <stdexcept>

namespace lithe{

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
		mid = range*0.5 + minVal;
		half_range =  (T) range / 2.0;
		if( range <=0 )
			throw std::range_error("RangeT invalid. Is <= 0" );
	};

	T minVal;
	T maxVal;
	T range;
	T half_range;
	T mid;

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
T linear_map(T value, RangeT<T> fromRange, RangeT<T> toRange)
{
	return ( (value - fromRange.minVal) * toRange.range / fromRange.range ) + toRange.minVal;
	// return ( (value-fromRange.minVal)*(toRange.maxVal-toRange.minVal)/(fromRange.maxVal-fromRange.minVal) ) + toRange.minVal;
}

/// @brief Wraps a value to the other side if out of range. 
template<typename T> 
T wrap(T value, RangeT<T> wrapRange)
{
	if( value > wrapRange.maxVal )
	{
		return wrap<T>(value-(T)wrapRange.range, wrapRange);
	}
	else if( value < wrapRange.minVal )
	{
		return wrap<T>(value+ (T)wrapRange.range, wrapRange);
	}
	else
	{	
		return value;
	}
}

/// @brief Clips a value to the bounds of clipRange if it exceeds
template< typename T>
T clip( T value, RangeT<T> clipRange)
{
	if( value > clipRange.maxVal )
	{
		return clipRange.maxVal;
	}
	else if( value < clipRange.minVal )
	{
		return clipRange.minVal;
	}
	else 
	{
		return value;
	}
}

/// @brief DC Shifts an input value by a an amount specified. Wraps if the shift puts it out of range.
template< typename T> 
T dc_shift_wrap(T value, T shift, RangeT<T> range)
{
	return wrap<T>(value + wrap<T>(shift, range), range);
}

/// @brief DC Shifts an input value by a an amount specified. Clips if the shift puts it out of range.
template< typename T>
T dc_shift_clip(T value, T shift, RangeT<T> range)
{
	return clip<T>(value+ (T)shift, range);
}

/* @brief Modulates about parameter_val using the modulation_signal. 

	NOTE: The modulation_signal is mapped to the same range as the parameter_val to enaure proper modulation. 
*/
template< typename T> 
T modulate_clip(T parameter_val, T modulation_signal, RangeT<T> modulation_range, RangeT<T> parameter_range)
{
	T modulation_signal_mapped = linear_map<float>(modulation_signal, modulation_range, parameter_range);
	return dc_shift_clip<T>( modulation_signal, parameter_val, parameter_range);
}

/// @brief Modulates about parameter_val using the modulation_signal. If it exceeds range, it clips
template< typename T> 
T modulate_wrap(T parameter_val, T modulation_signal, RangeT<T> modulation_range, RangeT<T> parameter_range)
{
	T modulation_signal_mapped = linear_map<float>(modulation_signal, modulation_range, parameter_range);
	return dc_shift_wrap<T>( modulation_signal, parameter_val, parameter_range);
}

}; //namespace lithe

#endif
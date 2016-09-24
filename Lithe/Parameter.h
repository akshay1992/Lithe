#ifndef PARAMETER_H
#define PARAMETER_H

/** @brief A convenience struct to specify the range of a parameter.

	Defaults to a float in (-1, 1)

	@ingroup Other
*/
template< typename T = float >
struct RangeT
{
	RangeT( T min = -1, T max = 1) : minVal(min), maxVal(max) {};
	T minVal;
	T maxVal;
};

typedef RangeT<float> Range;


/** @brief A parameter used within a module. TODO:  make everything thread safe

	@ingroup Other
*/
template< typename T> 
class ParameterT
{
	ParameterT(T default_value) : mVal(default_value), mDefaultVal(default_value)
	{	}

	T get() { return mVal; }
	void set(T val) { mVal = val; }
	void reset(void) { mVal = mDefaultVal; }

private:
	T mVal;
	T mDefaultVal;
};

typedef ParameterT<float> Parameter;


#endif //PARAMETER_H
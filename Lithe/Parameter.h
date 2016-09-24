#ifndef PARAMETER_H
#define PARAMETER_H

#include <stdexcept>
#include "Lithe/Sample.h"
#include "Lithe/Inlet.h"

#ifndef SAMPLE_H
pooop
#endif

/** @brief A parameter used within a module. TODO:  make everything thread safe

	@ingroup Other
*/
template< typename T> 
class ParameterT
{
	ParameterT(T default_value) : mVal(default_value), mDefaultVal(default_value)
	{	}
	~ParameterT()
	{	}

	RangeT<T> mappingBounds;

	T get() { return mVal; }
	void set(T val) { mVal = val; }
	void reset(void) { mVal = mDefaultVal; }

	/// @brief sets up a paremeter to be modulated by an inlet signal
	void link(Inlet& inlet, int sampleValIndex)
	{
		inlet_ref = &inlet;
		sampleValueIndex = sampleValIndex;
		linked_to_inlet = true;
	}

private:
	Inlet* inlet_ref;	///< inlet of the modulating signal
	int sampleValueIndex; ///< selects between audio, el, az, d
	bool linked_to_inlet;
	T mVal;
	T mDefaultVal;
};

typedef ParameterT<float> Parameter;

#endif //PARAMETER_H
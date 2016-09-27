#ifndef PARAMETER_H
#define PARAMETER_H

#include <stdexcept>
#include "Lithe/Sample.h"

class Inlet; // Forward declaration because of circular dependencies

/// @brief A way to select a type of attenuator while instantiating a ParameterT
enum AttenuatorType
{
	ATTENUATOR, 
	ATTENUVERTER,
	NONE
};

/** @brief A parameter used within a module. TODO:  make everything thread safe

	@ingroup Other
*/
template< typename T> 
class ParameterT
{
public:
	ParameterT(T default_value, RangeT<T> range, AttenuatorType att_type = NONE) : 
		mDefaultVal(default_value),
		mappingRange(range),
		linked_to_inlet(false)
	{
		try 
		{
			reset();
		}
		catch(std::range_error)
		{
			throw std::range_error("ParameterT default value not within range");
		}

		switch(att_type)
		{
			case ATTENUATOR: att = new ParameterT<float>(0, Range(0,1)); break;
			case ATTENUVERTER: att = new ParameterT<float>(0, Range(-1,1)); break;
			default:
			case NONE: att = NULL;
		}
	}

	/// @brief Getter for the parameter value. TODO: Add thread safety
	T get()
	{
		/// Lock mVal??
		return mVal;
		/// Unlock mVal??
	}

	/// @brief Getter for the parameter value with modulation added. TODO: Add thread safety
	T getModulated()
	{
		T return_val;
		/// Lock mVal??	
		if( linked_to_inlet && inlet_ref->isConnected() ) 
		{
			return_val = modulate();
		}
		else
		{
			return_val = get();			
		}
		/// Unlock mVal??
		return return_val;
	}


	/** @brief Default type of modulation using an inlet. 
	*/
	virtual inline T modulate()
	{
		T modulating_signal = att->get() * inlet_ref->getSample()[sampleValueIndex];
		return mVal + map<T>(modulating_signal , SampleT<T>::getRange(), mappingRange);
	}

	void set(T val) 
	{
		mappingRange.check(val);
		mVal = val;  
	}
	
	void reset(void) { set(mDefaultVal); }

	/// @brief range to which the incomping SampleT signal must be mapped. 
	RangeT<T> mappingRange;

	/// @brief sets up a paremeter to be modulated by an inlet signal. (Do this only once!
	void link(Inlet& inlet, int sampleValIndex)
	{
		inlet_ref = &inlet;
		sampleValueIndex = sampleValIndex;
		linked_to_inlet = true;
	}

	ParameterT<float>* att; ///< Attenuator/Attenuverter (instantiated in constructor)

private:
	Inlet* inlet_ref;	///< inlet of the modulating signal
	int sampleValueIndex; ///< selects between audio, el, az, d
	bool linked_to_inlet;
	T mVal;
	T mDefaultVal;
};

typedef ParameterT<float> Parameter;

#endif //PARAMETER_H
#ifndef PARAMETER_FIELD_H
#define PARAMETER_FIELD_H

#include "Lithe/Atlas.h"

namespace lithe {

template< class TAtlas >
class ParamterFieldBase
{
public:
	ParameterFieldBase() {	}

	TAtlas atlas;

	/// @brief Returns the value of the field at a certain point
	virtual float val(float u, float v) = 0;
};


template < class TAtlas >
class ConstantPField : ParameterFieldBase< TAtlas >
{
private:
	ConstantPField( float value = 0 )  : mValue(value)
	{

	}

	void setValue( float value ) { mValue = value; }


	virtual float val(float u, float v) 
	{
		return -12;
	}

	float mValue;
};

typedef ConstantPField<float> ConstantPFieldF;

}; // namespace lithe

#endif // PARAMETER_FIELD_H
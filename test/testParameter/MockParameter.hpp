#ifndef MOCK_PARAMETER_HPP
#define MOCK_PARAMETER_HPP

#include "Lithe/LitheCore.h"
#include "gmock/gmock.h"

class MockParameter : public Parameter
{
public:
	using Parameter::ParameterT;
	MOCK_METHOD0(modulate, float() );
};


#endif //MOCK_PARAMETER_HPP
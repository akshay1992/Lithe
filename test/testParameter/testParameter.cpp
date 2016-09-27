#include "testParameter.h"
#include "MockInlet.hpp"
#include "MockParameter.hpp"
ParameterTest::ParameterTest(void) {}

ParameterTest::~ParameterTest(void) {}

void ParameterTest::SetUp(void) {}

void ParameterTest::TearDown(void) {}

TEST_F(ParameterTest, default_value_constructor_test)
{
	Parameter a(440, Range(100, 12000));
	EXPECT_FLOAT_EQ( a.get(), 440);

	ParameterT<int> b(12, RangeT<int>(0, 128));
	EXPECT_EQ( b.get(), 12);

	// Out of range default value
	EXPECT_THROW( ParameterT<float> param(111, Range(9, 9.9)), std::range_error);

	ParameterT<float> a1 = ParameterT<float>( 129, Range(33, 3000), ATTENUATOR);
	EXPECT_FLOAT_EQ( a1.get(), 129);
	EXPECT_FLOAT_EQ( a1.att->mappingRange.minVal, 0);
	EXPECT_FLOAT_EQ( a1.att->mappingRange.maxVal, 1);
	a1 = ParameterT<float>( 129, Range(33, 3000), ATTENUVERTER);
	EXPECT_FLOAT_EQ( a1.get(), 129);
	EXPECT_FLOAT_EQ( a1.att->mappingRange.minVal, -1);
	EXPECT_FLOAT_EQ( a1.att->mappingRange.maxVal, 1);

	a1 = ParameterT<float>( 129, Range(33, 3000), NONE);
	EXPECT_FLOAT_EQ( a1.get(), 129);
	EXPECT_TRUE( a1.att == NULL);
}

TEST_F(ParameterTest, setter_test)
{
	Parameter a(0, Range(0, 1));
	a.set(0.873);
	EXPECT_FLOAT_EQ( a.get() , 0.873);	

	EXPECT_THROW( a.set(12) , std::range_error);
}

TEST_F(ParameterTest, set_reset_test)
{
	Parameter a(0, Range(-100, 100));
	a.set(12);
	EXPECT_FLOAT_EQ( a.get() , 12);
	a.set(-9);
	EXPECT_FLOAT_EQ( a.get() , -9);
	a.reset();
	EXPECT_FLOAT_EQ( a.get(), 0);
}

TEST_F(ParameterTest, modulation_algorithm_test)
{
	Parameter param(0.5, Range(-1, 1));
	EXPECT_FLOAT_EQ( param.modulate( 0.1 ), 0.5+0.1) ;

	//////// TODO

}

TEST_F (ParameterTest, modulation_mechanism_test)
{
	Parameter param(0, Range(-100, 100));
	MockInlet inlet;

	/// Modulate using the audio signal.
	param.link(inlet, 0);
	inlet.injectSampleValue( Sample(0, 0, 0, 0) );

	/////// TODO
}
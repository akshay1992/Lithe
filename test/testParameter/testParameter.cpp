#include "testParameter.h"

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

	ParameterT<float> a1 = ParameterT<float>( 129, Range(33, 3000), ATTENUATOR);
	EXPECT_FLOAT_EQ( a1.get(), 129);
	EXPECT_FLOAT_EQ( a1.att->mappingRange.minVal, 0);
	EXPECT_FLOAT_EQ( a1.att->mappingRange.maxVal, 1);
	a1 = ParameterT<float>( 129, Range(33, 3000), ATTENUVERTER);
	EXPECT_FLOAT_EQ( a1.get(), 129);
	EXPECT_FLOAT_EQ( a1.att->mappingRange.minVal, -1);
	EXPECT_FLOAT_EQ( a1.att->mappingRange.maxVal, 1);
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
#include "testParameter.h"

ParameterTest::ParameterTest(void) {}

ParameterTest::~ParameterTest(void) {}

void ParameterTest::SetUp(void) {}

void ParameterTest::TearDown(void) {}

TEST_F(ParameterTest, range_test)
{
	Range r(-1, 1);
	EXPECT_FLOAT_EQ(r.minVal, -1);
	EXPECT_FLOAT_EQ(r.maxVal, +1);
	EXPECT_FLOAT_EQ(r.range, 2);
	EXPECT_FLOAT_EQ(r.half_range, 1);

	Range r2(-128, 128);
	EXPECT_EQ(r2.minVal, -128);
	EXPECT_EQ(r2.maxVal, 128);
	EXPECT_EQ(r2.half_range, 128);
	EXPECT_EQ(r2.range, 256);
}

TEST_F(ParameterTest, map_test)
{
	Range r(-1, 1);
	Range r2(-128, 128);
	EXPECT_FLOAT_EQ( map<float>(0.5, r, r2), +64 ); 
	EXPECT_FLOAT_EQ( map<float>(1, r, r2), 128 ); 
	EXPECT_FLOAT_EQ( map<float>(-1, r, r2), -128 ); 
	EXPECT_FLOAT_EQ( map<float>(0, r, r2), 0 ); 
	EXPECT_FLOAT_EQ( map<float>(-0.25, r, r2), -32 ); 

	// Testing invertibility 
	EXPECT_FLOAT_EQ( map<float>(-1, r, r2), map<float>(map<float>(-128, r2, r), r, r2));

	r = Range(-1, 1);
	r2 = Range(0, 100);

	EXPECT_FLOAT_EQ( map<float>(-0.9, r, r2) , 5);
	EXPECT_FLOAT_EQ( map<float>(0.6, r, r2) , 80);
	EXPECT_FLOAT_EQ( map<float>(-1, r,r2), 0);
	EXPECT_FLOAT_EQ( map<float>(+1, r,r2), 100);
	EXPECT_FLOAT_EQ( map<float>(0, r,r2), 50);
}

TEST_F(ParameterTest, dc_shift_test)
{
	Range r( -1, 1);
	EXPECT_FLOAT_EQ( dc_shift<float>(0, +0.2, r), 0.2);
	EXPECT_FLOAT_EQ( dc_shift<float>(0.6, -0.2, r), 0.4);
	EXPECT_FLOAT_EQ( dc_shift<float>(-0.3, +0.2, r), -0.1);
	EXPECT_FLOAT_EQ( dc_shift<float>(-0.9, 0.02, r), -0.88);
	
	EXPECT_FLOAT_EQ( dc_shift<float>(0.8, +0.3, r), -0.9);
	EXPECT_FLOAT_EQ( dc_shift<float>(-0.7, -2, r), -0.7);

	/// Looks like an error accumulates
	EXPECT_FLOAT_EQ( dc_shift<float>(0.7, -3, r), -0.7);
	EXPECT_FLOAT_EQ( dc_shift<float>(-0.4, +5, r), -0.4);
}
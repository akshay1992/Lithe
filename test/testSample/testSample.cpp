#include "testSample.h"

SampleTest::SampleTest(void) {}

SampleTest::~SampleTest(void) {}

void SampleTest::SetUp(void) {}

void SampleTest::TearDown(void) {}

TEST_F (SampleTest, constructorTest)
{
	Sample s;
	EXPECT_FLOAT_EQ(s.audio, 0);
	EXPECT_FLOAT_EQ(s.az, 0);
	EXPECT_FLOAT_EQ(s.el, 0);
	EXPECT_FLOAT_EQ(s.d, 0);
	EXPECT_EQ(s.preferred_atlas, ATLAS_TYPE_DEFAULT);

	s = Sample(0.2, 0.3, -0.124, 0.56, ATLAS_TYPE_SPHERICAL);
	EXPECT_FLOAT_EQ(s.audio, 0.2);
	EXPECT_FLOAT_EQ(s.az, 0.3);
	EXPECT_FLOAT_EQ(s.el, -0.124);
	EXPECT_FLOAT_EQ(s.d, 00.56);
	EXPECT_EQ(s.preferred_atlas, ATLAS_TYPE_SPHERICAL);
}

TEST_F (SampleTest, indexingTest)
{
	Sample samp = Sample(0.1, -0.23, 0.43, -0.12);
	EXPECT_FLOAT_EQ(samp[0], 0.1);
	EXPECT_FLOAT_EQ(samp[1], -0.23);
	EXPECT_FLOAT_EQ(samp[2], 0.43);
	EXPECT_FLOAT_EQ(samp[3], -0.12);
}

TEST_F (SampleTest, SampleRangeTest)
{
	// Checking the defaults
	Range r = Sample::getRange();  
	EXPECT_FLOAT_EQ( r.minVal, -1);
	EXPECT_FLOAT_EQ( r.maxVal, +1);

	// Changing the defaults
	Sample::setRange( Range(-1.02, 3.43) );  
	r = Sample::getRange();  
	EXPECT_FLOAT_EQ( r.minVal, -1.02);
	EXPECT_FLOAT_EQ( r.maxVal, +3.43);
}

TEST_F(SampleTest, range_test)
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

	// Min value is more than max value. 
	EXPECT_THROW( r2 = Range(12, -2), std::range_error);
	EXPECT_THROW( RangeT<int> r4 = RangeT<int>(12, -2), std::range_error);
}

TEST_F(SampleTest, map_test)
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

TEST_F(SampleTest, dc_shift_test)
{
	Range r( -1, 1);
	EXPECT_FLOAT_EQ( dc_shift<float>(0, +0.2, r), 0.2);
	EXPECT_FLOAT_EQ( dc_shift<float>(0.6, -0.2, r), 0.4);
	EXPECT_FLOAT_EQ( dc_shift<float>(-0.3, +0.2, r), -0.1);
	EXPECT_FLOAT_EQ( dc_shift<float>(-0.9, 0.02, r), -0.88);
	
	EXPECT_FLOAT_EQ( dc_shift<float>(0.8, +0.3, r), -0.9);
	EXPECT_FLOAT_EQ( dc_shift<float>(-0.7, -2, r), -0.7);

	/// Looks like an error accumulates
	// float eps = 0.00001;
	// EXPECT_NEAR( dc_shift<float>(0.7, -3, r), -0.7, eps);
	// EXPECT_NEAR( dc_shift<float>(-0.4, +5, r), -0.4, eps);
	EXPECT_FLOAT_EQ( dc_shift<float>(0.7, -3, r), -0.3);
	EXPECT_FLOAT_EQ( dc_shift<float>(-0.4, +5, r), +0.6);
}

TEST_F(SampleTest, dc_shift_clip_test)
{
	Range r( -1, 1);
	EXPECT_FLOAT_EQ( dc_shift_clip<float>(0, +0.2, r), 0.2);
	EXPECT_FLOAT_EQ( dc_shift_clip<float>(0.6, -0.2, r), 0.4);
	EXPECT_FLOAT_EQ( dc_shift_clip<float>(-0.3, +0.2, r), -0.1);
	EXPECT_FLOAT_EQ( dc_shift_clip<float>(-0.9, 0.02, r), -0.88);
	
	EXPECT_FLOAT_EQ( dc_shift_clip<float>(0.8, +0.3, r), +1);
	EXPECT_FLOAT_EQ( dc_shift_clip<float>(-0.7, -2, r), -1);

	/// Looks like an error accumulates
	// float eps = 0.00001;
	// EXPECT_NEAR( dc_shift<float>(0.7, -3, r), -0.7, eps);
	// EXPECT_NEAR( dc_shift<float>(-0.4, +5, r), -0.4, eps);
	EXPECT_FLOAT_EQ( dc_shift_clip<float>(0.7, -3, r), -1);
	EXPECT_FLOAT_EQ( dc_shift_clip<float>(-0.4, +5, r), +1);
}
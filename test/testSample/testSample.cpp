#include "testSample.h"
#include "Lithe/Sample.h"

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
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
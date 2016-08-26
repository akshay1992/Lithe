#include "testSample.h"

SampleTest::SampleTest(void) {}

SampleTest::~SampleTest(void) {}

void SampleTest::SetUp(void) {}

void SampleTest::TearDown(void) {}

TEST_F(SampleTest, removeThisTest)
{
    EXPECT_EQ(1, 2);
}

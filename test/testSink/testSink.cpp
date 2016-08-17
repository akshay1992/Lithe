#include "testSink.h"
#include "Sink.h"

SinkTest::SinkTest(void) {}

SinkTest::~SinkTest(void) {}

void SinkTest::SetUp(void) {}

void SinkTest::TearDown(void) {}

// TEST_F(SinkTest, removeThisTest)
// {
//     EXPECT_EQ(1, 2);
// }

TEST_F(SinkTest, numInletsTest)
{
	int inlets = 3;

	Sink sink(inlets);

	EXPECT_EQ(sink.numInlets(), inlets);
}
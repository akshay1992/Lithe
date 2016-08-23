#include "testSink.h"
#include "Sink.h"

SinkTest::SinkTest(void) {}

SinkTest::~SinkTest(void) {}

void SinkTest::SetUp(void) {}

void SinkTest::TearDown(void) {}

TEST_F(SinkTest, numInletsTest)
{
	int inlets = 3;

	Sink sink(inlets);

	EXPECT_EQ(sink.numInlets(), inlets);
}

// TEST_F(SinkTest, own_ProcessState)
// {
// 	Sink s1(2);

// 	Node::resetAll_ProcessState();
// 	EXPECT_FALSE(s1.isDoneProcessing());
// 	s1.Process();
// 	EXPECT_TRUE(s1.isDoneProcessing());
// 	s1.resetAll_ProcessState();
// 	EXPECT_FALSE(s1.isDoneProcessing());
// }

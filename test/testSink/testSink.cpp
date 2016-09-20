#include "testSink.h"
#include "Lithe/Sink.h"
#include "DSPSink.hpp"

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

TEST_F(SinkTest, setCustomDSP_Test)
{
	/// Raw Sink = no DSP processing
	RawSink raw;
	int value = raw.value  ;

	raw.Process();
	EXPECT_EQ(raw.value, value);	// Value should not change on processing

	DSPSink s;
	// DSPSink increments value everytime it is processed. 
	value = s.value;
	s.Process();
	EXPECT_EQ( s.value, value+1  ); // This ensures that the new process method is being called
}
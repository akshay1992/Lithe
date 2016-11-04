#include "testSink.h"
#include "Lithe/LitheCore.h"
#include "DSPSink.hpp"
#include "ProcessingNode.hpp"
using namespace lithe;

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

TEST_F(SinkTest, own_ProcessState)
{
	Sink s1(2);

	Node::resetAll_ProcessState();
	EXPECT_FALSE(s1.isDoneProcessing());
	s1.Process();
	EXPECT_TRUE(s1.isDoneProcessing());
}

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

TEST_F(SinkTest, ConnectedGraph_Test)
{
	SourceNode ns1;
	ProcessingNode n1, n2;
	StorageSink sink(1);
	Patcher::connect(n2.getInlet(0),  n1.getOutlet(0));
	Patcher::connect(sink.getInlet(0), n2.getOutlet(0));
	Patcher::connect(n1.getInlet(0), ns1.getOutlet(0));

	Sample s = Sample(0.1, -0.2, 0.3, -0.4);
	ns1.inject(s);

	/// FOr some reason this works only when you force float addition.
	sink.Process();
	EXPECT_TRUE( sink.isDoneProcessing() );
	EXPECT_FLOAT_EQ(sink.inletSamples[0].audio, s.audio + 0.2);
	EXPECT_FLOAT_EQ(sink.inletSamples[0].az, s.az + (float) 0.2);
	EXPECT_FLOAT_EQ(sink.inletSamples[0].el, s.el + 0.2);
	EXPECT_FLOAT_EQ(sink.inletSamples[0].d, s.d + 0.2);
}
#include "testSink.h"
#include "Sink.h"
#include <iostream>
using namespace std;

SinkTest::SinkTest(void) {
}

SinkTest::~SinkTest(void) {}

void SinkTest::SetUp(void) {}

void SinkTest::TearDown(void) {}

TEST_F(SinkTest, testNumInputs)
{
	const int nInputs = 4;
	Sink sink(nInputs);

	EXPECT_EQ(sink.getNumInputs(), nInputs);
	EXPECT_EQ(sink.getInputs().size(), nInputs);
	EXPECT_EQ(sink.getNumInputs(), sink.getInputs().size());
}

TEST_F(SinkTest, testcInputs)
{
	const int nInputs = 4;
	Sink sink(nInputs);
	
	for(int i=0; i<sink.getNumInputs(); i++)
	{		
		EXPECT_TRUE(sink.getInputs()[i].block_ref == NULL);
		EXPECT_EQ(sink.getInputs()[i].index , -1);
	}
}
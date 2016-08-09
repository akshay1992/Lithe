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
}

TEST_F(SinkTest, testInputs)
{
	const int nInputs = 4;
	Sink sink(nInputs);
	
	for(int i=0; i<sink.getNumInputs(); i++)
	{		
		EXPECT_TRUE(sink.getInput(i).block_ref == NULL);
		EXPECT_EQ(sink.getInput(i).index , -1);
	}
}
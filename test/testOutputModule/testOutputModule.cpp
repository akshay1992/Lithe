#include "testOutputModule.h"
#include "OutputModule.h"
#include "DummyNode.hpp"	// For testing
#include <iostream>

OutputModuleTest::OutputModuleTest(void) {}

OutputModuleTest::~OutputModuleTest(void) {}

void OutputModuleTest::SetUp(void) {}

void OutputModuleTest::TearDown(void) {}

TEST_F(OutputModuleTest, defaultoutdevice_nChannels_Test)
{
	OutputModule outputModule(2, 128);
	al::AudioIO io(al::AudioIOData::DUMMY);
	io.deviceOut(al::AudioDevice::defaultOutput());
	EXPECT_EQ( io.channelsOutDevice(), outputModule.io.channelsOutDevice());
}

TEST_F(OutputModuleTest, ProducesOutput_test)
{
	DummyNode node;
	OutputModule out(1, 512);

	Patcher::connect(out.getInlet(0), node.getOutlet(0));

	out.startProcessing();

	for(int i=0; i<1; i++)
	{
		Sample s(0.2, 01, 0, +0.1);
		node.inject(s);

		out.Process();
		EXPECT_TRUE(false);
	}

}
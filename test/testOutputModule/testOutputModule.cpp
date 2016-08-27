#include "testOutputModule.h"
#include "OutputModule.h"

OutputModuleTest::OutputModuleTest(void) {}

OutputModuleTest::~OutputModuleTest(void) {}

void OutputModuleTest::SetUp(void) {}

void OutputModuleTest::TearDown(void) {}

TEST_F(OutputModuleTest, defaultoutdevice_nChannels_Test)
{
	OutputModule outputModule(2);
	al::AudioIO io(al::AudioIOData::DUMMY);
	io.deviceOut(al::AudioDevice::defaultOutput());
	EXPECT_EQ( io.channelsOutDevice(), outputModule.io.channelsOutDevice());
}

// TEST OTHER THINGS
TEST_F(OutputModuleTest, processingTest)
{
	EXPECT_EQ(1, 2)
}
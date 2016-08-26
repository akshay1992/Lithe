#include "testOscillator.h"
#include "Oscillator.h"

OscillatorTest::OscillatorTest(void) {}

OscillatorTest::~OscillatorTest(void) {}

void OscillatorTest::SetUp(void) {}

void OscillatorTest::TearDown(void) {}

#define DUR_SAMPS 44100

TEST_F(OscillatorTest, SineTest_NoSpatialModulation)
{
	gam::sampleRate(44100);	// Always put this before everything realted to gamma.
	Oscillator osc;
	gam::Sine<> sine;
	sine.freq(440);

	for(int i=0; i< DUR_SAMPS; i++)
	{
		Sample s = Sample( sine(), 0 , 0, 0);
		EXPECT_EQ( osc.getOutlet(0).getSample().audio, s.audio);
		EXPECT_EQ( osc.getOutlet(0).getSample().az, s.az);
		EXPECT_EQ( osc.getOutlet(0).getSample().el, s.el);
		EXPECT_EQ( osc.getOutlet(0).getSample().d, s.d);
		Node::resetAll_ProcessState();		// Remember to do this
	}
}

TEST_F(OscillatorTest, SquareTest_NoSpatialModulation)
{
	gam::sampleRate(44100);
	Oscillator osc;

	gam::Square<> square;
	square.freq(440);

	for(int i=0; i< DUR_SAMPS; i++)
	{
		Sample s = Sample( square(), 0 , 0, 0);
		EXPECT_EQ( osc.getOutlet(1).getSample().audio, s.audio);
		EXPECT_EQ( osc.getOutlet(1).getSample().az, s.az);
		EXPECT_EQ( osc.getOutlet(1).getSample().el, s.el);
		EXPECT_EQ( osc.getOutlet(1).getSample().d, s.d);
		Node::resetAll_ProcessState();
	}
}

TEST_F(OscillatorTest, TriTest_NoSpatialModulation)
{
	gam::sampleRate(44100);
	Oscillator osc;

	gam::DWO<> tri;
	tri.freq(440);

	for(int i=0; i< DUR_SAMPS; i++)
	{
		Sample s = Sample( tri.tri(), 0 , 0, 0);
		EXPECT_EQ( osc.getOutlet(2).getSample().audio, s.audio);
		EXPECT_EQ( osc.getOutlet(2).getSample().az, s.az);
		EXPECT_EQ( osc.getOutlet(2).getSample().el, s.el);
		EXPECT_EQ( osc.getOutlet(2).getSample().d, s.d);
		Node::resetAll_ProcessState();
	}
}

TEST_F(OscillatorTest, SawTest_NoSpatialModulation)
{
	gam::sampleRate(44100);
	Oscillator osc;

	gam::Saw<> saw;
	saw.freq(440);

	for(int i=0; i< DUR_SAMPS; i++)
	{
		Sample s = Sample( saw(), 0 , 0, 0);
		EXPECT_EQ( osc.getOutlet(3).getSample().audio, s.audio);
		EXPECT_EQ( osc.getOutlet(3).getSample().az, s.az);
		EXPECT_EQ( osc.getOutlet(3).getSample().el, s.el);
		EXPECT_EQ( osc.getOutlet(3).getSample().d, s.d);
		Node::resetAll_ProcessState();
	}
}

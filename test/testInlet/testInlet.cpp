#include "testInlet.h"
#include "Lithe/LitheCore.h"

using namespace lithe;
#include <iostream>

bool sampleCompare(Sample& s1, Sample& s2)
{
	// TODO: Handle case when there is a range mismatch
	if( s1[0] == s2[0] &&
		s1[1] == s2[1] && 
		s1[2] == s2[2] && 
		s1[3] == s2[3] )
	{
		return true;		
	}
	else
	{
		return false;
		std::cout << "Unequal samples: " << std::endl
		<<
		 s1[0] << "!=" << s2[0] << std::endl << 
		s1[1] << "!=" << s2[1] << std::endl << 
		s1[2] << "!=" << s2[2] << std::endl << 
		s1[3] << "!=" << s2[3] << std::endl << 
		 std::endl;
	}
}

void printSample(Sample s)
{
	std::cout << "{ " << s[0]<< ", " << s[1] << ", " << s[2] << ", "<< s[3]<< " }" << std::endl;
}

InletTest::InletTest(void) {}

InletTest::~InletTest(void) {}

void InletTest::SetUp(void) {}

void InletTest::TearDown(void) {}

TEST_F(InletTest, connect)
{
	Inlet inlet(NULL);
	Outlet outlet(NULL);
	EXPECT_TRUE(inlet.getConnectedOutlet() == NULL);
	inlet.connect(outlet);
	EXPECT_TRUE(inlet.getConnectedOutlet() == &outlet);
}

TEST_F(InletTest, disconnect)
{
	Inlet inlet(NULL);
	Outlet outlet(NULL);

	inlet.connect(outlet);
	EXPECT_TRUE(inlet.getConnectedOutlet() != NULL);
	inlet.disconnect();
	EXPECT_TRUE(inlet.getConnectedOutlet() == NULL);
}

TEST_F(InletTest, isConnected)
{
	Inlet inlet(NULL);
	Outlet outlet(NULL);

	EXPECT_FALSE(inlet.isConnected());
	inlet.connect(outlet);
	EXPECT_TRUE(inlet.isConnected());
	inlet.disconnect();
	EXPECT_FALSE(inlet.isConnected());
}

TEST_F(InletTest, getSample)
{
	{
		Inlet inlet(NULL);
		Outlet outlet(NULL);

		inlet.connect(outlet);

		Sample s(0.2, -0.92, +0.87, +0.01);
		outlet.setSample(s);
		// EXPECT_TRUE( lithe::sampleCompare<>(s, inlet.getSample()) );
		Sample inletSample = inlet.getSample();
		EXPECT_TRUE( sampleCompare(s, inletSample ) );

	}

	{
		Inlet inlet(NULL);
		Outlet outlet(NULL);

		inlet.connect(outlet);
		inlet.enableSampleDelay();

		Sample s(0.2, -0.92, +0.87, +0.01);
		outlet.setSample(s);
		Sample empty;

		Sample inletSample = inlet.getSample();
		EXPECT_TRUE( sampleCompare(empty, inletSample) );
		inletSample = inlet.getSample();
		EXPECT_TRUE( sampleCompare(s, inletSample) );
	}
}


// TEST_F(InletTest, connectTest_IsConnected)
// {
// 	Node node1(1, 0);
// 	Node node2(0, 1); 

//  	node1.getInlet(0).connect(node2.getOutlet(0));

// 	EXPECT_EQ( node1.getInlet(0).getConnectedOutlet()->getParentNode(), &node2 );

// 	EXPECT_TRUE( node1.getInlet(0).isConnected() );
// }


// TEST_F(InletTest, connectTest_NotConnected)
// {
// 	Node node1(2, 0);
// 	Node node2(1, 1); 

// 	node2.getOutlet(0).connect(node1.getInlet(0));

// 	EXPECT_TRUE( node1.getInlet(0).isConnected() );
// 	EXPECT_FALSE( node1.getInlet(1).isConnected() );
// 	EXPECT_FALSE( node2.getInlet(0).isConnected() );
// }


// TEST_F(InletTest, getSample_noneConnected_noDelay)
// {
// 	Node node(1, 1);

// 	Sample s;

// 	Sample inletSample = node.getInlet().getSample();

// 	EXPECT_EQ( inletSample.audio, s.audio);
// 	EXPECT_EQ( inletSample.az, s.az);
// 	EXPECT_EQ( inletSample.el, s.el);
// 	EXPECT_EQ( inletSample.d, s.d);
// }

// TEST_F(InletTest, getSample_noneConnected_yesDelay)
// {
// 	Node node(1, 1);

// 	Sample s;
// 	node.getInlet().enableSampleDelay();

// 	Sample inletSample = node.getInlet().getSample();

// 	EXPECT_EQ( inletSample.audio, s.audio);
// 	EXPECT_EQ( inletSample.az, s.az);
// 	EXPECT_EQ( inletSample.el, s.el);
// 	EXPECT_EQ( inletSample.d, s.d);

// 	// Second time 
// 	inletSample = node.getInlet().getSample();

// 	EXPECT_EQ( inletSample.audio, s.audio);
// 	EXPECT_EQ( inletSample.az, s.az);
// 	EXPECT_EQ( inletSample.el, s.el);
// 	EXPECT_EQ( inletSample.d, s.d);
// }

// TEST_F(InletTest, getSample_connected_noDelay)
// {
// 	Node node(1, 0);	// Destination
// 	Node node2(0, 1); // Source

// 	Patcher::connect(node.getInlet(), node2.getOutlet());
// 	node.getInlet().disableSampleDelay();


// 	Sample s(0.1, -0.986, +0.885, 0.2);
// 	node2.getOutlet().setSample(s);

// 	Sample inletSample = node.getInlet().getSample();

// 	EXPECT_EQ( inletSample.audio, s.audio);
// 	EXPECT_EQ( inletSample.az, s.az);
// 	EXPECT_EQ( inletSample.el, s.el);
// 	EXPECT_EQ( inletSample.d, s.d);

// 	s = Sample(0.09, -0.42, +0.74, 0.6);
// 	node2.getOutlet().setSample(s);

// 	inletSample = node.getInlet().getSample();

// 	EXPECT_EQ( inletSample.audio, s.audio);
// 	EXPECT_EQ( inletSample.az, s.az);
// 	EXPECT_EQ( inletSample.el, s.el);
// 	EXPECT_EQ( inletSample.d, s.d);
// }

// TEST_F(InletTest, getSample_connected_yesDelay)
// {
// 	Node node(1, 0);// Destination
// 	Node node2(0, 1); // Source

// 	node.getInlet().enableSampleDelay();
// 	Patcher::connect(node.getInlet(), node2.getOutlet());

// 	Sample set(0.1, -0.986, +0.885, 0.2);
// 	Sample expected;

// 	node2.getOutlet().setSample(set);
// 	Sample inletSample = node.getInlet().getSample();

// 	EXPECT_EQ( inletSample.audio, expected.audio);
// 	EXPECT_EQ( inletSample.az, expected.az);
// 	EXPECT_EQ( inletSample.el, expected.el);
// 	EXPECT_EQ( inletSample.d, expected.d);

// 	expected = set; // Expect previously set sample
// 	set = Sample(0.9, -0.42, +0.45, 0.3); // Set new (different sample value)
	
// 	node2.getOutlet().setSample(set);
// 	inletSample = node.getInlet().getSample();

// 	EXPECT_EQ( inletSample.audio, expected.audio);
// 	EXPECT_EQ( inletSample.az, expected.az);
// 	EXPECT_EQ( inletSample.el, expected.el);
// 	EXPECT_EQ( inletSample.d, expected.d);
// }


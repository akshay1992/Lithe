#include "testInlet.h"
#include "Outlet.h"

InletTest::InletTest(void) {}

InletTest::~InletTest(void) {}

void InletTest::SetUp(void) {}

void InletTest::TearDown(void) {}

TEST_F(InletTest, parentNodeTest_Correct)
{
	Node node1(1, 1);
	Node node2(1, 1);
	EXPECT_EQ ( node1.getInlet(0).parent_node, &node1 );

	EXPECT_NE ( node1.getInlet(0).parent_node, &node2 );
}

TEST_F(InletTest, connectTest_IsConnected)
{
	Node node1(1, 0);
	Node node2(0, 1); 

 	node1.getInlet(0).connect(node2.getOutlet(0));

	EXPECT_EQ( node1.getInlet(0).connected_outlet->parent_node, &node2 );

	EXPECT_TRUE( node1.getInlet(0).isConnected() );
}


TEST_F(InletTest, connectTest_NotConnected)
{
	Node node1(2, 0);
	Node node2(1, 1); 

	node2.getOutlet(0).connect(node1.getInlet(0));

	EXPECT_TRUE( node1.getInlet(0).isConnected() );
	EXPECT_FALSE( node1.getInlet(1).isConnected() );
	EXPECT_FALSE( node2.getInlet(0).isConnected() );
}


TEST_F(InletTest, getSample_noneConnected_noDelay)
{
	Node node(1, 1);

	Sample s;

	Sample inletSample = node.getInlet().getSample();

	EXPECT_EQ( inletSample.audio, s.audio);
	EXPECT_EQ( inletSample.az, s.az);
	EXPECT_EQ( inletSample.el, s.el);
	EXPECT_EQ( inletSample.d, s.d);
}

TEST_F(InletTest, getSample_noneConnected_yesDelay)
{
	Node node(1, 1);

	Sample s;
	node.getInlet().enableSampleDelay();

	Sample inletSample = node.getInlet().getSample();

	EXPECT_EQ( inletSample.audio, s.audio);
	EXPECT_EQ( inletSample.az, s.az);
	EXPECT_EQ( inletSample.el, s.el);
	EXPECT_EQ( inletSample.d, s.d);

	// Second time 
	inletSample = node.getInlet().getSample();

	EXPECT_EQ( inletSample.audio, s.audio);
	EXPECT_EQ( inletSample.az, s.az);
	EXPECT_EQ( inletSample.el, s.el);
	EXPECT_EQ( inletSample.d, s.d);
}

TEST_F(InletTest, getSample_connected_noDelay)
{
	Node node(1, 0);	// Destination
	Node node2(0, 1); // Source

	Patcher::connect(node.getInlet(), node2.getOutlet());
	node.getInlet().disableSampleDelay();


	Sample s(0.1, -0.986, +0.885, 0.2);
	node2.getOutlet().setSample(s);

	Sample inletSample = node.getInlet().getSample();

	EXPECT_EQ( inletSample.audio, s.audio);
	EXPECT_EQ( inletSample.az, s.az);
	EXPECT_EQ( inletSample.el, s.el);
	EXPECT_EQ( inletSample.d, s.d);

	s = Sample(0.09, -0.42, +0.74, 0.6);
	node2.getOutlet().setSample(s);

	inletSample = node.getInlet().getSample();

	EXPECT_EQ( inletSample.audio, s.audio);
	EXPECT_EQ( inletSample.az, s.az);
	EXPECT_EQ( inletSample.el, s.el);
	EXPECT_EQ( inletSample.d, s.d);
}

TEST_F(InletTest, getSample_connected_yesDelay)
{
	Node node(1, 0);// Destination
	Node node2(0, 1); // Source

	node.getInlet().enableSampleDelay();
	Patcher::connect(node.getInlet(), node2.getOutlet());

	Sample set(0.1, -0.986, +0.885, 0.2);
	Sample expected;

	node2.getOutlet().setSample(set);
	Sample inletSample = node.getInlet().getSample();

	EXPECT_EQ( inletSample.audio, expected.audio);
	EXPECT_EQ( inletSample.az, expected.az);
	EXPECT_EQ( inletSample.el, expected.el);
	EXPECT_EQ( inletSample.d, expected.d);

	expected = set; // Expect previously set sample
	set = Sample(0.9, -0.42, +0.45, 0.3); // Set new (different sample value)
	
	node2.getOutlet().setSample(set);
	inletSample = node.getInlet().getSample();

	EXPECT_EQ( inletSample.audio, expected.audio);
	EXPECT_EQ( inletSample.az, expected.az);
	EXPECT_EQ( inletSample.el, expected.el);
	EXPECT_EQ( inletSample.d, expected.d);
}

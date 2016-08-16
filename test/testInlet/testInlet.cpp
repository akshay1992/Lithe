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


TEST_F(InletTest, getSample_noneConnected)
{
	Node node(1, 1);

	Sample s;

	EXPECT_EQ( node.getInlet().getSample().audio, s.audio);
	EXPECT_EQ( node.getInlet().getSample().az, s.az);
	EXPECT_EQ( node.getInlet().getSample().el, s.el);
	EXPECT_EQ( node.getInlet().getSample().d, s.d);
}

TEST_F(InletTest, getSample_connected)
{
	Node node(1, 1);	// Destination
	Node node2(1, 1); // Source

	Patcher::connect(node.getInlet(), node2.getOutlet());

	Sample s(0.1, -0.986, +0.885, 0.0);
	node2.getOutlet().setSample(s);

	EXPECT_EQ( node.getInlet().getSample().audio, s.audio);
	EXPECT_EQ( node.getInlet().getSample().az, s.az);
	EXPECT_EQ( node.getInlet().getSample().el, s.el);
	EXPECT_EQ( node.getInlet().getSample().d, s.d);
}

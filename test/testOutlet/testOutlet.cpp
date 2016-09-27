#include "testOutlet.h"
#include "Lithe/LitheCore.h"

OutletTest::OutletTest(void) {}

OutletTest::~OutletTest(void) {}

void OutletTest::SetUp(void) {}

void OutletTest::TearDown(void) {}

TEST_F(OutletTest, parentNodeTest_Correct)
{
	Node node1(1, 1);
	Node node2(1, 1);

	EXPECT_EQ ( node1.getOutlet(0).parent_node, &node1 );

	EXPECT_NE ( node1.getOutlet(0).parent_node, &node2 );
}

TEST_F(OutletTest, connectTest_IsConnected)
{
	Node node1(1, 0);
	Node node2(0, 1); 

	node2.getOutlet(0).connect(node1.getInlet(0));
}

TEST_F(OutletTest, connectTest_NotConnected)
{
	Node node1(1, 1);
	Node node2(0, 2); 

	node2.getOutlet(0).connect(node1.getInlet(0));
}

TEST_F(OutletTest, get_set_Sample)
{
	Node node(1, 1);
	EXPECT_EQ( node.getOutlet().getSample().audio, 0);
	EXPECT_EQ( node.getOutlet().getSample().az, 0);
	EXPECT_EQ( node.getOutlet().getSample().el, 0);
	EXPECT_EQ( node.getOutlet().getSample().d, 0);

	Sample s(0.1, 0.3, -.7, -1.0);
	node.getOutlet().setSample( s );

	EXPECT_EQ( node.getOutlet().getSample().audio, s.audio);
	EXPECT_EQ( node.getOutlet().getSample().az, s.az);
	EXPECT_EQ( node.getOutlet().getSample().el, s.el);
	EXPECT_EQ( node.getOutlet().getSample().d, s.d);
}


#include "testOutlet.h"
#include "Lithe/LitheCore.h"
using namespace lithe;

OutletTest::OutletTest(void) {}

OutletTest::~OutletTest(void) {}

void OutletTest::SetUp(void) {}

void OutletTest::TearDown(void) {}

TEST_F(OutletTest, constructorTest)
{
	Node node1(1, 1);
	Node node2(1, 1);

	EXPECT_EQ ( node1.getOutlet(0).getParentNode(), &node1 );

	EXPECT_NE ( node1.getOutlet(0).getParentNode(), &node2 );
}

TEST_F(OutletTest, isConnected)
{
	// Fanned connections
	{
		/// Initializing outlets without parent nodes
		Inlet i0(nullptr), i1(nullptr), i2(nullptr);
		Outlet outlet(nullptr);

		EXPECT_FALSE(outlet.isConnected());
		outlet.connect(i0);
		EXPECT_TRUE(outlet.isConnected());
		EXPECT_EQ(outlet.getConnectedInlets().size(), 1);
		EXPECT_TRUE( outlet.getConnectedInlets()[0] == &i0 );

		outlet.connect(i1);
		EXPECT_TRUE(outlet.isConnected());	
		EXPECT_EQ(outlet.getConnectedInlets().size(), 2);
		EXPECT_TRUE( outlet.getConnectedInlets()[1] == &i1 );

		outlet.connect(i2);
		EXPECT_TRUE(outlet.isConnected());	
		EXPECT_EQ(outlet.getConnectedInlets().size(), 3);
		EXPECT_TRUE( outlet.getConnectedInlets()[2] == &i2 );

		outlet.disconnect(i1);
		EXPECT_FALSE(i1.isConnected());
		EXPECT_EQ(outlet.getConnectedInlets().size(), 2);
	}
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

#include "testNode.h"
#include "Lithe/LitheCore.h"
#include "InheritedNode.hpp"

using namespace lithe;

NodeTest::NodeTest(void) {}

NodeTest::~NodeTest(void) {}

void NodeTest::SetUp(void) {}

void NodeTest::TearDown(void) {}

TEST_F(NodeTest, inlet_parentNodeTest)
{
	Node node1(2, 1);
	EXPECT_EQ ( node1.getInlet(0).getParentNode(), &node1 );
	EXPECT_EQ ( node1.getInlet(1).getParentNode(), &node1 );
}

TEST_F(NodeTest, outlet_parentNodeTest)
{
	Node node1(1, 2);
	EXPECT_EQ ( node1.getOutlet(0).getParentNode(), &node1 );
	EXPECT_EQ ( node1.getOutlet(1).getParentNode(), &node1 );
}

TEST_F(NodeTest, numInletsOutletsTest)
{
	int inlets = 3;
	int outlets = 2;

	Node n(inlets, outlets);

	EXPECT_EQ(n.numInlets(), inlets);
	EXPECT_EQ(n.numOutlets(), outlets);
}

TEST_F(NodeTest, ID_test)
{
	Node n(2, 1);
	int id1 = n.getID();

	Node n2(4, 2);
	int id2 = n2.getID();

	EXPECT_EQ( id2-1, id1);
}

TEST_F(NodeTest, getNodeRef_ValidID)
{
	Node n(2, 1);

	int id = n.getID();

	EXPECT_EQ(Node::getNodeRef(id), &n);
}

TEST_F(NodeTest, getNodeRef_InvalidID)
{
	Node n1(1, 1);

	int id;
	Node* nodeptr;
	{ // Scoping the node so it gets removed
		Node n2(2, 1);
		id = n2.getID();
	}

	EXPECT_THROW( Node::getNodeRef(id), NodeNotFoundException);
	EXPECT_NO_THROW(Node::getNodeRef(n1.getID()));
	EXPECT_EQ(Node::getNodeRef(n1.getID()), &n1);
}

TEST_F(NodeTest, ProcessState)
{
	Node n1(2,1);

	EXPECT_FALSE(n1.isDoneProcessing());
	n1.Process();
	EXPECT_TRUE(n1.isDoneProcessing());
	Node::resetAll_ProcessState();
	EXPECT_FALSE(n1.isDoneProcessing());
}

TEST_F(NodeTest, ChangeDSP)
{
	Node n1(1, 1);	// Singleoutlet node
	InheritedNode n2; // Single inlet/outlet node with a bypass DSP

	Patcher::connect(n2.getInlet(0), n1.getOutlet(0));

	Sample s = Sample(1, 2, 4, 5);
	n1.getOutlet(0).setSample( s); // inject sample into n1's outlet

	Sample output = n2.getOutlet(0).getSample(); 	// Implicitly processes n2

	EXPECT_FLOAT_EQ(output.audio, s.audio+0.01);
	EXPECT_FLOAT_EQ(output.az, s.az+0.01);
	EXPECT_FLOAT_EQ(output.el, s.el+0.01);
	EXPECT_FLOAT_EQ(output.d, s.d+0.01);
}

TEST_F(NodeTest, destructor_test)
{
	Node* n1 = new Node(1,1);
	Node n2(1,1);
	Patcher::connect(n2.getInlet(), n1->getOutlet());

	delete n1;
	EXPECT_FALSE(n2.getInlet().isConnected());
}

TEST_F(NodeTest, resetSampleDelayState)
{
	Node n1( 4, 1);

	n1.getInlet(0).enableSampleDelay();
	n1.getInlet(1).enableSampleDelay();
	n1.getInlet(2).disableSampleDelay();
	n1.getInlet(3).enableSampleDelay();

	Node::resetAll_SampleDelayState(false);

	EXPECT_FALSE(n1.getInlet(0).sampleDelayEnabled());
	EXPECT_FALSE(n1.getInlet(1).sampleDelayEnabled());
	EXPECT_FALSE(n1.getInlet(2).sampleDelayEnabled());
	EXPECT_FALSE(n1.getInlet(3).sampleDelayEnabled());
}
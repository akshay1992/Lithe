#include "testNode.h"
#include "Lithe/LitheCore.h"
#include "InheritedNode.hpp"

using namespace lithe;

NodeTest::NodeTest(void) {}

NodeTest::~NodeTest(void) {}

void NodeTest::SetUp(void) {}

void NodeTest::TearDown(void) {}

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
	{ // Scoping the node
		Node n2(2, 1);
		id = n2.getID();
	}
	
	EXPECT_TRUE(Node::getNodeRef(id) == NULL);
	EXPECT_FALSE(Node::getNodeRef(id-1) == NULL);
	EXPECT_EQ(Node::getNodeRef(id-1), &n1);
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

	EXPECT_EQ(output.audio, s.audio);
	EXPECT_EQ(output.az, s.az);
	EXPECT_EQ(output.el, s.el);
	EXPECT_EQ(output.d, s.d);
}
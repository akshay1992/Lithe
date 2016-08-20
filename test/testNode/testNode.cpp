#include "testNode.h"
#include "Node.h"

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

	EXPECT_FALSE(n1.hasProcessed());
	n1.Process();
	EXPECT_TRUE(n1.hasProcessed());
	n1.resetProcessState();
	EXPECT_FALSE(n1.hasProcessed());
}
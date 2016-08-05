#include "testBlock.h"
#include "Block.h"

BlockTest::BlockTest() {
};

BlockTest::~BlockTest() {};

void BlockTest::SetUp() {};

void BlockTest::TearDown() {};

TEST_F(BlockTest, utInitInputVectors)
{
	const int nInput = 3;
	const int nOutput = 1;
	Block block(nInput, nOutput);

	EXPECT_EQ ( nInput, block.getNumInputs() ) ;
	EXPECT_EQ ( nInput, block.getInputs().size() );
	EXPECT_EQ ( block.getInputs().size(), block.getNumInputs() );

	for(int i=0; i< block.getNumInputs(); i++)
	{
		EXPECT_TRUE( block.getInputs()[i].block_ref == NULL );
		EXPECT_EQ( block.getInputs()[i].index, -1 );
	}
}

TEST_F(BlockTest, utInitOutputVectors)
{
	const int nInput = 2;
	const int nOutput = 5;
	Block block(nInput, nOutput);

	EXPECT_EQ ( nOutput, block.getNumOutputs() ) ;
	EXPECT_EQ ( nOutput, block.getOutputs().size() );
	EXPECT_EQ ( block.getOutputs().size(), block.getNumOutputs() );

	for(int i=0; i< block.getNumOutputs(); i++)
	{
		EXPECT_TRUE( block.getOutputs()[i].block_ref == NULL );
		EXPECT_EQ( block.getOutputs()[i].index, -1 );
	}
}

TEST_F(BlockTest, isValidInputTest)
{
	Block b = Block(2, 12);

	EXPECT_TRUE( b.isValidInput(1) );
	EXPECT_TRUE( b.isValidInput(0) );
	
	EXPECT_FALSE( b.isValidInput(-1) );
	EXPECT_FALSE( b.isValidInput(3) );
}

TEST_F(BlockTest, isValidOutputTest)
{
	Block b = Block(1, 5);

	EXPECT_TRUE( b.isValidOutput(1) );
	EXPECT_TRUE( b.isValidOutput(3) );
	EXPECT_TRUE( b.isValidOutput(4) );
	EXPECT_TRUE( b.isValidOutput(0) );
	EXPECT_TRUE( b.isValidOutput(2) );
	
	EXPECT_FALSE( b.isValidOutput(-1) );
	EXPECT_FALSE( b.isValidOutput(5) );
	EXPECT_FALSE( b.isValidOutput(6) );
	EXPECT_FALSE( b.isValidOutput(-4) );
}

TEST_F(BlockTest, idTest)
{
	Block b(1, 2);
	int id1 = b.getID();
	
	Block b1(2, 4);

	EXPECT_EQ( b.getID(), id1 );
	EXPECT_EQ( b1.getID(), id1+1);
	EXPECT_NE( b.getID(), b1.getID());
}

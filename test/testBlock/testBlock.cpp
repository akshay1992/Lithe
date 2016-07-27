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
		EXPECT_TRUE( block.getInputs()[i]==NULL );
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
		EXPECT_TRUE( block.getOutputs()[i]==NULL );
	}
}

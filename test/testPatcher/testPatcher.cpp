#include "testPatcher.h"

#include "Patcher.h"

PatcherTest::PatcherTest() 
{};

PatcherTest::~PatcherTest() {};

void PatcherTest::SetUp() {};

void PatcherTest::TearDown() {};

TEST_F(PatcherTest, singleBlockSinkPatch)
{
	Sink sink(1);
	Block block(1, 1);

	int outlet_index = 0; 
	int inlet_index = 0;

	Patcher::patch(block, outlet_index, sink, inlet_index);

	EXPECT_FALSE(sink.getInputs()[inlet_index] == NULL);
	EXPECT_FALSE(block.getOutputs()[outlet_index] == NULL);
	EXPECT_EQ(sink.getInputs()[inlet_index], block.getOutputs()[outlet_index]);
}


TEST_F(PatcherTest, singleBlockBlockPatch)
{
	Block block1(1, 1);
	Block block2(1, 1);

	int outlet_index = 0; 
	int inlet_index = 0;

	Patcher::patch(block1, outlet_index, block2, inlet_index);

	EXPECT_FALSE(block2.getInputs()[inlet_index] == NULL);
	EXPECT_FALSE(block1.getOutputs()[outlet_index] == NULL);

	EXPECT_EQ(block2.getInputs()[inlet_index], block1.getOutputs()[outlet_index]);
}

TEST_F(PatcherTest, chainBlockSinkPatch)
{
	int nBlocks = 6;
	std::vector<Block> block;

	Sink sink(1);
	for(int i=0; i<nBlocks; i++) 
	{
		block.push_back(* new Block(2, 1));
	}

	for(int i=0; i<nBlocks-1; i++)
	{
		Patcher::patch(block[i+1], 0, block[i], 0 );

		EXPECT_FALSE(block[i+1].getInputs()[0] == NULL);
		EXPECT_FALSE(block[i].getOutputs()[0] == NULL);

		EXPECT_EQ(block[i+1].getInputs()[0], block[i].getOutputs()[0]);

	}
	Patcher::patch(sink, 0, block[nBlocks-1], 0);

	EXPECT_FALSE(sink.getInputs()[0] == NULL);
	EXPECT_FALSE(block[nBlocks-1].getOutputs()[0] == NULL);

	EXPECT_EQ(sink.getInputs()[0], block[nBlocks-1].getOutputs()[0]);
}
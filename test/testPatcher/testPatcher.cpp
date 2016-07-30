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

	Patcher patcher;

	// Before Patch

	EXPECT_TRUE(sink.getInputs()[inlet_index].block_ref == NULL);
	EXPECT_TRUE(block.getOutputs()[outlet_index].block_ref == NULL);
	EXPECT_EQ(sink.getInputs()[inlet_index].index, -1);
	EXPECT_EQ(block.getOutputs()[outlet_index].index, -1);


	patcher.patch(block, outlet_index, sink, inlet_index);

	// After Patch

	EXPECT_EQ(sink.getInputs()[inlet_index].index, outlet_index);
	EXPECT_EQ(block.getOutputs()[outlet_index].index, inlet_index);
	EXPECT_EQ(sink.getInputs()[inlet_index].block_ref, &block);
	EXPECT_EQ(block.getOutputs()[outlet_index].block_ref, &sink);
}


TEST_F(PatcherTest, singleBlockBlockPatch)
{
	// [block1] --> [block2]
	Block block1(1, 1);
	Block block2(1, 1);

	int outlet_index = 0; 
	int inlet_index = 0;
	Patcher patcher;

	// Before Patch

	EXPECT_TRUE(block2.getInputs()[inlet_index].block_ref == NULL);
	EXPECT_TRUE(block1.getOutputs()[outlet_index].block_ref == NULL);
	EXPECT_EQ(block2.getInputs()[inlet_index].index, -1);
	EXPECT_EQ(block1.getOutputs()[outlet_index].index, -1);


	patcher.patch(block1, outlet_index, block2, inlet_index);

	// After Patch

	EXPECT_EQ(block2.getInputs()[inlet_index].block_ref, &block1);
	EXPECT_EQ(block1.getOutputs()[outlet_index].block_ref, &block2);
	EXPECT_EQ(block2.getInputs()[inlet_index].index, outlet_index);
	EXPECT_EQ(block1.getOutputs()[outlet_index].index, outlet_index);

}

TEST_F(PatcherTest, chainBlockSinkPatch)
{
	//[block1]-->[block2]--> ... --> [sink]
	int nBlocks = 2;

	std::vector<Block> blocks;
	Sink sink(6);
	for(int i=0; i<nBlocks; i++)
	{
		blocks.push_back(Block(1, 1));	
	}

	int outlet_index = 0; 
	int inlet_index = 0;
	int sink_inlet_index = 0;
	Patcher patcher;

	// Patching
	int i=0;
	while( i<nBlocks-1)
	{
		// Before patch
		EXPECT_TRUE(blocks[i+1].getInputs()[inlet_index].block_ref == NULL);
		EXPECT_TRUE(blocks[i].getOutputs()[outlet_index].block_ref == NULL);
		EXPECT_EQ(blocks[i+1].getInputs()[inlet_index].index, -1);
		EXPECT_EQ(blocks[i].getOutputs()[outlet_index].index, -1);

		patcher.patch(blocks[i], outlet_index, blocks[i+1], inlet_index);

		// After Patch
		EXPECT_EQ(blocks[i+1].getInputs()[inlet_index].block_ref, &blocks[i]);
		EXPECT_EQ(blocks[i].getOutputs()[outlet_index].block_ref, &blocks[i+1]);
		EXPECT_EQ(blocks[i+1].getInputs()[inlet_index].index, outlet_index);
		EXPECT_EQ(blocks[i].getOutputs()[outlet_index].index, outlet_index);

		i++;
	}

	// Before patch
	EXPECT_TRUE(sink.getInputs()[inlet_index].block_ref == NULL);
	EXPECT_TRUE(blocks[i].getOutputs()[outlet_index].block_ref == NULL);
	EXPECT_EQ(sink.getInputs()[inlet_index].index, -1);
	EXPECT_EQ(blocks[i].getOutputs()[outlet_index].index, -1);

	patcher.patch(blocks[i], outlet_index, sink, sink_inlet_index);

	// After Patch
	EXPECT_EQ(sink.getInputs()[inlet_index].block_ref, &blocks[i]);
	EXPECT_EQ(blocks[i].getOutputs()[outlet_index].block_ref, &sink);
	EXPECT_EQ(sink.getInputs()[inlet_index].index, outlet_index);
	EXPECT_EQ(blocks[i].getOutputs()[outlet_index].index, outlet_index);


}

#include "testPatcher.h"

#include "Patcher.h"

PatcherTest::PatcherTest() 
{};

PatcherTest::~PatcherTest() {};

void PatcherTest::SetUp() {};

void PatcherTest::TearDown() {};

TEST_F(PatcherTest, singleBlockSink_GOODPatch)
{
	Sink sink(1);
	Block block(1, 1);

	int outlet_index = 0; 
	int inlet_index = 0;

	// Before Patch

	EXPECT_TRUE(sink.getInput(inlet_index).block_ref == NULL);
	EXPECT_TRUE(block.getOutput(outlet_index).block_ref == NULL);
	EXPECT_EQ(sink.getInput(inlet_index).index, -1);
	EXPECT_EQ(block.getOutput(outlet_index).index, -1);

	EXPECT_TRUE( Patcher::patch(block, outlet_index, sink, inlet_index) ); 

	// After Patch
	EXPECT_EQ(sink.getInput(inlet_index).index, outlet_index);
	EXPECT_EQ(block.getOutput(outlet_index).index, inlet_index);
	EXPECT_EQ(sink.getInput(inlet_index).block_ref, &block);
	EXPECT_EQ(block.getOutput(outlet_index).block_ref, &sink);
}

TEST_F(PatcherTest, singleBlockSink_PatchExceptions)
{
	Sink sink(1);
	Block block(1, 1);

	// Give it a wrong inlet index

	int outlet_index = 0; 
	int inlet_index = 23;

	EXPECT_THROW( Patcher::patch(block, outlet_index, sink, inlet_index), std::range_error);

	// After Patch
	EXPECT_THROW(sink.getInput(inlet_index), std::range_error);
	EXPECT_TRUE(block.getOutput(outlet_index).block_ref == NULL);
	EXPECT_EQ(block.getOutput(outlet_index).index, -1);

	// Give it a wrong outlet index

	outlet_index = 3; 
	inlet_index = 0;
	EXPECT_THROW( Patcher::patch(block, outlet_index, sink, inlet_index), std::range_error);

	// After Patch
	EXPECT_TRUE(sink.getInput(inlet_index).block_ref == NULL);
	EXPECT_EQ(sink.getInput(inlet_index).index, -1);
	EXPECT_THROW(block.getOutput(outlet_index), std::range_error);

	// Give it a wrong input outlet index

	outlet_index = 3; 
	inlet_index = -1;
	EXPECT_THROW( Patcher::patch(block, outlet_index, sink, inlet_index), std::range_error);

	// After Patch
	EXPECT_THROW(sink.getInput(inlet_index), std::range_error);
	EXPECT_THROW(block.getOutput(outlet_index), std::range_error);
}


TEST_F(PatcherTest, singleBlockBlockPatch)
{
	// [block1] --> [block2]
	Block block1(1, 1);
	Block block2(1, 1);

	int outlet_index = 0; 
	int inlet_index = 0;

	// Before Patch

	EXPECT_TRUE(block2.getInput(inlet_index).block_ref == NULL);
	EXPECT_TRUE(block1.getOutput(outlet_index).block_ref == NULL);
	EXPECT_EQ(block2.getInput(inlet_index).index, -1);
	EXPECT_EQ(block1.getOutput(outlet_index).index, -1);


	EXPECT_TRUE( Patcher::patch(block1, outlet_index, block2, inlet_index) );

	// After Patch

	EXPECT_EQ(block2.getInput(inlet_index).block_ref, &block1);
	EXPECT_EQ(block1.getOutput(outlet_index).block_ref, &block2);
	EXPECT_EQ(block2.getInput(inlet_index).index, outlet_index);
	EXPECT_EQ(block1.getOutput(outlet_index).index, outlet_index);

}

TEST_F(PatcherTest, singleBlockBlock_PatchExceptions)
{
	Block destination(1, 12);
	Block block(1, 1);

	// Give it a wrong inlet index

	int outlet_index = 0; 
	int inlet_index = 23;

	EXPECT_THROW( Patcher::patch(block, outlet_index, destination, inlet_index), std::range_error);

	// After Patch
	EXPECT_THROW(destination.getInput(inlet_index), std::range_error);
	EXPECT_TRUE(block.getOutput(outlet_index).block_ref == NULL);
	EXPECT_EQ(block.getOutput(outlet_index).index, -1);

	// Give it a wrong outlet index

	outlet_index = 3; 
	inlet_index = 0;
	EXPECT_THROW( Patcher::patch(block, outlet_index, destination, inlet_index), std::range_error);

	// After Patch
	EXPECT_TRUE(destination.getInput(inlet_index).block_ref == NULL);
	EXPECT_EQ(destination.getInput(inlet_index).index, -1);
	EXPECT_THROW(block.getOutput(outlet_index), std::range_error);

	// Give it a wrong input outlet index

	outlet_index = 3; 
	inlet_index = -1;
	EXPECT_THROW( Patcher::patch(block, outlet_index, destination, inlet_index), std::range_error);

	// After Patch
	EXPECT_THROW(destination.getInput(inlet_index), std::range_error);
	EXPECT_THROW(block.getOutput(outlet_index), std::range_error);
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

	// Patching
	int i=0;
	while( i<nBlocks-1)
	{
		// Before patch
		EXPECT_TRUE(blocks[i+1].getInput(inlet_index).block_ref == NULL);
		EXPECT_TRUE(blocks[i].getOutput(outlet_index).block_ref == NULL);
		EXPECT_EQ(blocks[i+1].getInput(inlet_index).index, -1);
		EXPECT_EQ(blocks[i].getOutput(outlet_index).index, -1);

		EXPECT_TRUE( Patcher::patch(blocks[i], outlet_index, blocks[i+1], inlet_index) );

		// After Patch
		EXPECT_EQ(blocks[i+1].getInput(inlet_index).block_ref, &blocks[i]);
		EXPECT_EQ(blocks[i].getOutput(outlet_index).block_ref, &blocks[i+1]);
		EXPECT_EQ(blocks[i+1].getInput(inlet_index).index, outlet_index);
		EXPECT_EQ(blocks[i].getOutput(outlet_index).index, outlet_index);

		i++;
	}

	// Before patch
	EXPECT_TRUE(sink.getInput(inlet_index).block_ref == NULL);
	EXPECT_TRUE(blocks[i].getOutput(outlet_index).block_ref == NULL);
	EXPECT_EQ(sink.getInput(inlet_index).index, -1);
	EXPECT_EQ(blocks[i].getOutput(outlet_index).index, -1);

	EXPECT_TRUE( Patcher::patch(blocks[i], outlet_index, sink, sink_inlet_index) );

	// After Patch
	EXPECT_EQ(sink.getInput(inlet_index).block_ref, &blocks[i]);
	EXPECT_EQ(blocks[i].getOutput(outlet_index).block_ref, &sink);
	EXPECT_EQ(sink.getInput(inlet_index).index, outlet_index);
	EXPECT_EQ(blocks[i].getOutput(outlet_index).index, outlet_index);
}

TEST_F(PatcherTest, validatePatchTest)
{
	Block b11(1, 3), b22(2, 1), b33(3, 1);

	Patcher::patch(b11, 0, b22, 0);
	EXPECT_TRUE(Patcher::validatePatch(b11, 0, b22, 0));
	EXPECT_FALSE(Patcher::validatePatch(b11, 1, b33, 0));
	EXPECT_FALSE(Patcher::validatePatch(b11, 0, b22, 1));
}

TEST_F(PatcherTest, unpatchTest)
{
	Block b1(1, 2), b2(2, 1);
	Sink s(13);

	EXPECT_TRUE( Patcher::patch(b1, 0, b2, 1) );
	EXPECT_TRUE( Patcher::unpatch(b1, 0, b2, 1) );
	// EXPECT_FALSE( Patcher::unpatch(b1, 0, b2, 0));
}

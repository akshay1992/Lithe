#include "testBlock.h"
#include "Block.h"

BlockTest::BlockTest() {
};

BlockTest::~BlockTest() {};

void BlockTest::SetUp() {};

void BlockTest::TearDown() {};

TEST_F(BlockTest, incrementByDefaultOne) {

	Block block;
    block.setValue(1);
    int value = block.value();
    EXPECT_EQ(value+1, block.increment());
}

TEST_F(BlockTest, incrementBySpecificPositiveValue) {
	Block block;
    block.setValue(1);
    int value_before = block.value();
    int increment = 12;
    int value_after = block.increment(increment);
    EXPECT_EQ(value_before+increment, value_after);
}

TEST_F(BlockTest, incrementBySpecificNegativeValue) {
	Block block;
    block.setValue(1);
    int value_before = block.value();
    int increment = -7;
    int value_after = block.increment(increment);
    EXPECT_EQ(value_before+increment, value_after);
}




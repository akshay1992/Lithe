#include "testTerminal.h"
#include "Terminal.h"

TerminalTest::TerminalTest(void) {}

TerminalTest::~TerminalTest(void) {}

void TerminalTest::SetUp(void) {}

void TerminalTest::TearDown(void) {}

TEST_F(TerminalTest, DefaultTerminal_Test)
{
	Terminal t1 = Terminal();

	EXPECT_TRUE( t1.block_ref == NULL);
	EXPECT_EQ(t1.index, -1);
	EXPECT_EQ( t1.type, TERMINAL_TYPE_INVALID);
}

TEST_F(TerminalTest, BlockTerminalTest)
{
	Block b(2, 4);

	for(int i=0; i<b.getNumInputs(); i++)
	{
		EXPECT_EQ(b.getInput(i).type, TERMINAL_TYPE_INPUT );
	}
	
	for(int i=0; i<b.getNumOutputs(); i++)
	{
		EXPECT_EQ(b.getOutput(i).type, TERMINAL_TYPE_OUTPUT );
	}
}
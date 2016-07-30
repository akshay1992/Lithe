#include "Block.h"

Block::Block(int nInputs, int nOutputs)
{
	for(int i=0; i<nInputs; i++)
	{
		inputs.push_back(Terminal());
	}
	for(int i=0; i<nOutputs; i++)
	{
		outputs.push_back(Terminal());
	}
}

void Block::setOutput(int outletIndex, Block &destination_block, int inletIndex)
{
	Terminal destination(destination_block, inletIndex);

	setOutput(outletIndex, destination);
}

void Block::setOutput(int outletIndex, Terminal destination)
{
	outputs[outletIndex] = destination;
}

void Block::setInput(int inletIndex, Block &source_block, int outletIndex)
{
	Terminal source(source_block ,outletIndex);

	setInput(outletIndex, source);
}

void Block::setInput(int inletIndex, Terminal source)
{
	inputs[inletIndex] = source;
}

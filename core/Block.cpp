#include "Block.h"

int Block::running_count;

Block::Block(int nInputs, int nOutputs)
{
	running_count++;
	id = running_count;

	for(int i=0; i<nInputs; i++)
	{
		inputs.push_back(Terminal(TERMINAL_TYPE_INPUT));
	}
	for(int i=0; i<nOutputs; i++)
	{
		outputs.push_back(Terminal(TERMINAL_TYPE_OUTPUT));
	}
}

Terminal Block::getInput(int index)
{ 
	return getInputs()[index]; 
}
	
Terminal Block::getOutput(int index)
{ 
	return getOutputs()[index]; 
}

int Block::getNumInputs(void) 
{ 
	return inputs.size(); 
}
int Block::getNumOutputs(void) 
{ 
	return outputs.size(); 
}


void Block::setOutput(int outletIndex, Block &destination_block, int inletIndex)
{
	Terminal destination(destination_block, inletIndex, TERMINAL_TYPE_OUTPUT);

	setOutput(outletIndex, destination);
}

void Block::setOutput(int outletIndex, Terminal destination)
{
	outputs[outletIndex] = destination;
}

void Block::setInput(int inletIndex, Block &source_block, int outletIndex)
{
	Terminal source(source_block ,outletIndex, TERMINAL_TYPE_OUTPUT);

	setInput(outletIndex, source);
}

void Block::setInput(int inletIndex, Terminal source)
{
	inputs[inletIndex] = source;
}
#include "Block.h"

int Block::running_count;

Block::Block(int nInputs, int nOutputs)
{
	running_count++;
	id = running_count;

	for(int i=0; i<nInputs; i++)
	{
		inputs.push_back(Terminal(i, TERMINAL_TYPE_INPUT));
	}
	for(int i=0; i<nOutputs; i++)
	{
		outputs.push_back(Terminal(i, TERMINAL_TYPE_OUTPUT));
	}
}

bool Block::isValidOutput(int outletIndex) 
{ 
	return (outletIndex < getNumOutputs()) && (outletIndex >= 0); 
}

bool Block::isValidInput(int inletIndex) 
{ 
	return (inletIndex < getNumInputs()) && (inletIndex >= 0); 
}

const Terminal Block::getInput(int index)
{ 
	if(! isValidInput(index))
	{
		throw std::range_error("Invalid Inlet Index");
	}
	return inputs[index]; 		
}
	
const Terminal Block::getOutput(int index)
{ 
	if( ! isValidOutput(index))
	{
		throw std::range_error("Invalid Outlet Index");
	}

	return outputs[index]; 
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
	if(isValidOutput(outletIndex))
	{
		outputs[outletIndex] = destination;
	}
	else 
	{
		throw std::range_error("Invalid Outlet Index");
	}
}

void Block::setInput(int inletIndex, Block &source_block, int outletIndex)
{
	Terminal source(source_block ,outletIndex, TERMINAL_TYPE_OUTPUT);

	setInput(outletIndex, source);
}

void Block::setInput(int inletIndex, Terminal source)
{
	if(isValidInput(inletIndex))
	{
		inputs[inletIndex] = source;
	}
	else 
	{
		throw std::range_error("Invalid Inlet Index");
	}
}

void Block::resetOutput(int outletIndex)
{
	if(isValidOutput(outletIndex))
	{
		outputs[outletIndex].block_ref = NULL;
		outputs[outletIndex].index = -1;
	}
	else 
	{
		throw std::range_error("Invalid Outlet Index");
	}
}

void Block::resetInput(int inletIndex)
{
	if(isValidInput(inletIndex))
	{
		inputs[inletIndex].block_ref = NULL;
		inputs[inletIndex].index = -1;
	}
	else 
	{
		throw std::range_error("Invalid Inlet Index");
	}
}
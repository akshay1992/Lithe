#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

class Block;

// \brief A terminal is an abstraction of the inlets and outlets of a block
class Terminal
{
public:
	Terminal( Block &block_reference, int terminal_index)		:
		block_ref(&block_reference),
		index(terminal_index)
	{	}

	Terminal(void)		:
		block_ref(NULL),
		index(-1)
	{	}

	Block* block_ref;
	int index;
};

/// \brief Abstract class for each module block
class Block 
{
public:
	/// Creates appropriate number of ports and initializes them to NULL pointers.
	Block(int nInputs, int nOutputs);

	const std::vector<Terminal> getInputs(void) { return inputs; }
	const std::vector<Terminal> getOutputs(void) { return outputs; }
	int getNumInputs(void) { return inputs.size(); }
	int getNumOutputs(void) { return outputs.size(); }

	bool isValidOutput(int outletIndex) { return outletIndex < getNumOutputs(); }
	bool isValidInput(int inletIndex) { return inletIndex < getNumInputs(); }

	void setOutput(int outletIndex, Block &destination_block, int inletIndex);
	void setOutput(int outletIndex, Terminal destination);
	void setInput(int inletIndex, Block &source_block, int outletIndex);
	void setInput(int inletIndex, Terminal source);

	int getID(void)  { return id; }

protected:
	int id;
	std::vector<Terminal> inputs;
	std::vector<Terminal> outputs;
};

#endif
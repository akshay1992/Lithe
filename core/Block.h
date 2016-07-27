#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

/// \brief Abstract class for each module block
class Block 
{
public:
	/// Creates appropriate number of ports and initializes them to NULL pointers.
	Block(int nInputs, int nOutputs)
	{
		for(int i=0; i<nInputs; i++)
		{
			inputs.push_back(NULL);
		}
		for(int i=0; i<nOutputs; i++)
		{
			outputs.push_back(NULL);
		}
	}

	const std::vector<Block *> getInputs(void) { return inputs; }
	const std::vector<Block *> getOutputs(void) { return outputs; }
	int getNumInputs(void) { return inputs.size(); }
	int getNumOutputs(void) { return outputs.size(); }

protected:
	std::vector<Block *> inputs;
	std::vector<Block *> outputs;
};

#endif
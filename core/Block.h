#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

#include "Terminal.h"
class Terminal;

/*!
	\brief Abstract class for each module block
 
	TODO: More info here. 

*/
class Block 
{
public:
	/// Creates appropriate number of ports and initializes them to NULL pointers.
	Block(int nInputs, int nOutputs);

	const std::vector<Terminal> getInputs(void) { return inputs; }
	const std::vector<Terminal> getOutputs(void) { return outputs; }
	Terminal getInput(int index = 0);
	Terminal getOutput(int index = 0);
	int getNumInputs(void);
	int getNumOutputs(void);

	/// @brief Returns true if the specified outlet index is valid. 
	bool isValidOutput(int outletIndex) 
	{ 
		return (outletIndex < getNumOutputs()) && (outletIndex >= 0); 
	}
	
	/// @brief Returns true if the specified inlet index is valid. 
	bool isValidInput(int inletIndex) 
	{ 
		return (inletIndex < getNumInputs()) && (inletIndex >= 0); 
	}

	void setOutput(int outletIndex, Block &destination_block, int inletIndex);
	void setOutput(int outletIndex, Terminal destination);
	void setInput(int inletIndex, Block &source_block, int outletIndex);
	void setInput(int inletIndex, Terminal source);

	int getID(void)  { return id; }

protected:
	/// Unique ID for each block. 
	int id;

	/// This is used to give each block a unique ID
	static int running_count;
	std::vector<Terminal> inputs;
	std::vector<Terminal> outputs;
};

#endif
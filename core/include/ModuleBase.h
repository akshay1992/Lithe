#ifndef MODULE_BASE_H
#define MODULE_BASE_H

#include "Node.h"

// A block is a node with audio processing and parameters included. It is an abstract class. 
// It has a virtual function to implement the DSP
// It also has parameters along with ranges (take from allosystem?)

class ModuleBase : private Node
{
public:
	using Node::getID;


private:

};



#endif //MODULE_BASE_H

// ----- OLD --------
// #include <vector>

// #include "Terminal.h"
// class Terminal;

// /**
// 	\brief Abstract class for each node in a directed graph. 
 
// 	Each block has a defined number of inlets and outlets. Each instance also has 
// 	a unique numerical ID that helps identify it in a graph. 
// */
// class Block 
// {
// public:
// 	/// Creates appropriate number of ports and initializes them to NULL pointers.
// 	Block(int nInputs, int nOutputs);

// 	// const std::vector<Terminal> getInputs(void) { return inputs; }
// 	// const std::vector<Terminal> getOutputs(void) { return outputs; }
// 	const Terminal getInput(int index = 0);
// 	const Terminal getOutput(int index = 0);
// 	int getNumInputs(void);
// 	int getNumOutputs(void);

// 	/// Returns true if the specified outlet index is valid. 
// 	bool isValidOutput(int outletIndex);
	
// 	/// Returns true if the specified inlet index is valid. 
// 	bool isValidInput(int inletIndex);

// 	void setOutput(int outletIndex, Block &destination_block, int inletIndex);
// 	void setOutput(int outletIndex, Terminal destination);
// 	void setInput(int inletIndex, Block &source_block, int outletIndex);
// 	void setInput(int inletIndex, Terminal source);
// 	void resetOutput(int outletIndex);
// 	void resetInput(int inletIndex);

// 	int getID(void)  { return id; }

// protected:
// 	/// Unique ID for each block. 
// 	int id;

// 	/// This is used to give each block a unique ID
// 	static int running_count;
// 	std::vector<Terminal> inputs;
// 	std::vector<Terminal> outputs;
// };
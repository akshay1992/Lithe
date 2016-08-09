#ifndef TERMINAL_H
#define TERMINAL_H

#include "Block.h"

class Block;

/// \brief Specifies type of Terminal
enum TerminalType
{
	TERMINAL_TYPE_INVALID,
	TERMINAL_TYPE_INPUT,
	TERMINAL_TYPE_OUTPUT
};

/*! 
	\brief An abstraction of the inlets and outlets of a Block.
	
	Terminals are usually a part of a Block. They specify connections using the block_ref. 
*/
class Terminal
{
public:
	Terminal( Block &block_reference, int terminal_index, TerminalType t_type)		:
		block_ref(&block_reference),
		index(terminal_index),
		type(t_type)
	{	}

	Terminal(void)		:
		block_ref(NULL),
		index(-1),
		type(TERMINAL_TYPE_INVALID)
	{	}

	Terminal( int myindex, TerminalType t_type )		:
		block_ref(NULL),
		index(-1),
		type(t_type), 
		myIndex(myindex)
	{	}

	/// Enables a single sample delay. This is to ensure causality in feedback loops.
	void enableSampleDelay(void) { SampleDelayEnabled = true; }

	/// Disables a single sample delay. 
	void disableSampleDelay(void) {SampleDelayEnabled = false; }

	/// block_ref is the reference to the Block that this Terminal is connected to. 
	Block* block_ref;
	/// Inlet/outlet index of the block that this Terminal is connected to.
	int index;
	TerminalType type;

	/// Inlet/outlet index of the block that this Terminal is a PART OF.
	int myIndex;

private:
	bool SampleDelayEnabled;
};

#endif
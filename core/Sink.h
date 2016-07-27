#ifndef SINK_H
#define SINK_H

#include "Block.h"

class Sink : public Block
{
public:
	Sink(int nInputs) : Block(nInputs, 0) {}

private:
	using Block::getNumOutputs;
	using Block::getOutputs;
};

#endif
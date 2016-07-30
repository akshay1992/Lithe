#ifndef PATCHING_UTILS_H
#define PATCHING_UTILS_H

#include "Block.h"
#include "Sink.h"
#include <vector>
#include <exception>

/// Defines a patch by the terminal configs in each block
struct Patch
{
	Terminal source;
	Terminal destination;
};

class Patcher
{
public:
	void patch(Block &source, int outlet_index, Block &destination, int inlet_index);
	void patch(Block &source, int outlet_index, Sink &destination, int inlet_index);
	void unpatch(Patch patch);
	void refreshProcessOrder(void);

	std::vector<Patch> patches;
	Sink* sink;
};

#endif
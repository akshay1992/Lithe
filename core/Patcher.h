#ifndef PATCHING_UTILS_H
#define PATCHING_UTILS_H

#include "Block.h"
#include "Sink.h"
#include <vector>

struct Patch
{
	Block * node1;
	Block * node2;
};

class Patcher
{
public:
	static void patch(Block &input, int outlet_index, Block &output, int inlet_index);
	static void patch(Block &input, int outlet_index, Sink &output, int inlet_index);
	static void unpatch(Patch patch);
	static void refreshProcessOrder(void);

	static std::vector<Patch> patches;
	Sink* sink;
};

#endif
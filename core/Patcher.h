#ifndef PATCHING_UTILS_H
#define PATCHING_UTILS_H

#include "Block.h"
#include "Sink.h"
#include <vector>

/// Defines a patch by the \link Terminal Terminals \endlink of the two Block instances
struct Patch
{
	Terminal source;
	Terminal destination;
};

/** \brief Utility class used for patching Block instances
*/

class Patcher
{
public:
	static bool patch(Block &source, int outlet_index, Block &destination, int inlet_index);
	static bool unpatch(Block &source, int outlet_index, Block &destination, int inlet_index);
	static void refreshProcessOrder(void);

	std::vector<Patch> patches;
	Sink* sink;

	static bool validatePatch(Block &source, int outlet_index, Block &destination, int inlet_index);
};

#endif
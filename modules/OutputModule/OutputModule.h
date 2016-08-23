#ifndef OUTPUT_MODULE_H
#define OUTPUT_MODULE_H

#include "Sink.h"
#include "allocore/sound/al_AudioScene.hpp"

class OutputModule : public Sink
{
public:
	OutputModule() : 
		Sink(12)
	{

	}

};

#endif //OUTPUT_MODULE_H
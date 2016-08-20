#include "Sink.h"
#include "Sorter.h"

void Sink::refreshProcessOrder(void)
{
	BFS::sort(*this);
}

void Sink::Process(void)
{
	// TODO: Insert Panner code here.
	doneProceessing();
}

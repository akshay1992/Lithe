#include "Sink.h"
#include "Sorter.h"

void Sink::refreshProcessOrder(void)
{
	BFS::sort(*this);
}
#include "Lithe/Sink.h"
#include "Lithe/Sorter.h"

Sink::Sink(int inlets) :
		Node::Node(inlets, 0)
{
}

void Sink::Process(void)
{
	DSP();
	Node::resetAll_ProcessState();
	doneProceessing();
}

void Sink::refreshProcessOrder(void)
{
	BFS::sort(*this);
}
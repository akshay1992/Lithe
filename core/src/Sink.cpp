#include "Sink.h"
#include "Sorter.h"

#define thisClass Sink

Sink::Sink(int inlets) :
		Node::Node(inlets, 0)
{
	set_DSP_method((DSP_Method)& Sink::DSP);
}

void Sink::refreshProcessOrder(void)
{
	BFS::sort(*this);
}
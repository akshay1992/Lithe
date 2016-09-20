#include "Lithe/Sink.h"
#include "Lithe/Sorter.h"

Sink::Sink(int inlets) :
		Node::Node(inlets, 0)
{
	set_DSP_method((DSP_Method)& Sink::DSP);
}

void Sink::refreshProcessOrder(void)
{
	BFS::sort(*this);
}
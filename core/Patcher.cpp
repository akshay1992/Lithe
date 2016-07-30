#include "Patcher.h"
#include <iostream>

void Patcher::patch(Block &source, int outlet_index, Block &destination, int inlet_index)
{
	if(source.isValidOutput(outlet_index) && destination.isValidInput(inlet_index))
	{
		source.setOutput(outlet_index, destination, inlet_index);
		destination.setInput(inlet_index, source, outlet_index);		
	}
	else
	{
		// TODO: Error handling
		std::cout << "ERROR" << std::endl;
	}
}

void Patcher::patch(Block &source, int outlet_index, Sink &destination, int inlet_index)
{
	if(source.isValidOutput(outlet_index) && destination.isValidInput(inlet_index))
	{
		source.setOutput(outlet_index, destination, inlet_index);
		destination.setInput(inlet_index, source, outlet_index);		
	}
	else
	{
		// TODO: Error handling
		std::cout << "ERROR" << std::endl;
	}
}

void Patcher::unpatch(Patch patch)
{

}

void Patcher::refreshProcessOrder(void)
{

}


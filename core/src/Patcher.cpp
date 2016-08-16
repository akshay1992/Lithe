#include "Patcher.h"
// #include <iostream>

void Patcher::connect(Inlet& inlet, Outlet& outlet)
{
	if( inlet.isConnected() )	inlet.disconnect();
	if( outlet.isConnected() ) outlet.disconnect();

	inlet.connected_outlet = &outlet;
	outlet.connected_inlet = &inlet;
}

void Patcher::disconnect(Inlet& inlet, Outlet& outlet)
{
	inlet.connected_outlet = NULL;
	outlet.connected_inlet = NULL;
}



// bool Patcher::patch(Block &source, int outlet_index, Block &destination, int inlet_index)
// {
// 	try
// 	{
// 		Terminal sourceState = source.getOutput(outlet_index);
// 		Terminal destinationState = destination.getInput(inlet_index);
// 	}
// 	catch(std::range_error)
// 	{
// 		throw std::range_error("Patching exception, invalid inlet/outlet index");
// 		return false;
// 	}

// 	source.setOutput(outlet_index, destination, inlet_index);
// 	destination.setInput(inlet_index, source, outlet_index);

// 	return true;
// }

// bool Patcher::unpatch(Block &source, int outlet_index, Block &destination, int inlet_index)
// {
// 	try
// 	{
// 		Terminal sourceState = source.getOutput(outlet_index);
// 		Terminal destinationState = destination.getInput(inlet_index);		
// 	}
// 	catch(std::range_error)
// 	{
// 		throw std::range_error("Unpatching exception, invalid inlet/outlet index");
// 		return false;
// 	}

// 	if( Patcher::validatePatch(source, outlet_index, destination, inlet_index) )
// 	{
// 		source.resetOutput(outlet_index);
// 		destination.resetInput(inlet_index);

// 		return true;
// 	}

// 	return false;
// }

// bool Patcher::validatePatch(Block &source, int outlet_index, Block &destination, int inlet_index)
// {
// 	Terminal sourceTerminal = source.getOutput(outlet_index);
// 	Terminal destinationTerminal = destination.getInput(inlet_index);

// 	// if( sourceTerminal.block_ref == NULL || destinationTerminal.block_ref == NULL)
// 	// 	return false;

// 	// if( sourceTerminal.block_ref != &destination || destinationTerminal.block_ref != &source)
// 	// 	return false;

// 	// if ( sourceTerminal.index != destinationTerminal.myindex || destinationTerminal.index != sourceTerminal.myindex) return false;

// 	return true;
// }

// void Patcher::refreshProcessOrder(void)
// {

// }

#ifndef ATTENUVERTER_H
#define ATTENUVERTER_H

#include "Lithe/Sample.h"
#include "Lithe/Node.h"
#include "Lithe/Parameter.h"

/// @brief An Atteuator-inverter component used within a module. 
template< typename T >
class AttenuverterT
{
	Attenuverter(Node& node, );

	int inletIndex = -1;
	int sampleValIndex = 0;
	Node* node_ref = NULL;
};
typedef AttenuverterT<float> Attenuverter;

#endif //ATTENUVERTER_H
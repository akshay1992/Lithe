#ifndef SORTER_HPP
#define SORTER_HPP

#include <vector>
#include <algorithm> // for std::min
#include "Lithe/Sink.h"

#include <iostream>
using namespace std;

/** @brief BFS-based algorithm that enables appropriate sample-delays on the inlets of a graph.
    
    It does a breadth-first traversal starting at the sink and if any back edges are found at
    connected inlets, it enables it's single-sample delay
	@ingroup Sorter
 */
class BFS
{
private:
	static void visit(Node& node, int level);

public:	
	static void sort(Sink& sink);
};

/** @brief [INCOMEPLTE/UNTESTED] Topologically sorts all nodes connected to a sink to establish a processing order.

	This is done using Tarjan's algorithm. 
	@ingroup Sorter

*/ 
class TarjanSort
{
private:	
	static void visit(Node& node, int& index, std::vector<Node*>& stack, std::vector< std::vector<Node *> > & sccs);

public:
	static void sort(Sink& sink);
};

#endif //SORTER_HPP
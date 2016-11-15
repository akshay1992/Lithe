#ifndef SORTER_H
#define SORTER_H

#include <vector>
#include <algorithm> // for std::min
#include "Lithe/Node.h"

namespace lithe {

/** @brief BFS-based algorithm that enables appropriate sample-delays on the inlets of a graph.
    
    It does a breadth-first traversal starting at the Node and if any back edges are found at
    connected inlets, it enables it's single-sample delay

    Node: It treats a given node as a sink and traverses upstream. Behaviour is unknown when
    the node is actually in the middle of a complex graph.

	@ingroup AudioGraph
 */
class BFS
{
private:
	static void visit(Node& node, int level);

public:	
	static void sort(Node& sink);
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
	static void sort(Node& sink);
};

}; // namespace lithe

#endif //SORTER_H
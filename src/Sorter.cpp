#include "Lithe/Sorter.h"
#include "Lithe/Inlet.h"
#include "Lithe/Outlet.h"

namespace lithe {

void BFS_visit(Node& node, int level, std::map<Node*, int /*index*/>& sortState)
{
	std::vector<Node*> next_node_set;

	for(int i=0; i< node.numInlets(); ++i)
	{
		if ( node.getInlet(i).isConnected() )
		{
			Node* successor_node = node.getInlet(i).getConnectedOutlet()->getParentNode();
			if (sortState.count(successor_node) == 0)
			{
				// Forward edge found (not previously discovered).
				node.getInlet(i).disableSampleDelay();
				sortState[successor_node] = level;
				next_node_set.push_back(successor_node);	// Add it to the list of nodes to traverse in the next call
			}
			else if( level > sortState[successor_node] )
			{
				// Back edge found. 
				node.getInlet(i).enableSampleDelay();
			}
		}
	}

	// Travese the next list of nodes
	int new_level = level+1;
	for(int i=0; i< next_node_set.size(); ++i)
	{
		BFS_visit(*(next_node_set[i]), new_level, sortState);
	}
}

void BFS::sort(Node& sink)
{
	std::map<Node*, int> _sortState;
	Node::resetAll_SampleDelayState(false);
	_sortState[&sink] = 0;
	BFS_visit(sink, 1, _sortState);
}

};  // namespace lithe
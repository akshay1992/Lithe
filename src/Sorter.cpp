#include "Lithe/Sorter.h"
#include "Lithe/Inlet.h"
#include "Lithe/Outlet.h"

void BFS::visit(Node& node, int level)
{
	std::vector<Node*> next_node_set;

	for(int i=0; i< node.numInlets(); ++i)
	{
		if ( node.getInlet(i).isConnected() )
		{
			Node* successor_node = node.getInlet(i).connected_outlet->parent_node;
			if (successor_node->index == -1)
			{
				// Forward edge found (not previously discovered).
				node.getInlet(i).disableSampleDelay();
				successor_node->index = level;
				next_node_set.push_back(successor_node);	// Add it to the list of nodes to traverse in the next call
			}
			else if( level > successor_node->index )
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
		visit(*(next_node_set[i]), new_level);
	}
}

void BFS::sort(Sink& sink)
{
	Node::resetSortParams(-1, -1, false);
	Node::resetSampleDelayState(false);
	sink.index = 0;
	visit(sink, 1);
	// Node::resetSortParams(-1, -1, false); 	// Since they are not used further
}


//------------------------------------

void TarjanSort::visit(Node& node, int& index, std::vector<Node*>& stack, std::vector< std::vector<Node *> >& sccs)
{
	node.index = index;
	node.lowLink = index;
	index++;
	stack.push_back( &node );
	node.onStack = true;

	for ( int i=0; i< node.numInlets(); ++i)
	{
		if ( node.getInlet(i).isConnected() )
		{
			Node& successor_node = *node.getInlet(i).connected_outlet->parent_node;
			if (successor_node.index == -1)
			{
				visit(successor_node, index, stack, sccs);
				node.lowLink = std::min(node.lowLink, successor_node.lowLink);
			}
			else if ( successor_node.onStack)
			{
				successor_node.lowLink = std::min(successor_node.lowLink, node.index);
			}
		}
	}

	if(node.lowLink == node.index) 
	{
		Node* popped_node;
		// Start a new SCC ---- TODO
		std::vector< Node *> scc;
		do
		{
			popped_node = stack.back();
			stack.pop_back();
			popped_node->onStack = false;			
			scc.push_back(popped_node);
			// OUTPUT SCC -- TODO	
		} while( popped_node != &node);
		sccs.push_back(scc);
	}
}

void TarjanSort::sort(Sink& sink)
{
	Node::resetSortParams(-1, -1, false);
	int index = 0;
	std::vector<Node *> stack;
	std::vector< std::vector<Node *> > sccs;

	visit(sink, index, stack, sccs);

	// cout << "SCCS:  " << endl;
	for(int i=0; i<sccs.size(); i++)
	{
		std::vector< Node *> scc = sccs.back();
		// cout << "{ " ;
		for(int j=0; j<scc.size(); j++)
		{
			// cout << scc[j]->getID()<< ", ";
		}
		 // cout << " }" << endl;
		sccs.pop_back();
	}

}
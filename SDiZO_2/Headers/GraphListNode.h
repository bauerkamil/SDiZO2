#pragma once
#include "Edge.h"

namespace Graphs
{
	struct GraphListNode
	{
		Edge* edge;
		GraphListNode* prevNode;
		GraphListNode* nextNode;
		GraphListNode(Edge* value, GraphListNode* previous, GraphListNode* next)
			: edge(value), prevNode(previous), nextNode(next) {}
	};
}

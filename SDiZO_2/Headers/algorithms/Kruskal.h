#pragma once
#include <iostream>
#include <stdexcept>
#include "../Edge.h"
#include "../GraphListNode.h"
#include "../ListGraph.h"
#include "../MatrixGraph.h"
#include "../utils/EdgeHeapMin.h"

namespace Graphs
{
	class Kruskal
	{
	public:
		Kruskal();
		~Kruskal();
		virtual Edge** getMST(MatrixGraph* graph);
		virtual Edge** getMST(ListGraph* graph);
		virtual void printMST(std::ostream& out, Edge** mst, size_t vertexNum);

		// structure pointer is null
		const std::out_of_range* structure_null = new std::out_of_range("Structure pointer is null");
	private:
		bool visitedEveryVertex(size_t* visitedArr, size_t vertexNum);
	};
}
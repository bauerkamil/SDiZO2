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
	class Dijkstra
	{
	public:
		Dijkstra();
		~Dijkstra();
		virtual int** getMinPaths(MatrixGraph* graph, size_t beginningV);
		virtual int** getMinPaths(ListGraph* graph, size_t beginningV);
		virtual void printMinPaths(std::ostream& out, int** paths, size_t vertexNum);
		virtual void printMinPath(std::ostream& out, int** paths, size_t vertexNum, size_t destination);

		// structure pointer is null
		const std::out_of_range* structure_null = new std::out_of_range("Structure pointer is null");
		const std::invalid_argument* invalid_vertex = new std::invalid_argument("Invalid vertex");
	private:
	};
}
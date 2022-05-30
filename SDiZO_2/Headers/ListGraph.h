#pragma once
#include <iostream>
#include <stdexcept>
#include "Edge.h"
#include "GraphListNode.h"

namespace Graphs
{
	class ListGraph
	{
	public:
		// class constructor
		ListGraph(bool isDirected);
		// class destructor
		~ListGraph();
		// prints the matrix in console
		virtual void print(std::ostream& out);
		//clears previous list and fills based on values of given args - edgeList[edgeNum][3] and vertexNum
		virtual void setNieghbourhoodList(size_t** edgeList, size_t vertexNum, size_t edgeNum, bool isDirected);
		//returns neighbourhood list
		virtual GraphListNode** getNieghbourhoodList();
		//returns number of vertexes
		virtual size_t getVertexNumber();
		//returns number of edges
		virtual size_t getEdgeNumber();
		//returns true if graph is directed
		virtual bool getIsDirected();
		//deletes neighbourhood list
		virtual void clear();
		// invalid vertex exception
		const std::invalid_argument* invalid_vertex = new std::invalid_argument("Invalid vertex");
		// structure pointer is null
		const std::out_of_range* matrix_null = new std::out_of_range("Structure pointer is null");

	private:
		GraphListNode** incidenceMatrix;
		size_t vertexNum;
		size_t edgeNum;
		bool isDirected;

		void addEnd(size_t vertex, Edge* edge);
	};
}

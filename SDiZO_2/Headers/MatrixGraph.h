#pragma once
#include <iostream>
#include <stdexcept>

namespace Graphs
{
	//dynamic matrix graph implementation
	class MatrixGraph
	{
	public:
		// class constructor
		MatrixGraph(bool isDirected);
		// class destructor
		~MatrixGraph();
		// prints the matrix in console
		virtual void print(std::ostream& out);
		// adds vertex to the end of graph
		virtual void addVertex();
		// adds edge between two vertexes
		virtual void addEdge(size_t value, size_t vertex1, size_t vertex2);
		//clears any previous matrix and creates new based on given arguments - edgeList[edgeNum][3] and vertexNum
		virtual void setIncidenceMatrix(size_t** edgeList, size_t vertexNum, size_t edgeNum);
		// returns incidence matrix
		virtual int** getIncidenceMatrix();
		//returns number of vertexes
		virtual size_t getVertexNumber();
		//returns number of edges
		virtual size_t getEdgeNumber();
		//returns true if graph is directed
		virtual bool getIsDirected();
		//deletes everything inside structue
		virtual void clear();
		// invalid vertex exception
		const std::invalid_argument* invalid_vertex = new std::invalid_argument("Invalid vertex");
		// structure pointer is null
		const std::out_of_range* matrix_null = new std::out_of_range("Structure pointer is null");

	private:
		int** incidenceMatrix;
		size_t vertexNum;
		size_t edgeNum;
		bool isDirected;
	};
}

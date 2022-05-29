#include "../Headers/MatrixGraph.h"

Graphs::MatrixGraph::MatrixGraph(bool isDirected)
{
	this->vertexNum = 0;
	this->edgeNum = 0;
	this->incidenceMatrix = nullptr;
	this->isDirected = isDirected;
}

Graphs::MatrixGraph::~MatrixGraph()
{
	clear();
}

void Graphs::MatrixGraph::print(std::ostream& out)
{
	if (this->vertexNum > 0 && this->incidenceMatrix != nullptr)
	{
		out << "   ";
		for (size_t i = 0; i < edgeNum; i++)
		{
			out << i << "  ";
		}
		out << "\n";
		for (size_t i = 0; i < vertexNum; i++)
		{
			out << i << " [";
			for (size_t j = 0; j < edgeNum-1; j++)
			{
				out << this->incidenceMatrix[i][j] << ", ";
			}
			out << this->incidenceMatrix[i][edgeNum-1] << "]\n";
		}
		
		return;
	}
	out << "Data structure is empty" << std::endl;
}

void Graphs::MatrixGraph::addVertex()
{
	int** newMatrix = new int* [vertexNum + 1];
	for (size_t i = 0; i < vertexNum; i++)
	{
		newMatrix[i] = incidenceMatrix[i];
	}

	int* newVertex = new int[edgeNum];
	newMatrix[vertexNum] = newVertex;

	this->vertexNum++;
	this->incidenceMatrix = newMatrix;
}

void Graphs::MatrixGraph::addEdge(size_t value, size_t vertex1, size_t vertex2)
{
	int** newMatrix = new int* [vertexNum];

	for (size_t i = 0; i < vertexNum; i++)
	{
		int* newVertex = new int[edgeNum + 1];

		for (size_t j = 0; j < edgeNum; j++)
		{
			newMatrix[i][j] = incidenceMatrix[i][j];
		}
	}

	newMatrix[vertex1][edgeNum + 1] = value;
	if (isDirected)
	{
		int minusValue = 0 - value;
		newMatrix[vertex2][edgeNum + 1] = minusValue;
	}
	else
		newMatrix[vertex2][edgeNum + 1] = value;

	this->edgeNum++;
	this->incidenceMatrix = newMatrix;
}

void Graphs::MatrixGraph::setIncidenceMatrix(size_t** edgeList, size_t vertexNum, size_t edgeNum)
{
	this->vertexNum = vertexNum;
	this->edgeNum = edgeNum;

	int** newMatrix = new int* [vertexNum];

	for (size_t i = 0; i < vertexNum; i++)
	{
		int* newVertex = new int[edgeNum];

		newMatrix[i] = newVertex;

		for (size_t j = 0; j < edgeNum; j++)
		{
			newMatrix[i][j] = 0;
		}
	}

	for (size_t i = 0; i < edgeNum; i++)
	{
		newMatrix[edgeList[i][0]][i] = edgeList[i][2];

		if (isDirected)
		{
			int minusValue = 0 - edgeList[i][2];
			this->incidenceMatrix[edgeList[i][1]][i] = minusValue;

		}
		else
			newMatrix[edgeList[i][1]][i] = edgeList[i][2];
	}

	this->incidenceMatrix = newMatrix;
}

int** Graphs::MatrixGraph::getIncidenceMatrix()
{
	return incidenceMatrix;
}

size_t Graphs::MatrixGraph::getVertexNumber()
{
	return vertexNum;
}

size_t Graphs::MatrixGraph::getEdgeNumber()
{
	return edgeNum;
}

bool Graphs::MatrixGraph::getIsDirected()
{
	return isDirected;
}

void Graphs::MatrixGraph::clear()
{
	if (incidenceMatrix != nullptr)
	{
		for (size_t i = 0; i < vertexNum; i++)
		{
			delete[] incidenceMatrix[i];
		}
	}
	delete[] this->incidenceMatrix;
	this->incidenceMatrix = nullptr;
	this->edgeNum = 0;
	this->vertexNum = 0;
}

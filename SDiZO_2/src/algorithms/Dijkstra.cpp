#include "../../Headers/algorithms/Dijkstra.h"

Graphs::Dijkstra::Dijkstra()
{
}

Graphs::Dijkstra::~Dijkstra()
{
}

int** Graphs::Dijkstra::getMinPaths(MatrixGraph* graph, size_t beginningV)
{
	size_t edgeNum = graph->getEdgeNumber();
	size_t vertexNum = graph->getVertexNumber();
	int** incidenceMatrix = graph->getIncidenceMatrix();

	if (incidenceMatrix == nullptr || vertexNum == 0)
	{
		throw* structure_null;
	}
	if (vertexNum == 1 || edgeNum == 0)
	{
		return nullptr;
	}
	if (beginningV > vertexNum)
	{
		throw* invalid_vertex;
	}


	int* pathsWeight = new int[vertexNum];
	int* fromVertex = new int[vertexNum];
	for (size_t i = 0; i < vertexNum; i++)
	{
		pathsWeight[i] = -1;
		fromVertex[i] = -1;
	}


	int** minPaths = new int* [2];
	minPaths[0] = pathsWeight;
	minPaths[1] = fromVertex;

	return minPaths;
}

int** Graphs::Dijkstra::getMinPaths(ListGraph* graph, size_t beginningV)
{
	size_t edgeNum = graph->getEdgeNumber();
	size_t vertexNum = graph->getVertexNumber();
	GraphListNode** neighbourhoodList = graph->getNieghbourhoodList();
	
	if (neighbourhoodList == nullptr || vertexNum == 0)
	{
		throw* structure_null;
	}
	if (beginningV > vertexNum)
	{
		throw* invalid_vertex;
	}
	if (vertexNum == 1 || edgeNum == 0 || neighbourhoodList[beginningV] == nullptr)
	{
		return nullptr;
	}

	int* pathsWeight = new int[vertexNum];
	int* fromVertex = new int[vertexNum];
	bool* visitedVertices = new bool[vertexNum];
	for (size_t i = 0; i < vertexNum; i++)
	{
		pathsWeight[i] = INT_MAX;
		fromVertex[i] = -1;
		visitedVertices[i] = false;
	}

	pathsWeight[beginningV] = 0;


	size_t pos = beginningV;

	for (size_t k = 0; k < vertexNum; k++)
	{
		visitedVertices[pos] = true;

		GraphListNode* node = neighbourhoodList[pos];

		while (node)
		{
			size_t destination = node->edge->destination;
			size_t weight = node->edge->weight;
			if (pathsWeight[destination] == INT_MAX || pathsWeight[destination] > pathsWeight[pos] + weight)
			{
				pathsWeight[destination] = pathsWeight[pos] + weight;
				fromVertex[destination] = pos;
			}
			node = node->nextNode;
		}

		int shortestPath = INT_MAX;
		size_t currShortest = vertexNum;
		for (size_t i = 0; i < vertexNum; i++)
		{
			if (pathsWeight[i] != INT_MAX)
			{
				std::cout << pathsWeight[i] << " ";
			}
			else
				std::cout << "- ";

			if (visitedVertices[i] == false)
			{

				if (pathsWeight[i] < shortestPath)
				{
					shortestPath = pathsWeight[i];
					currShortest = i;
				}
			}			
		}
		std::cout << std::endl;
		if (currShortest == vertexNum)
		{
			break;
		}
		pos = currShortest;
	}

	int** minPaths = new int* [2];
	minPaths[0] = pathsWeight;
	minPaths[1] = fromVertex;

	delete[] visitedVertices;

	return minPaths;
}

void Graphs::Dijkstra::printMinPaths(std::ostream& out, int** paths, size_t vertexNum)
{
	for (size_t i = 0; i < vertexNum; i++)
	{

	}
}


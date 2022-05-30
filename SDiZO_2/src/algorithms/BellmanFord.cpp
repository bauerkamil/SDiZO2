#include "../../Headers/algorithms/BellmanFord.h"

Graphs::BellmanFord::BellmanFord()
{
}

Graphs::BellmanFord::~BellmanFord()
{
}

int** Graphs::BellmanFord::getMinPaths(MatrixGraph* graph, size_t beginningV)
{
	size_t edgeNum = graph->getEdgeNumber();
	size_t vertexNum = graph->getVertexNumber();
	int** incidenceMatrix = graph->getIncidenceMatrix();

	if (incidenceMatrix == nullptr || vertexNum == 0)
	{
		throw* structure_null;
	}
	if (beginningV > vertexNum)
	{
		throw* invalid_vertex;
	}
	if (vertexNum == 1 || edgeNum == 0)
	{
		return nullptr;
	}

	int* pathsWeight = new int[vertexNum];
	int* fromVertex = new int[vertexNum];

	for (size_t i = 0; i < vertexNum; i++)
	{
		pathsWeight[i] = INT_MAX;
		fromVertex[i] = -1;
	}

	pathsWeight[beginningV] = 0;

	for (size_t i = 0; i < vertexNum; i++)
	{
		for (size_t pos = 0; pos < vertexNum; pos++)
		{
			for (size_t j = 0; j < edgeNum; j++)
			{
				if (incidenceMatrix[pos][j] > 0)
				{
					size_t weight = incidenceMatrix[pos][j];
					for (size_t dest = 0; dest < vertexNum; dest++)
					{
						if (incidenceMatrix[dest][j] < 0)
						{
							if (pathsWeight[dest] > pathsWeight[pos] + weight)
							{
								pathsWeight[dest] = pathsWeight[pos] + weight;
								fromVertex[dest] = pos;
							}
						}
					}
				}
			}
			
		}
	}

	int** minPaths = new int* [2];
	minPaths[0] = pathsWeight;
	minPaths[1] = fromVertex;

	return minPaths;
}

int** Graphs::BellmanFord::getMinPaths(ListGraph* graph, size_t beginningV)
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

	for (size_t i = 0; i < vertexNum; i++)
	{
		pathsWeight[i] = INT_MAX;
		fromVertex[i] = -1;
	}

	pathsWeight[beginningV] = 0;

	for (size_t i = 0; i < vertexNum; i++)
	{
		for (size_t pos = 0; pos < vertexNum; pos++)
		{
			GraphListNode* node = neighbourhoodList[pos];
			if (pathsWeight[pos] != INT_MAX)
				while (node)
				{			
					size_t destination = node->edge->destination;
					size_t weight = node->edge->weight;
					if (pathsWeight[destination] > pathsWeight[pos] + weight)
					{
						pathsWeight[destination] = pathsWeight[pos] + weight;
						fromVertex[destination] = pos;
					}
					node = node->nextNode;
				}
		}
	}

	int** minPaths = new int* [2];
	minPaths[0] = pathsWeight;
	minPaths[1] = fromVertex;

	return minPaths;
}

void Graphs::BellmanFord::printMinPaths(std::ostream& out, int** paths, size_t vertexNum)
{
	if (paths == nullptr)
	{
		out << "No paths available\n";
		return;
	}

	for (size_t i = 0; i < vertexNum; i++)
	{
		out << i << " ";
	}
	out << "\n";
	for (size_t i = 0; i < vertexNum; i++)
	{
		if (paths[0][i] != INT_MAX)
		{
			out << paths[0][i] << " ";
		}
		else
			out << "- ";
	}

	out << "\n";
}

void Graphs::BellmanFord::printMinPath(std::ostream& out, int** paths, size_t vertexNum, size_t destination)
{
	if (destination > vertexNum)
	{
		throw* invalid_vertex;
	}
	if (paths == nullptr || paths[0][destination] == INT_MAX)
	{
		out << "No paths available\n";
		return;
	}

	size_t currVertex = destination;
	out << "(W)" << paths[0][currVertex] << ": ";
	for (size_t i = 0; i < vertexNum; i++)
	{
		if (paths[0][currVertex] == 0)
			break;

		out << currVertex << " <- ";
		currVertex = paths[1][currVertex];
	}
	out << currVertex << "\n";
}

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


		for (size_t i = 0; i < edgeNum; i++)
		{
			if (incidenceMatrix[pos][i] > 0)
			{
				size_t weight = incidenceMatrix[pos][i];
				for (size_t dest = 0; dest < vertexNum; dest++)
				{
					if (incidenceMatrix[dest][i] < 0)
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

		int shortestPath = INT_MAX;
		size_t currShortest = vertexNum;
		for (size_t i = 0; i < vertexNum; i++)
		{
			//if (pathsWeight[i] != INT_MAX)
			//{
			//	std::cout << pathsWeight[i] << " ";
			//}
			//else
			//	std::cout << "- ";

			if (visitedVertices[i] == false)
			{
				if (pathsWeight[i] < shortestPath)
				{
					shortestPath = pathsWeight[i];
					currShortest = i;
				}
			}
		}
		//std::cout << std::endl;
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
			//if (pathsWeight[i] != INT_MAX)
			//{
			//	std::cout << pathsWeight[i] << " ";
			//}
			//else
			//	std::cout << "- ";

			if (visitedVertices[i] == false)
			{

				if (pathsWeight[i] < shortestPath)
				{
					shortestPath = pathsWeight[i];
					currShortest = i;
				}
			}			
		}
		//std::cout << std::endl;
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

void Graphs::Dijkstra::printMinPath(std::ostream& out, int** paths, size_t vertexNum, size_t destination)
{
	if (destination >= vertexNum)
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


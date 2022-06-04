#include "../../Headers/algorithms/Prim.h"

Graphs::Prim::Prim()
{
}

Graphs::Prim::~Prim()
{
}

Graphs::Edge** Graphs::Prim::getMST(MatrixGraph* graph)
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

	EdgeHeapMin* heap = new EdgeHeapMin(2 * edgeNum);

	Edge** mst = new Edge * [vertexNum - 1];

	bool* visitedVertices = new bool[vertexNum];
	for (size_t i = 0; i < vertexNum; i++)
	{
		visitedVertices[i] = false;
	}

	for (size_t i = 0; i < edgeNum; i++)
	{
		if (incidenceMatrix[0][i] != 0)
		{
			size_t destination = SIZE_MAX;
			size_t weight = incidenceMatrix[0][i];

			for (size_t j = 1; j < vertexNum; j++)
			{
				if (incidenceMatrix[j][i] != 0)
				{
					destination = j;
				}
			}
			if (destination == SIZE_MAX)
			{
				destination = 0;
			}

			Edge* newEdge = new Graphs::Edge(weight, 0, destination);
			//std::cout << newEdge->destination << " " << newEdge->weight << std::endl;
			heap->add(newEdge);
		}
	}


	visitedVertices[0] = true;

	size_t pos = 0;
	for (size_t k = 0; k < 2 * edgeNum; k++)
	{
		if (!visitedEveryVertex(visitedVertices, vertexNum))
		{
			Edge* edge = heap->extractRoot();


			if (visitedVertices[edge->destination] == false)
			{
				for (size_t i = 0; i < edgeNum; i++)
				{
					if (incidenceMatrix[edge->destination][i] != 0)
					{
						size_t destination2 = SIZE_MAX;
						size_t weight = incidenceMatrix[edge->destination][i];

						for (size_t j = 0; j < vertexNum; j++)
						{
							if (incidenceMatrix[j][i] != 0 && j != edge->destination)
							{
								destination2 = j;
							}
						}
						if (destination2 == SIZE_MAX)
						{
							destination2 = edge->destination;
						}

						Edge* newEdge = new Graphs::Edge(weight, edge->destination, destination2);
						heap->add(newEdge);

						//std::cout << newEdge->source << newEdge->destination << " " << newEdge->weight << std::endl;
					}
				}

				visitedVertices[edge->destination] = true;

				mst[pos] = edge;
				pos++;
			}
		}
		else
			break;
	}

	heap->clear(true);
	delete heap;
	return mst;
}

Graphs::Edge** Graphs::Prim::getMST(ListGraph* graph)
{
	size_t edgeNum = graph->getEdgeNumber();
	size_t vertexNum = graph->getVertexNumber();
	GraphListNode** neighbourhoodList = graph->getNieghbourhoodList();
	if (neighbourhoodList == nullptr || vertexNum == 0)
	{
		throw* structure_null;
	}
	if (vertexNum == 1 || edgeNum == 0)
	{
		return nullptr;
	}

	EdgeHeapMin* heap = new EdgeHeapMin(2*edgeNum);

	Edge** mst = new Edge * [vertexNum - 1];

	bool* visitedVertices = new bool[vertexNum];
	for (size_t i = 0; i < vertexNum; i++)
	{
		visitedVertices[i] = false;
	}

	GraphListNode* node = neighbourhoodList[0];
	while (node)
	{
		heap->add(node->edge);
		node = node->nextNode;
	}
	visitedVertices[0] = true;

	size_t j = 0;
	for (size_t i = 0; i < 2*edgeNum; i++)
	{
		if (!visitedEveryVertex(visitedVertices, vertexNum))
		{
			Edge* edge = heap->extractRoot();
			/*std::cout << edge->value << ". ";
			for (size_t i = 0; i < vertexNum; i++)
			{
				std::cout << connectedVertices[i] << " ";
			}
			std::cout << std::endl;*/

			if (visitedVertices[edge->source] == false)
			{
				GraphListNode* node = neighbourhoodList[edge->source];
				while (node)
				{
					heap->add(node->edge);
					node = node->nextNode;
				}

				visitedVertices[edge->source] = true;

				mst[j] = edge;
				j++;
			}
			else if (visitedVertices[edge->destination] == false)
			{
				GraphListNode* node = neighbourhoodList[edge->destination];
				while (node)
				{
					heap->add(node->edge);
					node = node->nextNode;
				}

				visitedVertices[edge->destination] = true;


				mst[j] = edge;
				j++;
			}
		}
		else
			break;
	}

	delete heap;
	return mst;
}

void Graphs::Prim::printMST(std::ostream& out, Graphs::Edge** mst, size_t vertexNum)
{
	if (vertexNum > 0 && mst != nullptr)
	{
		for (size_t i = 0; i < vertexNum - 1; i++)
		{
			out << i << ". ";
			Edge* edge = mst[i];
			if (edge == nullptr)
			{
				out << "MST is not full\n";
				return;
			}
			out << "(F: " << edge->source
				<< " To: " << edge->destination
				<< " V: " << edge->weight
				<< ")\n";
		}

		return;
	}
	out << "Data structure is empty" << std::endl;


}

bool Graphs::Prim::visitedEveryVertex(bool* visitedArr, size_t vertexNum)
{
	for (size_t i = 0; i < vertexNum; i++)
	{
		if (visitedArr[i] != true)
			return false;
	}
	return true;
}

#include "../../Headers/algorithms/Prim.h"

Graphs::Prim::Prim()
{
}

Graphs::Prim::~Prim()
{
}

Graphs::Edge** Graphs::Prim::getMST(MatrixGraph* graph)
{
	return nullptr;
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
				<< " V: " << edge->value
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

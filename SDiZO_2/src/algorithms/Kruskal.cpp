#include "../../Headers/algorithms/Kruskal.h"

Graphs::Kruskal::Kruskal()
{
}

Graphs::Kruskal::~Kruskal()
{
}

Graphs::Edge** Graphs::Kruskal::getMST(MatrixGraph* graph)
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

	EdgeHeapMin* heap = new EdgeHeapMin(edgeNum);

	Edge** mst = new Edge * [vertexNum - 1];

	size_t* connectedVertices = new size_t[vertexNum];
	for (size_t i = 0; i < vertexNum; i++)
	{
		connectedVertices[i] = i;
	}

	for (size_t i = 0; i < edgeNum; i++)
	{
		size_t weight = 0;
		size_t source;
		size_t destination;

		for (size_t j = 0; j < vertexNum; j++)
		{
			if (incidenceMatrix[j][i] != 0)
			{
				if (weight == 0)
				{
					weight = incidenceMatrix[j][i];
					source = j;
				}
				else
					destination = j;

			}
		}

		Edge* newEdge = new Graphs::Edge(weight, source, destination);
		heap->add(newEdge);
	}

	size_t j = 0;
	for (size_t i = 0; i < 2 * edgeNum; i++)
	{
		if (!visitedEveryVertex(connectedVertices, vertexNum))
		{
			Edge* edge = heap->extractRoot();
			/*std::cout << edge->value << ". ";
			for (size_t i = 0; i < vertexNum; i++)
			{
				std::cout << connectedVertices[i] << " ";
			}
			std::cout << std::endl;*/

			if (connectedVertices[edge->source] != connectedVertices[edge->destination])
			{
				size_t lowerVal;
				size_t higherVal;
				if (connectedVertices[edge->source] > connectedVertices[edge->destination])
				{
					higherVal = connectedVertices[edge->source];
					lowerVal = connectedVertices[edge->destination];
				}
				else
				{
					lowerVal = connectedVertices[edge->source];
					higherVal = connectedVertices[edge->destination];
				}

				for (size_t i = 0; i < vertexNum; i++)
				{
					if (connectedVertices[i] == higherVal)
						connectedVertices[i] = lowerVal;
				}

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

Graphs::Edge** Graphs::Kruskal::getMST(ListGraph* graph)
{
	size_t edgeNum = graph->getEdgeNumber();
	size_t vertexNum = graph->getVertexNumber();
	GraphListNode** neighbourhoodList = graph->getNieghbourhoodList();
	if (neighbourhoodList == nullptr || vertexNum == 0)
	{
		throw* structure_null;
	}
	if (vertexNum == 1 || edgeNum==0)
	{
		return nullptr;
	}

	EdgeHeapMin* heap = new EdgeHeapMin(edgeNum*2);

	Edge** mst = new Edge * [vertexNum - 1];

	size_t* connectedVertices = new size_t[vertexNum];
	for (size_t i = 0; i < vertexNum; i++)
	{
		connectedVertices[i] = i;
	}

	for (size_t i = 0; i < vertexNum; i++)
	{
		GraphListNode* node = neighbourhoodList[i];
		while (node)
		{
			heap->add(node->edge);
			node = node->nextNode;
		}
	}
	//heap->print(std::cout);
	size_t j = 0;
	for (size_t i = 0; i < 2*edgeNum; i++)
	{
		if (!visitedEveryVertex(connectedVertices, vertexNum))
		{
			Edge* edge = heap->extractRoot();
			/*std::cout << edge->value << ". ";
			for (size_t i = 0; i < vertexNum; i++)
			{
				std::cout << connectedVertices[i] << " ";
			}
			std::cout << std::endl;*/

			if (connectedVertices[edge->source] != connectedVertices[edge->destination])
			{
				size_t lowerVal;
				size_t higherVal;
				if (connectedVertices[edge->source] > connectedVertices[edge->destination])
				{
					higherVal = connectedVertices[edge->source];
					lowerVal = connectedVertices[edge->destination];
				}
				else
				{
					lowerVal = connectedVertices[edge->source];
					higherVal = connectedVertices[edge->destination];
				}

				for (size_t i = 0; i < vertexNum; i++)
				{
					if (connectedVertices[i] == higherVal)
						connectedVertices[i] = lowerVal;
				}

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

void Graphs::Kruskal::printMST(std::ostream& out, Edge** mst, size_t vertexNum)
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

bool Graphs::Kruskal::visitedEveryVertex(size_t* visitedArr, size_t vertexNum)
{
	size_t initValue = visitedArr[0];
	for (size_t i = 0; i < vertexNum; i++)
	{
		if (visitedArr[i] != initValue)
			return false;
	}
	return true;
}

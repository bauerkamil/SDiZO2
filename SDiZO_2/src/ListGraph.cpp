#include "../Headers/ListGraph.h"

Graphs::ListGraph::ListGraph(bool isDirected)
{
	this->incidenceMatrix = nullptr;
	this->edgeNum = 0;
	this->vertexNum = 0;
	this->isDirected = isDirected;
}

Graphs::ListGraph::~ListGraph()
{
	clear();
}

void Graphs::ListGraph::print(std::ostream& out)
{
	if (this->vertexNum > 0 && this->incidenceMatrix != nullptr)
	{
		for (size_t i = 0; i < vertexNum; i++)
		{
			out << i << ". ";
			GraphListNode* node = this->incidenceMatrix[i];
			out << "[";
			while (node)
			{
				if (node->nextNode)
					out << "(F: " << node->edge->source
					<< " To: " << node->edge->destination
					<< " V: " << node->edge->weight
					<< ") <-> ";
				else
					out << "(F: " << node->edge->source
					<< " To: " << node->edge->destination
					<< " V: " << node->edge->weight
					<< ")";
				node = node->nextNode;
			}
			out << "]" << std::endl;
		}

		return;
	}
	out << "Data structure is empty" << std::endl;
}

void Graphs::ListGraph::setNieghbourhoodList(size_t** edgeList, size_t vertexNum, size_t edgeNum, bool isDirected)
{
	this->vertexNum = vertexNum;
	this->edgeNum = edgeNum;
	this->isDirected = isDirected;

	this->incidenceMatrix = new Graphs::GraphListNode*[vertexNum];

	for (size_t i = 0; i < vertexNum; i++)
	{
		this->incidenceMatrix[i] = nullptr;
	}

	if (!isDirected)
	{
		//size_t addedEdgeNonDirected = 0;

		for (size_t i = 0; i < edgeNum; i++)
		{
			Graphs::Edge* newEdge = new Graphs::Edge(edgeList[i][2], edgeList[i][0], edgeList[i][1]);
			addEnd(edgeList[i][0], newEdge);

			addEnd(edgeList[i][1], newEdge);
			//addedEdgeNonDirected++;

		}

		//this->edgeNum += addedEdgeNonDirected;
	}
	else
	{
		for (size_t i = 0; i < edgeNum; i++)
		{
			Graphs::Edge* newEdge = new Graphs::Edge(edgeList[i][2], edgeList[i][0], edgeList[i][1]);
			addEnd(edgeList[i][0], newEdge);
		}

	}

}

Graphs::GraphListNode** Graphs::ListGraph::getNieghbourhoodList()
{
	return incidenceMatrix;
}



size_t Graphs::ListGraph::getVertexNumber()
{
	return vertexNum;
}

size_t Graphs::ListGraph::getEdgeNumber()
{
	return edgeNum;
}

bool Graphs::ListGraph::getIsDirected()
{
	return isDirected;
}

void Graphs::ListGraph::clear()
{
	for (size_t i = 0; i < vertexNum; i++)
	{
		//delete this->neighbourhoodList[i];
	}
	delete[] this->incidenceMatrix;
	this->incidenceMatrix = nullptr;
	this->edgeNum = 0;
	this->vertexNum = 0;
}

void Graphs::ListGraph::addEnd(size_t vertex, Edge* edge)
{
	if (vertex >= vertexNum)
	{
		throw* invalid_vertex;
	}
	if (incidenceMatrix[vertex] != nullptr)
	{
		GraphListNode* next = incidenceMatrix[vertex];
		while (next->nextNode != nullptr)
		{
			next = next->nextNode;
		}
		GraphListNode* newNode = new GraphListNode(edge, next, nullptr);
		next->nextNode = newNode;

	}
	else
	{
		incidenceMatrix[vertex] = new GraphListNode(edge, nullptr, nullptr);
	}
}

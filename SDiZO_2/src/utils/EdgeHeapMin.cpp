#include "../../Headers/utils/EdgeHeapMin.h"
#include <math.h>


Graphs::EdgeHeapMin::EdgeHeapMin(size_t totalSize)
{
	this->size = 0;
	this->totalSize = totalSize;
	this->root = new Edge * [totalSize];
}

Graphs::EdgeHeapMin::~EdgeHeapMin()
{
	clear();
}

void Graphs::EdgeHeapMin::add(Edge* element)
{
	if (size >= totalSize)
	{
		throw* this->not_enough_space;
	}

	this->root[this->size] = element;

	this->size++;

	buildHeap();
}

void Graphs::EdgeHeapMin::addAll(size_t& numOfElements, Edge** staticArr)
{
	if (size + numOfElements >= totalSize)
	{
		throw* this->not_enough_space;
	}

	for (size_t i = 0; i < numOfElements; i++)
	{
		this->root[size + i] = staticArr[i];
	}

	this->size = size + numOfElements;

	buildHeap();
}

Graphs::Edge* Graphs::EdgeHeapMin::extractRoot()
{
	// Check if any data exists
	if (this->root == nullptr)
	{
		throw* this->head_null;
	}

	Edge* root = this->root[0];
	this->root[0] = this->root[size - 1];
	this->root[size - 1] = nullptr;

	this->size--;

	//no need to go up
	heapifyMin(0);

	return root;
}

void Graphs::EdgeHeapMin::heapifyMin(size_t index)
{
	size_t minimum;
	size_t left = getLeftChild(index);
	size_t right = getRightChild(index);

	//determine which is the lowest
	if (left<this->size && root[left]->weight < root[index]->weight)
		minimum = left;
	else
		minimum = index;
	if (right<this->size && root[right]->weight < root[minimum]->weight)
		minimum = right;

	if (minimum != index)
	{
		swap(index, minimum);
		heapifyMin(minimum);
	}
}

void Graphs::EdgeHeapMin::buildHeap()
{
	if (this->size > 1)
		for (size_t i = getParent(this->size - 1); i >= 0; i--)
		{
			heapifyMin(i);
			if (i == 0)
			{
				break;
			}
		}
}

void Graphs::EdgeHeapMin::swap(size_t index1, size_t index2)
{
	Edge* value = this->root[index1];
	this->root[index1] = this->root[index2];
	this->root[index2] = value;
}

void Graphs::EdgeHeapMin::clear()
{
	if (this->root != nullptr)
	{
		delete[] this->root;
	}
	this->root = nullptr;
	this->size = 0;
}


void Graphs::EdgeHeapMin::print(std::ostream& out)
{
	if (this->size > 0 && this->root != nullptr)
	{
		size_t height;
		if (this->size == 1)
			height = 1;
		else
			height = ceil(log2(this->size + 1));

		size_t index = 0;
		for (size_t currLevel = 1; currLevel < height; currLevel++)
		{
			out << currLevel << ".";
			size_t numOfLevelElements = pow(2, currLevel - 1);

			size_t tmp = height - currLevel;
			size_t numOfSpace = pow(2, tmp) - 1;
			size_t numOfMinus = pow(2, tmp - 1) - 1;

			out << std::string(numOfMinus, ' ');
			for (size_t i = 0; i < numOfLevelElements; i++)
			{
				out << "/" << std::string(numOfMinus, '-') << this->root[index]->weight;
				out << std::string(numOfMinus, '-') << "\\" << std::string(numOfSpace, ' ');
				index++;
			}
			out << std::endl;
		}
		out << height << ".";
		while (index < this->size)
		{
			out << this->root[index]->weight << " ";
			index++;
		}
		out << std::endl;
	}
	return;

	out << "Data structure is empty" << std::endl;
}

size_t Graphs::EdgeHeapMin::getLeftChild(size_t parentIndex)
{
	return (2 * parentIndex + 1);
}

size_t Graphs::EdgeHeapMin::getRightChild(size_t parentIndex)
{
	return (2 * parentIndex + 2);
}

size_t Graphs::EdgeHeapMin::getParent(size_t childIndex)
{
	return floor(childIndex / 2);
}

size_t Graphs::EdgeHeapMin::getSize()
{
	return this->size;
}

size_t Graphs::EdgeHeapMin::getEdgeNum()
{
	return this->totalSize;
}

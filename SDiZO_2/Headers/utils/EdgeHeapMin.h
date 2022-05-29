#pragma once
#include <iostream>
#include <stdexcept>
#include "../Edge.h"

namespace Graphs
{
	//non-dynamic Heap implementation
	class EdgeHeapMin
	{
	public:
		// invalid index exception
		const std::invalid_argument* invalid_index = new std::invalid_argument("Invalid index");
		// structure pointer is null
		const std::out_of_range* head_null = new std::out_of_range("Structure pointer is null");
		// structure pointer is null
		const std::out_of_range* not_enough_space = new std::out_of_range("There is not enough space to add new element");
		// class constructor
		EdgeHeapMin(size_t edgeNum);
		// class destructor
		~EdgeHeapMin();
		//adds to the end and heapifies
		virtual void add(Edge* element);
		// adds elements from static Heap
		virtual void addAll(size_t& numOfElements, Edge** staticArr);
		// removes first obj of the Heap and returns it
		virtual Edge* extractRoot();
		//clears Heap
		virtual void clear();
		// returns the quantity of elements in Heap
		virtual size_t getSize();
		// returns the size of Heap
		virtual size_t getEdgeNum();
		// prints the Heap in console
		virtual void print(std::ostream& out);

	private:
		// pointer to beggining of array containing heap
		Edge** root;
		//quantity of elements inside Heap
		size_t size;
		//the following is for better time results
		//size of array
		size_t totalSize;
		//the following is for better time results
		//position of root
		size_t startpoint = 0;
		//get smaller element down
		void heapifyMin(size_t index);
		//heapify array bottom-up
		void buildHeap();
		//swaps parent and child
		void swap(size_t parentIndex, size_t childIndex);
		//returns index of left child
		//might return index that isnt in heap
		size_t getLeftChild(size_t parentIndex);
		//returns index of right child
		//might return index that isnt in heap
		size_t getRightChild(size_t parentIndex);
		//returns index of parent
		size_t getParent(size_t childIndex);
	};
}


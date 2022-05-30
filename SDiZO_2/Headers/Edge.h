#pragma once
#include <iostream>

namespace Graphs
{
	struct Edge
	{
		size_t weight;
		size_t source;
		size_t destination;
		Edge(size_t weight, size_t source, size_t destination)
			: weight(weight), source(source), destination(destination) {}

		//friend std::ostream& operator<< (std::ostream& output, const Edge& E) {
		//	output << "F: " << E.source << " To: " << E.destination << " V: " << E.value;
		//	return output;
		//}

	};

}

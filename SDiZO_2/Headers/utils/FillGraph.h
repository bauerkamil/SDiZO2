#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <bits.h>
#include <string>
#include <sstream>
#include <stdexcept>

class FillGraph
{
public:
	FillGraph();
	~FillGraph();
	size_t** getEdgeList();
	size_t getEdgeNum();
	size_t getVertexNum();
	void fillFromFile(std::string filename);
	void fillRandom(size_t vertexNum, size_t densityPercent, bool isDirected);

	const std::exception* fileEmpty = new std::exception("File empty");
	const std::exception* fileCorrupted = new std::exception("File corrupted");
	const std::exception* file404 = new std::exception("File not found");
	const std::invalid_argument* invalid_density = new std::invalid_argument("Invalid density");
private:
	size_t** edgeList;
	size_t edgeNum;
	size_t vertexNum;

	void clear();
};

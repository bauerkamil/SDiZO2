#pragma once
#include<iostream>
#include <fstream>
#include<cstdlib>
#include<ctime>
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

	const std::exception* fileEmpty = new std::exception("File empty");
	const std::exception* fileCorrupted = new std::exception("File corrupted");
	const std::exception* file404 = new std::exception("File not found");
private:
	size_t** edgeList;
	size_t edgeNum;
	size_t vertexNum;

	void clear();
};

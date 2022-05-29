#pragma once
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "../MatrixGraph.h"
#include "../algorithms/Kruskal.h"
#include "../algorithms/Prim.h"
#include "../utils/FillGraph.h"

class MatrixTest
{
public:
	MatrixTest(FillGraph* fileGraph, Graphs::Kruskal* kruskalAlg, Graphs::Prim* primAlg);
	~MatrixTest();
	void run();
private:
	Graphs::MatrixGraph* testGraph = new Graphs::MatrixGraph(false);
	Graphs::Kruskal* kruskalAlg;
	Graphs::Prim* primAlg;
	FillGraph* fillGraph;
	const int FILL_WIDTH = 100;
	bool isFinished = false;

	void printOptions();
	int getOption();
	std::string getFileName();
	void chooseOption(int option);
};

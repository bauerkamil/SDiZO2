#pragma once
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "../MatrixGraph.h"
#include "../ListGraph.h"
#include "../Edge.h"
#include "../algorithms/Kruskal.h"
#include "../algorithms/Prim.h"
#include "../algorithms/Dijkstra.h"
#include "../algorithms/BellmanFord.h"
#include "../utils/FillGraph.h"
#include "../utils/Timer.h"

class AutoTest
{
public:
	AutoTest(FillGraph* fillGraph, Graphs::Kruskal* kruskalAlg, Graphs::Prim* primAlg, Graphs::Dijkstra* dijkstraAlg, Graphs::BellmanFord* bfAlg);
	~AutoTest();
private:
	Graphs::ListGraph* listGraph = new Graphs::ListGraph(false);
	Graphs::MatrixGraph* matrixGraph = new Graphs::MatrixGraph(false);
	Timer* timer = new Timer();
	Graphs::Kruskal* kruskalAlg;
	Graphs::Prim* primAlg;
	Graphs::Dijkstra* dijkstraAlg;
	Graphs::BellmanFord* bfAlg;
	FillGraph* fillGraph;

	std::ofstream resultFile;
	std::string fileName = "output/results.csv";

	size_t iterations;
	size_t* densities;
	size_t* vertexNums;

	void saveToFile(char graph, char alg, size_t density, size_t vertexNum, long time);
	void runTests();
};
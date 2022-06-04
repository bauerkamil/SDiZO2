#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <iomanip>
#include "MatrixTest.h"
#include "ListTest.h"
#include "AutoTest.h"
#include "../algorithms/Kruskal.h"
#include "../algorithms/Prim.h"
#include "../algorithms/Dijkstra.h"
#include "../algorithms/BellmanFord.h"
#include "../utils/FillGraph.h"

class Menu
{
public:
	Menu();
	virtual ~Menu();

private:
	void printMenu();
	int getChoice();
	void chooseOption(int choice);
	const int FILL_WIDTH = 100;

	MatrixTest* matrixTest;
	ListTest* listTest;
	Graphs::Kruskal* kruskalAlg;
	Graphs::Prim* primAlg;
	Graphs::Dijkstra* dijkstraAlg;
	Graphs::BellmanFord* bfAlg;
	FillGraph* fillGraph;
	bool isFinished;
};

#endif

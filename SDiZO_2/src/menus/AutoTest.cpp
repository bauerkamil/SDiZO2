#include "../../Headers/menus/AutoTest.h"

AutoTest::AutoTest(FillGraph* fillGraph, Graphs::Kruskal* kruskalAlg, Graphs::Prim* primAlg, Graphs::Dijkstra* dijkstraAlg, Graphs::BellmanFord* bfAlg)
{
	this->fillGraph = fillGraph;
	this->kruskalAlg = kruskalAlg;
	this->primAlg = primAlg;
	this->dijkstraAlg = dijkstraAlg;
	this->bfAlg = bfAlg;

	iterations = 50;

	size_t d[4] = {25, 50, 75, 99};
	densities = d;
	size_t v[8] = {20, 30, 40, 50, 60, 70, 80, 90};
	vertexNums = v;

	runTests();
}

AutoTest::~AutoTest()
{
	delete this->matrixGraph;
	delete this->listGraph;
	delete this->timer;

	//			std::cout << 1;
	//delete[] this->densities;
	//delete[] this->vertexNums;
}

void AutoTest::saveToFile(char graph, char alg, size_t density, size_t vertexNum, long time)
{
	this->resultFile.open(fileName, std::ios::app);
	this->resultFile << graph << "," << alg << "," << density << "," << vertexNum << "," << time << std::endl;
	this->resultFile.close();
}

void AutoTest::runTests()
{
	while (iterations > 0)
	{
		for (size_t i = 0; i < 4; i++)
		{
			size_t density = densities[i];

			for (size_t j = 0; j < 8; j++)
			{
				size_t vertexNum = vertexNums[j];

				fillGraph->fillRandom(vertexNum, density, false);
				matrixGraph->setIncidenceMatrix(fillGraph->getEdgeList(), vertexNum, fillGraph->getEdgeNum(), false);

				timer->start();
				Graphs::Edge** mst = primAlg->getMST(matrixGraph);
				timer->stop();
				saveToFile('m', 'p', density, vertexNum, timer->result());
				for (size_t i = 0; i < vertexNum - 1; i++)
				{
					delete mst[i];
				}
				delete[] mst;

				timer->start();
				Graphs::Edge** mst1 = kruskalAlg->getMST(matrixGraph);
				timer->stop();
				saveToFile('m', 'k', density, vertexNum, timer->result());
				for (size_t i = 0; i < vertexNum - 1; i++)
				{
					delete mst1[i];
				}
				delete[] mst1;

				listGraph->setNieghbourhoodList(fillGraph->getEdgeList(), vertexNum, fillGraph->getEdgeNum(), false);

				timer->start();
				Graphs::Edge** mst2 = primAlg->getMST(listGraph);
				timer->stop();
				saveToFile('l', 'p', density, vertexNum, timer->result());
				delete[] mst2;

				timer->start();
				Graphs::Edge** mst3 = kruskalAlg->getMST(listGraph);
				timer->stop();
				saveToFile('l', 'k', density, vertexNum, timer->result());
				delete[] mst3;


				fillGraph->fillRandom(vertexNum, density, true);
				matrixGraph->setIncidenceMatrix(fillGraph->getEdgeList(), fillGraph->getEdgeNum(), vertexNum, true);

				timer->start();
				int** sh = dijkstraAlg->getMinPaths(matrixGraph, 0);
				timer->stop();
				saveToFile('m', 'd', density, vertexNum, timer->result());
				delete[] sh[0];
				delete[] sh[1];
				delete[] sh;

				timer->start();
				int** sh1 = bfAlg->getMinPaths(matrixGraph, 0);
				timer->stop();
				saveToFile('m', 'b', density, vertexNum, timer->result());
				delete[] sh1[0];
				delete[] sh1[1];
				delete[] sh1;

				listGraph->setNieghbourhoodList(fillGraph->getEdgeList(), vertexNum, fillGraph->getEdgeNum(), true);

				timer->start();
				int** sh2 = dijkstraAlg->getMinPaths(listGraph, 0);
				timer->stop();
				saveToFile('l', 'd', density, vertexNum, timer->result());
				delete[] sh2[0];
				delete[] sh2[1];
				delete[] sh2;

				timer->start();
				int** sh3 = bfAlg->getMinPaths(listGraph, 0);
				timer->stop();
				saveToFile('l', 'b', density, vertexNum, timer->result());
				delete[] sh3[0];
				delete[] sh3[1];
				delete[] sh3;
			}

		}


		this->iterations--;
	}
}

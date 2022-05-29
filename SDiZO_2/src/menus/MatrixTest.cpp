#include "../../Headers/menus/MatrixTest.h"

MatrixTest::MatrixTest(FillGraph* fillGraph, Graphs::Kruskal* kruskalAlg, Graphs::Prim* primAlg)
{
	this->fillGraph = fillGraph;
	this->kruskalAlg = kruskalAlg;
	this->primAlg = primAlg;
}

MatrixTest::~MatrixTest()
{
	delete this->testGraph;
}

void MatrixTest::run()
{
	this->isFinished = false;

	std::cout << std::setfill('=') << std::setw(FILL_WIDTH) << "\n"
		<< std::setfill(' ') << std::setw(40) << "Matrix Graph" << std::endl;

	while (!isFinished)
	{
		printOptions();
		chooseOption(getOption());
	}
}

void MatrixTest::printOptions()
{
	std::cout << std::setfill('=') << std::setw(FILL_WIDTH) << "\n"
		<< "Please choose one of following options : \n"
		<< "1. Print graph\n"
		<< "2. Fill from file\n"
		<< "3. Generate random graph\n"
		<< "4. Get MST - Prim algorithm\n"
		<< "5. Get MST - Kruskal algorithm\n"
		<< "0. Exit" << std::endl;
}

int MatrixTest::getOption()
{
	int option;
	std::cin >> option;

	return option;
}

std::string MatrixTest::getFileName()
{
	std::string fileName;
	std::cout << "Enter filename (with path from working directory): " << std::endl;
	std::cin >> fileName;
	return fileName;
}

void MatrixTest::chooseOption(int choice)
{
	switch (choice)
	{
	case 1:
	{
		this->testGraph->print(std::cout);
	}
	break;
	case 2:
	{

		std::string filename = getFileName();
		try
		{
			fillGraph->fillFromFile(filename);

			size_t** edgeList = this->fillGraph->getEdgeList();
			size_t edgeNum = this->fillGraph->getEdgeNum();
			size_t vertexNum = this->fillGraph->getVertexNum();

			this->testGraph->setIncidenceMatrix(edgeList, vertexNum, edgeNum);

			this->testGraph->print(std::cout);
		}
		catch (std::exception e)
		{
			std::cout << e.what();
		}
	}
	break;
	case 4:
	{
		if (testGraph->getIsDirected() == true)
		{
			std::cout << "Changing to not directed" << std::endl;
		}

		try
		{
			Graphs::Edge** mst = this->primAlg->getMST(testGraph);
			primAlg->printMST(std::cout, mst, testGraph->getVertexNumber());
		}
		catch (std::exception e)
		{
			std::cout << e.what();
		}
	}
	break;
	case 5:
	{
		if (testGraph->getIsDirected() == true)
		{
			std::cout << "Changing to not directed" << std::endl;
		}

		try
		{
			Graphs::Edge** mst = this->kruskalAlg->getMST(testGraph);
			kruskalAlg->printMST(std::cout, mst, testGraph->getVertexNumber());
		}
		catch (std::exception e)
		{
			std::cout << e.what();
		}
	}
	break;
	case 0:
	{
		isFinished = true;
	}
	break;
	default:
		std::cout << "\nPlease try again" << std::endl;
	}
}
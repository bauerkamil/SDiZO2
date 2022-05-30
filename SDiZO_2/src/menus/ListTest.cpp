#include "../../Headers/menus/ListTest.h"

ListTest::ListTest(FillGraph* fillGraph, Graphs::Kruskal* kruskalAlg, Graphs::Prim* primAlg, Graphs::Dijkstra* dijkstraAlg, Graphs::BellmanFord* bfAlg)
{
	this->fillGraph = fillGraph;
	this->kruskalAlg = kruskalAlg;
	this->primAlg = primAlg;
	this->dijkstraAlg = dijkstraAlg;
	this->bfAlg = bfAlg;
}

ListTest::~ListTest()
{
	delete this->testGraph;
}

void ListTest::run()
{
	this->isFinished = false;

	std::cout << std::setfill('=') << std::setw(FILL_WIDTH) << "\n"
		<< std::setfill(' ') << std::setw(40) << "Neighbourhood List Graph" << std::endl;

	while (!isFinished)
	{
		printOptions();
		chooseOption(getOption());
	}
}

void ListTest::printOptions()
{
	std::cout << std::setfill('=') << std::setw(FILL_WIDTH) << "\n"
		<< "Please choose one of following options : \n"
		<< "1. Print graph\n"
		<< "2. Fill from file\n"
		<< "3. Generate random graph\n"
		<< "4. Get MST - Prim's algorithm\n"
		<< "5. Get MST - Kruskal's algorithm\n"
		<< "6. Get shortest path - Dijkstra's algorithm\n"
		<< "7. Get shortest path - Bellman-Ford's algorithm\n"
		<< "0. Exit" << std::endl;
}

int ListTest::getOption()
{
	int option;
	std::cin >> option;

	return option;
}

std::string ListTest::getFileName()
{
	std::string fileName;
	std::cout << "Enter filename (with path from working directory): " << std::endl;
	std::cin >> fileName;
	return fileName;
}

void ListTest::chooseOption(int choice)
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
			bool isDirected = getDirectory();

			size_t** edgeList = this->fillGraph->getEdgeList();
			size_t edgeNum = this->fillGraph->getEdgeNum();
			size_t vertexNum = this->fillGraph->getVertexNum();

			this->testGraph->setNieghbourhoodList(edgeList, vertexNum, edgeNum, isDirected);

			this->testGraph->print(std::cout);
		}
		catch (std::exception e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	break;
	case 3:
	{
		try
		{
			bool isDirected = getDirectory();
			fillGraph->fillRandom(getVertexNum(), getDensity(), isDirected);

			size_t** edgeList = this->fillGraph->getEdgeList();
			size_t edgeNum = this->fillGraph->getEdgeNum();
			size_t vertexNum = this->fillGraph->getVertexNum();

			this->testGraph->setNieghbourhoodList(edgeList, vertexNum, edgeNum, isDirected);

			this->testGraph->print(std::cout);
		}
		catch (std::exception e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	break;
	case 4:
	{
		if (testGraph->getIsDirected() == true)
		{
			std::cout << "The graph ought not to be directed\n" << std::endl;
		}
		else
		{
			try
			{
				Graphs::Edge** mst = this->primAlg->getMST(testGraph);
				primAlg->printMST(std::cout, mst, testGraph->getVertexNumber());
			}
			catch (std::exception e)
			{
				std::cout << e.what() << std::endl;
			}

		}

	}
	break;
	case 5:
	{
		if (testGraph->getIsDirected() == true)
		{
			std::cout << "The graph ought not to be directed\n" << std::endl;
		}
		else
		{
			try
			{
				Graphs::Edge** mst = this->kruskalAlg->getMST(testGraph);
				kruskalAlg->printMST(std::cout, mst, testGraph->getVertexNumber());
			}
			catch (std::exception e)
			{
				std::cout << e.what() << std::endl;
			}

		}
	}
	break;
	case 6:
	{
		if (testGraph->getIsDirected() == false)
		{
			std::cout << "The graph ought to be directed\n" << std::endl;
		}
		else
		{
			try
			{
				size_t source = getVertex();
				int** paths = dijkstraAlg->getMinPaths(testGraph, source);
				dijkstraAlg->printMinPaths(std::cout, paths, testGraph->getVertexNumber());
				size_t destination = getVertex();
				dijkstraAlg->printMinPath(std::cout, paths, testGraph->getVertexNumber(), destination);
			}
			catch (std::exception e)
			{
				std::cout << e.what() << std::endl;
			}

		}
	}
	break;
	case 7:
	{
		if (testGraph->getIsDirected() == false)
		{
			std::cout << "The graph ought to be directed\n" << std::endl;
		}
		else
		{
			try
			{
				size_t source = getVertex();
				int** paths = bfAlg->getMinPaths(testGraph, source);
				bfAlg->printMinPaths(std::cout, paths, testGraph->getVertexNumber());
				size_t destination = getVertex();
				bfAlg->printMinPath(std::cout, paths, testGraph->getVertexNumber(), destination);
			}
			catch (std::exception e)
			{
				std::cout << e.what() << std::endl;
			}

		}
	}
	break;
	case 0:
	{
		isFinished = true;
	}
	break;
	default:
	{
		std::cout << "\nPlease try again" << std::endl;
	}
	break;
	}
}


size_t ListTest::getVertexNum()
{
	std::cout << "Please enter number of vertices\n";
	size_t option;
	std::cin >> option;

	return option;
}

size_t ListTest::getVertex()
{
	std::cout << "Please enter number of vertex\n";
	size_t option;
	std::cin >> option;

	return option;
}
size_t ListTest::getDensity()
{
	std::cout << "Please enter density of graph\n";
	size_t option;
	std::cin >> option;

	if (option > 100)
	{
		throw* invalid_arg;
	}
	else
		return option;
}

bool ListTest::getDirectory()
{
	std::cout << "Should the graph be directed? [y/n]\n";
	char option;
	std::cin >> option;

	switch (option)
	{
	case 'y':
	{
		return true;
	}
	break;
	case 'n':
	{
		return false;
	}
	break;
	default:
	{
		throw* invalid_arg;
		return false;
	}
	break;
	}
}
#include "../../Headers/menus/Menu.h"
using namespace std;

bool isFinished;

Menu::Menu() {
	this->fillGraph = new FillGraph();
	this->kruskalAlg = new Graphs::Kruskal();
	this->primAlg = new Graphs::Prim();
	this->dijkstraAlg = new Graphs::Dijkstra();
	this->bfAlg = new Graphs::BellmanFord();
	this->matrixTest = new MatrixTest(fillGraph, kruskalAlg, primAlg, dijkstraAlg, bfAlg);
	this->listTest = new ListTest(fillGraph, kruskalAlg, primAlg, dijkstraAlg, bfAlg);

	isFinished = false;

		while (!isFinished) {
			printMenu();
			chooseOption(getChoice());
		}
	
}

Menu::~Menu()
{
	delete this->matrixTest;
	delete this->listTest;
	delete this->fillGraph;
}


void Menu::printMenu()
{
	std::cout << setfill('=') << setw(FILL_WIDTH) << "\n";
	cout << setfill(' ') << setw((int)FILL_WIDTH / 2 - 2) << "MENU\n";
	cout << setfill('=') << setw(FILL_WIDTH) << "\n"
		<< "Please choose one of following options : \n"
		<< "1. Matrix implementation\n"
		<< "2. List implementation\n"
		<< "3. Auto tests\n"
		<< "0. Exit" << endl;
}

int Menu::getChoice()
{
	int choice;
	cin >> choice;
	return choice;
}

void Menu::chooseOption(int choice)
{
	switch (choice)
	{
	case 1:
	{
		this->matrixTest->run();
	}
	break;
	case 2:
	{
		this->listTest->run();
	}
	break;
	case 3:
	{
		AutoTest* autoT = new AutoTest(fillGraph, kruskalAlg, primAlg, dijkstraAlg, bfAlg);
		delete autoT;
	}
	break;

	case 0:
	{
		isFinished = true;
	}
	break;
	default:
		cout << "\nPlease try again" << endl;
	}
}
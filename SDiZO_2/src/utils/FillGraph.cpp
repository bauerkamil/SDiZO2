#include "../../Headers/utils/FillGraph.h"

FillGraph::FillGraph()
{
	this->edgeNum = 0;
	this->vertexNum = 0;
	this->edgeList = nullptr;

	std::srand(std::time(0));
}

FillGraph::~FillGraph()
{
	clear();
}

size_t** FillGraph::getEdgeList()
{
	return this->edgeList;
}

size_t FillGraph::getEdgeNum()
{
	return this->edgeNum;
}

size_t FillGraph::getVertexNum()
{
	return this->vertexNum;
}

void FillGraph::fillFromFile(std::string fileName)
{
	clear();

	const char delimiter = ' ';

	std::ifstream file;
	file.open(fileName, std::ios::in);

	if (file.is_open())
	{
		std::string line, string;
		std::getline(file, line);

		std::istringstream iss(line);

		std::getline(iss, string, delimiter);
		this->edgeNum = std::stoi(string);
		std::getline(iss, string, delimiter);
		this->vertexNum = std::stoi(string);

		this->edgeList = new size_t * [edgeNum];

		size_t i = 0;
		while (std::getline(file, line))
		{
			this->edgeList[i] = new size_t[3];

			std::istringstream iss(line);
			std::getline(iss, string, delimiter);
			this->edgeList[i][0] = std::stoi(string);
			std::getline(iss, string, delimiter);
			this->edgeList[i][1] = std::stoi(string);
			std::getline(iss, string, delimiter);
			this->edgeList[i][2] = std::stoi(string);

			i++;
			/*if (i > edgeNum)
			{
				throw* fileCorrupted;
			}*/
		}
		return;
	}
	throw* file404;
}

void FillGraph::fillRandom(size_t vertexNum, size_t densityPercent, bool isDirected)
{
	clear();

	//std::cout << "V: " << vertexNum << " D: " << densityPercent << " Dir " << isDirected << std::endl;

	if (vertexNum == 0)
	{
		return;
	}

	size_t edgeNum = (size_t)floor(vertexNum * (vertexNum - 1) * densityPercent / 200);


	if (edgeNum < vertexNum || densityPercent > 100)
	{
		throw* invalid_density;
	}

	if (isDirected)
	{
		fillRandomDirected(vertexNum, edgeNum, densityPercent);
	}
	else
		fillRandomNonDirected(vertexNum, edgeNum, densityPercent);

}

void FillGraph::clear()
{
	if (edgeList)
	{
		for (size_t i = 0; i < edgeNum; i++)
		{
			delete[] edgeList[i];
		}
		delete[] edgeList;
		this->edgeNum = 0;
		this->vertexNum = 0;
	}
}

void FillGraph::fillRandomDirected(size_t vertexNum, size_t edgeNum, size_t densityPercent)
{
	bool* addedVertex = new bool[vertexNum];
	for (size_t i = 0; i < vertexNum; i++)
	{
		addedVertex[i] = false;
	}

	size_t** adjencyMatrix = new size_t * [vertexNum];
	for (size_t i = 0; i < vertexNum; i++)
	{
		size_t* row = new size_t[vertexNum];
		adjencyMatrix[i] = row;
		for (size_t j = 0; j < vertexNum; j++)
		{
			adjencyMatrix[i][j] = 0;
		}

	}

	//create ring
	for (size_t i = 0; i < vertexNum; i++)
	{
		size_t weight = rand() % 100;
		while (weight == 0)
		{
			weight = rand() % 100;
		}

		if (i + 1 == vertexNum)
		{
			adjencyMatrix[i][0] = weight;
			break;
		}
		else
			adjencyMatrix[i][i + 1] = weight;
	}

	size_t remainingEdges = edgeNum - vertexNum;
	for (size_t i = 0; i < remainingEdges; i++)
	{
		size_t source = rand() % vertexNum;
		size_t destination = rand() % vertexNum;

		while (adjencyMatrix[source][destination] != 0)
		{
			source = rand() % vertexNum;
			destination = rand() % vertexNum;
		}

		size_t weight = rand() % 100;
		while (weight == 0)
		{
			weight = rand() % 100;
		}

		adjencyMatrix[source][destination] = weight;
	}

	this->vertexNum = vertexNum;
	this->edgeNum = edgeNum;
	this->edgeList = new size_t * [edgeNum];
	for (size_t i = 0; i < edgeNum; i++)
	{
		this->edgeList[i] = new size_t[3];
	}

	size_t pos = 0;
	for (size_t i = 0; i < vertexNum; i++)
	{
		for (size_t j = 0; j < vertexNum; j++)
		{
			if (adjencyMatrix[i][j] != 0)
			{
				this->edgeList[pos][0] = i;
				this->edgeList[pos][1] = j;
				this->edgeList[pos][2] = adjencyMatrix[i][j];
				pos++;
			}
		}
	}


	for (size_t i = 0; i < vertexNum; i++)
	{
		delete[] adjencyMatrix[i];
	}
	delete[] adjencyMatrix;
}

void FillGraph::fillRandomNonDirected(size_t vertexNum, size_t edgeNum, size_t densityPercent)
{
	bool* addedVertex = new bool[vertexNum];
	for (size_t i = 0; i < vertexNum; i++)
	{
		addedVertex[i] = false;
	}

	size_t** adjencyMatrix = new size_t * [vertexNum];
	for (size_t i = 0; i < vertexNum; i++)
	{
		size_t* row = new size_t[vertexNum];
		adjencyMatrix[i] = row;
		for (size_t j = 0; j < vertexNum; j++)
		{
			adjencyMatrix[i][j] = 0;
		}

	}

	//std::cout << "step";
	addedVertex[0] = true;
	//create mst
	for (size_t i = 1; i < vertexNum; i++)
	{
		size_t destination = rand() % vertexNum;

		while (addedVertex[destination] == false)
		{
			//std::cout << destination << " ";
			destination = rand() % vertexNum;
		}
		//std::cout << destination << "\n";

		size_t weight = rand() % 100;
		while (weight == 0)
		{
			weight = rand() % 100;
		}

		adjencyMatrix[i][destination] = weight;
		adjencyMatrix[destination][i] = weight;
		//std::cout << i << " " << destination << " " << weight << std::endl;

		addedVertex[i] = true;
	}

	delete[] addedVertex;

	size_t remainingEdges = edgeNum - vertexNum + 1;
	for (size_t i = 0; i < remainingEdges; i++)
	{
		size_t source = rand() % vertexNum;
		size_t destination = rand() % vertexNum;

		while (adjencyMatrix[source][destination] != 0)
		{
			source = rand() % vertexNum;
			destination = rand() % vertexNum;
		}

		size_t weight = rand() % 100;
		while (weight == 0)
		{
			weight = rand() % 100;
		}

		adjencyMatrix[source][destination] = weight;
		adjencyMatrix[destination][source] = weight;
		//std::cout << source << " " << destination << " " << weight << std::endl;

	}
	this->vertexNum = vertexNum;
	this->edgeNum = edgeNum;
	this->edgeList = new size_t * [edgeNum];
	for (size_t i = 0; i < edgeNum; i++)
	{
		this->edgeList[i] = new size_t[3];
	}

	//for (size_t i = 0; i < vertexNum; i++)
	//{
	//	for (size_t j = 0; j < vertexNum; j++)
	//	{
	//		std::cout << adjencyMatrix[i][j] << " ";
	//	}
	//	std::cout << std::endl;
	//}

	//std::cout << "EdgeList: \n";
	size_t pos = 0;
	for (size_t i = 0; i < vertexNum; i++)
	{
		for (size_t j = 0; j < vertexNum; j++)
		{
			if (adjencyMatrix[i][j] != 0)
			{
				this->edgeList[pos][0] = j;
				this->edgeList[pos][1] = i;
				this->edgeList[pos][2] = adjencyMatrix[i][j];
				adjencyMatrix[j][i] = 0;
				pos++;
				// std::cout << i << " " << j << " " << adjencyMatrix[i][j] << std::endl;
			}
		}
	}
	//std::cout << pos;

	for (size_t i = 0; i < vertexNum; i++)
	{
		delete[] adjencyMatrix[i];
	}
	delete[] adjencyMatrix;
}

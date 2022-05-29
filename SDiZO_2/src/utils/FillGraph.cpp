#include "../../Headers/utils/FillGraph.h"

FillGraph::FillGraph()
{
	this->edgeNum = 0;
	this->vertexNum = 0;
	this->edgeList = nullptr;
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
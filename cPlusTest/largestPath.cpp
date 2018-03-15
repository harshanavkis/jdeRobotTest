#include <iostream>
#include <fstream>
#include "bfsFunc.h"

int rows, cols;
std::vector<std::vector<bool> > visited;
std::vector<std::vector<char> > spaceMatrix;

int main(int argc, char const *argv[])
{
	std::ifstream inFile;
	int lineCount=0;
	std::string currentLine;
	int charCount;

	inFile.open(argv[1]);

	while(std::getline(inFile, currentLine))
	{
		++lineCount;
		std::vector<char> v = split(currentLine);
		std::vector<bool> b;
		for(int i=0; i<v.size(); i++)
			b.push_back(false);
		spaceMatrix.push_back(v);
		visited.push_back(b);
	}

	std::vector<std::vector<bool> > tempVisit = visited;
	inFile.close();
	rows = lineCount;
	cols = spaceMatrix[0].size();

	bfsProp prevProp;
	prevProp.dist = 0;

	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<cols; j++)
		{
			if(spaceMatrix[i][j]=='.' && !visited[i][j])
			{
				bfsProp d = bfs(i, j);
				if(prevProp.dist < d.dist)
					prevProp = d;
			}
		}
	}
	std::cout<< rows << cols <<std::endl;

	std::cout << prevProp.dist << std::endl;
	std::cout << prevProp.x << " " << prevProp.y << std::endl;

	visited = tempVisit;

	std::ofstream outFile;
	outFile.open(argv[1]);
	if(!outFile)
	{
		std::cerr << "Error: file could not be opened" << std::endl;
      	exit(1);
	}
	outFile<<prevProp.dist<<'\n';

	bfsChangeVals(prevProp.x, prevProp.y);

	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<cols; j++)
		{
			std::cout<<spaceMatrix[i][j] << " ";
		}
		std::cout<<std::endl;
	}

	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<cols; j++)
		{
			if(spaceMatrix[i][j]!='.' && spaceMatrix[i][j]!='#')
				outFile << spaceMatrix[i][j]-'0' << char(32);
			else
				outFile << spaceMatrix[i][j] << char(32);
		}
		outFile<<'\n';
	}
	outFile.close();


	return 0;
}

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <fstream>

struct bfsProp
{
	int x, y, dist;
};

struct coord
{
	int x, y;
};

bfsProp bfs(int, int);
bool isValid(int, int);
std::vector<char> split(std::string);
void bfsChangeVals(int, int);
// std::string join(std::vector<char>);

std::vector<std::vector<bool> > visited;
std::vector<std::vector<char> > spaceMatrix;

int rows, cols;

int main(int argc, char const *argv[])
{
	std::ifstream inFile;
	int lineCount=0;
	std::string currentLine;
	int charCount;

	inFile.open("test.txt");

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
	std::cout << prevProp.dist << std::endl;
	std::cout << prevProp.x << " " << prevProp.y << std::endl;

	visited = tempVisit;
	bfsChangeVals(prevProp.x, prevProp.y);

	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<cols; j++)
		{
			std::cout<<spaceMatrix[i][j] << " ";
		}
		std::cout<<std::endl;
	}

	std::ofstream outFile;
	outFile.open("test.txt");
	if(!outFile)
	{
		std::cerr << "Error: file could not be opened" << std::endl;
      	exit(1);
	}
	outFile<<prevProp.dist<<'\n';
	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<cols; j++)
		{
			outFile<<spaceMatrix[i][j];
		}
		outFile<<'\n';
	}
	outFile.close();


	return 0;
}

int gc[] = {1, 0, 0, -1};
int gr[] = {0, 1, -1, 0};

bool isValid(int x, int y)
{
	return x>-1 && x<rows && y>-1 && y<cols;
}

bfsProp bfs(int i, int j)
{
	std::queue<int> x, y;
	int topx, topy, dist=0;

	visited[i][j] = true;

	bfsProp b;
	b.x = i;
	b.y = j;

	x.push(i);
	y.push(j);

	while(!x.empty())
	{
		topx = x.front();
		topy = y.front();
		x.pop();
		y.pop();

		for(int d=0; d<4; d++)
		{
			i = topx + gr[d];
			j = topy + gc[d];
			if(!isValid(i, j))
				continue;
			if(!visited[i][j] && spaceMatrix[i][j]=='.')
			{
				visited[i][j] = true;
				x.push(i);
				y.push(j);
				dist++;
			}
		}
	}
	b.dist = dist+1;
	return b;
}

std::vector<char> split(std::string line)
{
	std::vector<char> ch;
	for(int i=0; i<line.length(); i++)
	{
		if(line.at(i) != '.' && line.at(i)!='#')
		{
			continue;
		}
		ch.push_back(line.at(i));
	}
	std::cout<<line<<std::endl;
	return ch;
}

void bfsChangeVals(int i, int j)
{
	std::queue<int> x, y;
	int topx, topy, dist=0;
	spaceMatrix[i][j] = char(48);

	x.push(i);
	y.push(j);

	while(!x.empty())
	{
		topx = x.front();
		topy = y.front();
		x.pop();
		y.pop();

		for(int d=0; d<4; d++)
		{
			i = topx + gr[d];
			j = topy + gc[d];
			if(!isValid(i, j))
				continue;
			if(!visited[i][j] && spaceMatrix[i][j]=='.')
			{
				visited[i][j] = true;
				spaceMatrix[i][j] = char(48+dist+1);
				dist++;
				x.push(i);
				y.push(j);
			}
		}
	}
}

// std::string join(std::vector<char> c)
// {

// }

// 5 7                                                                                                                            
// # # . # # # #                                                                                                                  
// # . . # # . #                                                                                                                  
// # . # # # # #                                                                                                                  
// # . . # # # #                                                                                                                  
// # # # # # # #
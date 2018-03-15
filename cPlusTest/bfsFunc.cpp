#include "bfsFunc.h"


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
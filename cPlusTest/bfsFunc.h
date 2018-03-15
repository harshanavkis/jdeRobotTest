#ifndef BFSFUNC_H

#define BFSFUNC_H

#include <iostream>
#include <queue>
#include <vector>
#include <string>

extern std::vector<std::vector<bool> > visited;
extern std::vector<std::vector<char> > spaceMatrix;

extern int rows, cols;


const int gc[] = {1, 0, 0, -1};
const int gr[] = {0, 1, -1, 0};

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

#endif
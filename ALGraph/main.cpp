#include <iostream>
#include "ALGraph.cpp"
using namespace std;


int path[10];
bool visitedFP[10];

int main()
{
	GraphType t = digraph;
	int vexs[5] = {1,2,3,4,5};
	int n =5,e = 7;
	ALGraph<int> a(t,vexs,n,e);
	
	return 0;
}
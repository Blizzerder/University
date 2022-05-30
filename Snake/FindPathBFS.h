#pragma once
#include <queue>

using std::queue;//队列

typedef struct
{
	int x;
	int y;
}COORDINATE;

class FindPathBFS//宽度优先搜索的方式 (BFS算法)
{
private:
	bool **m_chess; //用矩阵表示的图
	bool **m_visit; //节点是否被访问过
	COORDINATE **m_parent;//每个被访问过的节点的父节点
	COORDINATE m_size; //图的大小
	void FindPath(COORDINATE begin_point, COORDINATE end_point);
	void GetQueue(COORDINATE end_point);
public:
	FindPathBFS();
	~FindPathBFS();

	void InitMap(bool **chess); //初始化图
	void GetPath(COORDINATE begin_point, COORDINATE end_point);

	queue<COORDINATE> m_paths_queue;//队列
};
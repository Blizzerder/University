#include <iostream>
#include <vector>
#include <ctime>
#include "SeqQueue.cpp"
using namespace std;
#define MAXY 100
#define INFINITY 999999

enum GraphType{undigraph,digraph,undinetwork,dinetwork};  //无向图、无向网、有向图、有向网

template<class T>
struct EdgeType						//边类型定义
{
	T head,tail;
	int cost;
	EdgeType(T h, T t,int c)
	{
		head = h;tail = t;cost = c;
	}
	EdgeType()
	{
		
		//cost = 0;
	}
};


template<class T>
struct Edge
{
	T adjvex;				//相邻结点
	float lowcost;			//路径
};


template <class T>
class MGraph
{
private:
	int vexnum,edgenum;					//顶点数、边数
	GraphType kind;						//图类型
	vector < vector<int> >edges;		//邻接矩阵
	vector <T> vexs;					//顶点表
	vector <EdgeType<T> > graph;
	int MiniNum(Edge<T> * miniedges)
	{
		int k = 0;
		while (miniedges[k].lowcost==0)
			k++;
		for (int i =0;i<vexnum;i++)
		{
			if (miniedges[i].lowcost<miniedges[k].lowcost&&miniedges[i].lowcost!=0)
				k = i;
		}
		
		return k;
	}
	void DFS(int v , bool * visited)	//连通分量的深度优先遍历
	{
		cout<<vexs[v];
		visited[v] = true;
		for (int i = 0;i<vexnum;i++)
			if (edges[v][i]!= 0 && edges[v][i]!= INFINITY && !visited[i])
				DFS(i,visited);
	}

public:
	MGraph(GraphType t , T v[] , int n , int e)
	{
		vexnum = n;
		edgenum = e;
		kind = t;
		vexs.resize(vexnum);
		edges.resize(vexnum);
		for (int i = 0;i < n;i++)
			vexs[i] = v[i];
		for (i = 0;i<n;i++)
			edges[i].resize(vexnum);
		for (i = 0;i<n;i++)
		{
			for (int j = 0;j<n;j++)
				if (i==j)
					edges[i][j] = 0;
				else
					edges[i][j] = INFINITY;
		}
		srand((int)time(0));
		cout<<"请输入数据：起点 终点 距离"<<endl;
		graph.resize(e);
		for (i = 0;i < e;i++)
		{
			int va,vb,w;
			va = rand()%n;
			vb = rand()%n;
			w = rand()%10+1;
			//cin>>va;
			//cin>>vb;
			//cin>>w;
			graph[i].head = va;
			graph[i].tail = vb;
			graph[i].cost = w;
			switch (t)
			{
			case 0:edges[va][vb] = edges[vb][va] = 1; break;
			case 1:edges[va][vb] = edges[vb][va] = w; break;
			case 2:edges[va][vb] = 1;break;
			case 3:edges[va][vb] = w;break;
			default:cout<<"输入错误！请重新输入："<<endl; i--;break;
			}
		}
	}
	~MGraph(){};
	int GetEdgeOfVex(T v)					//返回某一个顶点的边数量
	{
		int i = GetVexValueNum(v);
		int n = 0;
		for (int j = 0;j<vexnum;j++)
			if (edges[i][j]!= 0 &&edges[i][j]!=INFINITY)
				n++;
		return n;
	}
	int VexterNum()							//返回图中的顶点数量
	{
		return vexnum;
	}
	int EdgeNum()								//返回图中的边数量
	{
		return edgenum;
	}
	T GetVexValue(int i)						//返回顶点表中的第i个顶点的值
	{
		return vexs[i];
	}
	int GetVexValueNum(T v)						//返回顶点表中值的序号
	{
		int i = 0;
		while (vexs[i] != v)
		{
			i++;
		}
		return i;
	}
	int GetEdgeValue(int i , int j)				//返回邻接矩阵中第i个顶点到第j个顶点的权值
	{
		return edges[i][j];
	}
	void InsertVex(T v)							//插入一个顶点
	{
		vexs[vexnum++] = v;
	}
	void RemoveVex(T v)							//删除一个顶点
	{
		int p = GetVexValue(x);
		if (p == -1)
			return ;
		int i ,j;
		int n = GetEdgeOfVex(v);
		for (i = p;i<vexnum-1;i++)
			vexs[i] = vexs[i+1];
		for (i = p;i<vexnum-1;i++)
			for (j = 0;j<vexnum-1;j++)
				edges[i][j]=edges[i+1][j];
		for (i = 0;i<vexnum-1;i++)
			for (j = p;j<vexnum-1;j++)
				edges[i][j] = edges[i][j+1];
		vexnum--;
		edgenum-=n;
	}
	void InsertEdge(EdgeType<T> e,GraphType t)					//插入一条边
	{
		edgenum++;
		int p1 = GetVexValueNum(e.head);
		int p2 = GetVexValueNum(e.tail);
		int w = e.cost;
		switch (t)
		{
		case 0:edges[p1][p2] = edges[p1][p2] = 1; break;
		case 1:edges[p1][p2] = edges[p2][p1] = w; break;
		case 2:edges[p1][p2] = 1;break;
		case 3:edges[p1][p2] = w;break;
		default:cout<<"输入错误！请重新输入："<<endl; edgenum--;break;
		}
	}
	void DeleteEdge(EdgeType<T> e,GraphType t)					//删除一条边
	{
		int p1 = GetVexValueNum(e.head);
		int p2 = GetVexValueNum(e.tail);
		int w = e.cost;
		switch (t)
		{
		case 0:
		case 1:edges[p1][p2] = edges[p2][p1] = 0; break;
		case 2:
		case 3:edges[p1][p2] = 0;break;
		}
		edgenum--;
	}
	
	void DFSTraverse()							//深度优先遍历
	{
		bool * visited = new bool[vexnum];
		for (int v = 0;v<vexnum;v++)
			visited[v] = false;
		for (v = 0;v<vexnum;v++)
			if (!visited[v])
				DFS(v,visited);
		delete []visited;
	}
	void BFSTraverse()							//广度优先遍历
	{
		SeqQueue <int , 10> q;
		bool * visited = new bool[vexnum];
		for (int i = 0;i<vexnum;i++)			//初始化
			visited[i] = false;
		for (i = 0;i<vexnum;i++)
		{
			if (!visited[i])					//未被遍历
			{
				cout<<vexs[i];
				visited[i] = true;
				q.EnQueue(i);
				while (!q.Empty())
				{
					int u = q.DeQueue();
					for (int j = 0;j<vexnum;j++)
					{
						if (edges[u][j] != 0 && edges[u][j] != INFINITY && !visited[j])
						{
							cout<<vexs[j];
							visited[j] = true;
							q.EnQueue(j);
						}
					}
				}
			}
		}
		delete[]visited;
	}
	void PrintEdges()							//遍历邻接矩阵
	{
		int i;
		for (i = 0;i<vexnum;i++)
		{
			cout<<vexs[i]<<" ";
			for (int j = 0;j<vexnum;j++)
				printf("%8d",edges[i][j]);
			cout<<endl;
		}
	}
	void PrintVexs()							//遍历顶点表
	{
		int i;
		for (i = 0;i<vexnum;i++)
			cout<<vexs[i]<<" ";
	}
	void Prim(int v)							//Prim算法求最小生成树
	{
		Edge <T> * miniedges = new Edge<T> [vexnum];	//结点V-U数组，lowcost记录从顶点Vi到顶点u的权值的最小值，adjvex记录最短边所关联的另外一个结点
		for (int i = 0; i < vexnum ; i++)			
		{												//v是根节点
			miniedges[i].adjvex = GetVexValue(v);		//所有其他结点和根节点关联
			miniedges[i].lowcost = GetEdgeValue(v,i);	//所有其他结点到根节点的距离
		}
		miniedges[v].lowcost = 0;						//自己到自己的距离为0
		for (i = 1;i < vexnum ; i++)
		{
			int k = MiniNum(miniedges);					//找到一个到当前树具有最小权值的结点
			cout<<miniedges[k].adjvex<<"-->"<<GetVexValue(k)<<endl;//显示新生成的边
			miniedges[k].lowcost = 0;					//表明这个顶点加入到最小生成树中
			for (int j = 0;j < vexnum; j++)				//
			{
				if (k<vexnum)
				if (GetEdgeValue(k,j) < miniedges[j].lowcost &&GetEdgeValue(k,j)!=0)//这个新的结点有一条更近的边
				{
					miniedges[j].adjvex = GetVexValue(k);	// 调整最近边
					miniedges[j].lowcost = GetEdgeValue(k,j);
				}
			}
		}
		delete []miniedges;
	}
	void GetGraph(vector<EdgeType<T> > &graph)
	{
		for (int i = 0 ; i < edgenum ; i++)
			for (int j = i ; j<edgenum ; j++)
				if (graph[i].cost > graph[j].cost)
				{
					EdgeType<T> temp = graph[i];
					graph[i] = graph[j];
					graph[j] = temp;
				}
	}
	void Kruskal(vector <EdgeType<T> > &tree)		//Kruskal算法构造最小生成树
	{
		vector <EdgeType<T> > graph1 = graph;
		graph.resize(vexnum-1);
		GetGraph(graph1);
		tree.resize(vexnum-1);
		int * components = new int[vexnum];
		for (int i = 0 ; i < vexnum ; i++)
			components[i] = i;
		int k = 0;
		int j = 0;
		while (k < vexnum - 1)
		{
			T h1 = graph1[j].head;
			T t1 = graph1[j].tail;
			int H1 = GetVexValueNum(h1);
			int T1 = GetVexValueNum(t1);
			int h2 = components[H1];
			int t2 = components[T1];
			if (h2 != t2)
			{
				tree[k].head = h1;
				tree[k].tail = t1;
				tree[k].cost = graph1[j].cost;
				k++;			//边加一条
				for (int i = 0;i<vexnum;i++)
					if (components[i] == t2)
						components[i] = h2;
			}
			j++;
		}
		delete[] components;
	}
	void Dijkstra(int v , int path[] , int dist[])//求单源最短路径
	{
		bool * s = new bool[vexnum];
		for (int i = 0;i<vexnum;i++)
		{
			s[i] = false;
			dist[i] = GetEdgeValue(v,i);
			if (dist[i]<INFINITY||i==v)
				path[i] = v;
			else
				path[i] = -1;
		}
		dist[v] = 0;
		s[v] = true;
		for (i = 1;i<vexnum;i++)
		{
			int k = v;
			int min = INFINITY;
			for (int j = 0; j < vexnum ; j++)
				if (!s[j]&&dist[j]<min)
				{
					min = dist[j];
					k = j;
				}
			s[k] = true;
			for (int w = 0;w<vexnum;w++)
				if (!s[w]&&dist[w]>dist[k]+GetEdgeValue(k,w))
				{
					dist[w] = dist[k] +GetEdgeValue(k,w);
					path[w] = k;
				}
		}
		delete[]s;
	}
	void Floyd(int path[][MAXY] , int D[][MAXY])//求各顶点对之间最短路径
	{
		for (int i = 0 ; i<vexnum;i++)
			for (int j = 0;j<vexnum;j++)
			{
				if (i == j)
					D[i][j] = 0;
				else
					D[i][j] = GetEdgeValue(i,j);
				if (D[i][j] < INFINITY)
					path[i][j] = j;
				else
					path[i][j] = -1;
			}
		for (int k = 0;k<vexnum;k++)
			for (i = 0;i<vexnum;i++)
				for (int j = 0;j<vexnum;j++)
					if (D[i][k]+D[k][j]<D[i][j])
					{
						D[i][j] = D[i][k]+D[k][j];
						path[i][j] = path[i][k];
					}
		
	}
	void Output(int path[][MAXY] , int D[][MAXY])
	{
		cout<<"path数组："<<endl;
		for (int i = 0;i<vexnum;i++)
		{
			for (int j = 0;j<vexnum;j++)
				cout<<path[i][j]<<" ";
			cout<<endl;
		}
		cout<<"D数组:"<<endl;
		for (i = 0;i<vexnum;i++)
		{
			for (int j = 0;j<vexnum;j++)
				cout<<D[i][j]<<" ";
			cout<<endl;
		}
	}
};



template<class T>
PrintSubTree(MGraph<T> &g,vector<EdgeType<T> > tree)
{
	int i = 0;
	while (i<tree.size())
	{
		int k1 = g.GetVexValueNum(tree[i].head);
		int k2 = g.GetVexValueNum(tree[i].tail);
		cout<<g.GetVexValue(k1)<<"-->"<<g.GetVexValue(k2)<<endl;
		i++;
	}
}


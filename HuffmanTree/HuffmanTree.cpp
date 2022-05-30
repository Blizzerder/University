#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct HuffmanNode
{
	char data;
	double weight;
	int parent,lchild,rchild;
};

class HuffmanTree
{
private:
	vector<HuffmanNode> hufftree;		//树中所有结点的存储空间
	int n;								//叶子结点数
public:
	void SelectSmall(int &least,int &less,int n)
	{
		int i = 0;
		while (hufftree[i].parent!=-1 && i<n)
			i++;
		least = i;
		i++;
		while (hufftree[i].parent!=-1 && i<n)
			i++;
		if (hufftree[i].weight < hufftree[least].weight)
		{
			less = least;
			least = i;
		}
		else
		{
			less = i;
		}
		for (int j = i+1;j < n;j++)
		{
			if (hufftree[j].parent != -1)
				continue;
			if (hufftree[j].weight < least)
			{
				less =least;
				least = j;
			}
			else
				if (hufftree[j].weight>=least && hufftree[j].weight<less)
					less = j;
		}
	}
	HuffmanTree(vector<HuffmanNode>&leaves)
	{
		n = leaves.size();
		hufftree.resize( 2 * n - 1);
		for (int i = 0;i<n;i++)
		{
			hufftree[i].data = leaves[i].data;
			hufftree[i].weight = leaves[i].weight;
			hufftree[i].parent = hufftree[i].lchild = hufftree[i].rchild = -1;
		}
		for (i = n ; i < 2 * n - 1 ; i++)
		{
			int least,less;
			SelectSmall(least,less,i);
			hufftree[least].parent = hufftree[less].parent = i;
			hufftree[i].parent = -1;
			hufftree[i].lchild = least;
			hufftree[i].rchild = less;
			hufftree[i].weight = hufftree[least].weight+hufftree[less].weight;
		}
	}
	~HuffmanTree()
	{
	}
	vector<int>GetCode(int i)			//取编码
	{
		vector<int>code;
		int p = i;						//p是当前结点的下标
		int parent = hufftree[i].parent;
		while (parent!= -1)
		{
			if (hufftree[parent].lchild == p)
				code.insert(code.begin(),0);
			else
				code.insert(code.begin(),1);
			p = parent;
			parent = hufftree[parent].parent;
		}
		return code;
	}
	string Decode(vector<int> &source)	//译码
	{
		string target = "";
		int root = hufftree.size()-1;
		int  p = root;
		for (int i = 0;i<source.size();i++)
		{
			if (source[i] == 0)
				p = hufftree[p].lchild;
			else
				p = hufftree[p].rchild;
			if (hufftree[p].lchild == -1 && hufftree[p].rchild == -1)
			{
				target = target + hufftree[p].data;
				p = root;
			}
		}
		return target;
	}
};
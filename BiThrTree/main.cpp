#include <iostream>
#include <vector>
#include "BiThrTree.h"
using namespace std;
int main()
{
	cout<<"请输入数据："<<endl;
	char c;
	vector<char> data;
	while (cin>>c)
	{
		if (c!='@')
			data.push_back(c);
		else
			break;
	}
	InBiThrTree<char> t(data);
	t.InThreaded();
	cout<<"线索二叉树的中序遍历为:"<<endl;
	t.Travese();
	cout<<endl;
	cout<<"B的后继结点地址为："<<endl;
	BiThrNode<char> *p = t.GetRoot();
	p = p->lchild;
	cout<<t.GetNext(p)<<endl;
	cout<<"B的前驱结点地址为："<<endl;
	cout<<t.GetPrev(p)<<endl;
	cout<<"B的父结点地址为："<<endl;
	cout<<t.GetParent(p)<<endl;
	return 0;
}
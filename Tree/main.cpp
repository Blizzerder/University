#include <iostream>
#include <vector>
#include "tree.cpp"
using namespace std;

int main()
{
	//cout<<"请输入树的前序值："<<endl;
	vector<char> data1;
	vector<char> data2;
	char c;
	while (cin>>c)
	{
		if (c!='@')
			data1.push_back(c);
		else
			break;
	}
	
	while (cin>>c)
	{
		if (c!='@')
			data2.push_back(c);
		else
			break;
	}
	BiTree<char> t(data1,data2);
	cout<<"树的前序遍历为：";t.PreOrder();
	cout<<endl<<"树的中序遍历为：";t.InOrder();
	cout<<endl<<"树的后序遍历为：";t.PostOrder();
	cout<<endl;
	cout<<"树的层序遍历为：";t.LevelOrder();
	cout<<endl;
	cout<<"树的结点个数为："<<t.Count()<<endl;
	cout<<"树的高为："<<t.Height()<<endl;
	cout<<"指向A的指针为："<<t.Search('A')<<endl;
	return 0;
}
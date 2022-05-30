#include <iostream>
#include "BiSortTree.cpp"

using namespace std;

int main()
{
	int a[11]={63,45,90,24,58,74,99,16,35,64,85};
	int n = 11;
	BiSortTree t(a,n);
	cout<<"树的中序遍历为："<<endl;
	t.InOrder();
	cout<<endl;
	int k = 58;
	bool p1 = t.Search(k);
	if (p1 == 1)
		cout<<"树中存在结点"<<k<<endl;
	else
		cout<<"树中不存在结点"<<k<<endl;
	k = 70;
	bool p2 = t.Search2(k);
	if (p2 == 1)
		cout<<"树中存在结点"<<k<<endl;
	else
		cout<<"树中不存在结点"<<k<<endl;
	cout<<"删除45之后的中序遍历为:"<<endl;
	t.Delete(45);
	t.InOrder();
	return 0;
}
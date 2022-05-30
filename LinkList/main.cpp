#include <iostream>
#include "linklist.cpp"

using namespace std;

int main()
{
	int a[5]={1,2,3,4,5};
	LinkList<int> s(a,5);
	cout<<"原始的链表为："<<endl;
	s.PrintLinkList();

	cout<<"链表的长度为："<<s.ListLength()<<endl;

	cout<<"链表第二个元素为："<<s.Get(2)<<endl;

	cout<<"链表中数值3在第"<<s.Locate(3)<<"个元素"<<endl;

	s.Insert(2,3);
	cout<<"在链表的第二个位置插入3后的链表为："<<endl;
	s.PrintLinkList();

	s.Delete(3);
	cout<<"删除第三个数据后的链表为："<<endl;
	s.PrintLinkList();

	s.Invert();
	cout<<"转置后的链表为："<<endl;
	s.PrintLinkList();

	cout<<"有序排列后的链表为："<<endl;
	int b[5]={0,2,5,6,7};
	LinkList<int> g(b,5);
	g.Invert();
	s.Merge(s,g);
	s.PrintLinkList();
	s.~LinkList();
	return 0;
}
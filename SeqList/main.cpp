#include <iostream>
#include "SeqList.cpp"

using namespace std;

void main()
{
	int a[5];
	cout<<"请输入5个原始数据："<<endl;
	for (int i=0;i<5;i++)
	{
		cin>>a[i];
	}
	SeqList<int , 100> s(a,5);
	cout<<"原始顺序表显示为： ";
	s.Print();
	s.Insert(2,7);
	cout<<"插入后的顺序表显示为： ";
	s.Print();
	s.DeletePosition(2);
	cout<<"删除后的顺序表显示为： ";
	s.Print();

	/****************
	扩展功能
	****************/

	s.Sort();
	cout<<"排序后的顺序表显示为： ";
	s.Print();

	cout<<"请输入你想得到的数据位置： ";
	int k;
	cin>>k;
	cout<<"该位置的数据为";
	cout<<s.GetData(k)<<endl;

	cout<<"请输入你想查找位置的数据： ";
	int h;
	cin>>h;
	int ss[100];
	int aa = s.GetPosition(h,ss);
	if (aa != 0)
	{
		cout<<"该数据在第";
		for (i=0;i<aa;i++)
			cout<<ss[i]+1<<" ";
		cout<<"个位置"<<endl;
	}
	else
		cout<<"无该数值！"<<endl;

	int b[4]={4,1,3,5};
	SeqList<int,100> p(b,4);
	s.Merge(p);
	cout<<"有序插入后的顺序表显示为： ";
	s.Print();

	cout<<"删除的最小值为： ";
	cout<<s.DeleteMin()<<endl;

	s.DeleteItem(3);
	cout<<"删除所有的3后的顺序表显示为： ";
	s.Print();

	s.DeleteItem(2,4);
	cout<<"删除2~4后的顺序表显示为： ";
	s.Print();

	s.DeleteRepeat();
	cout<<"去重后的顺序表显示为： ";
	s.Print();

	int c[6]={5,1,3,7,8,2};
	SeqList<int,100> f(c,6);
	f.ReSortList();
	cout<<"重新排列的顺序表显示为： ";
	f.Print();

	f.MoveLeft(2);
	cout<<"左移2位后的顺序表显示为： ";
	f.Print();
}
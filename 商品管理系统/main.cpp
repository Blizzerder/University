#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "SeqList.cpp"
#include "Goods.h"
using namespace std;

int menu()
{
	int choice;
	cout<<"----------------------------"<<endl;
	cout<<"-       库存管理系统       -"<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"-      1.显示库存          -"<<endl;
    cout<<"-      2.修改库存          -"<<endl;
    cout<<"-      3.删除记录		  -"<<endl;
    cout<<"-      4.对库存记录排序    -"<<endl;
    cout<<"-      5.退出       -"<<endl;
	cout<<"----------------------------"<<endl;
	cout<<"请选择操作：";
	cin>>choice;
	return choice;
}

int main()
{
	ifstream in("data.txt");
	Goods goods[100];
	Goods del;
	int count = 0;
	while (!in.eof())
	{
		in>>goods[count];
		count++;
	}
	in.close();
	SeqList <Goods,100> s(goods,count);
	while (true)
	{
		int index,pos;
		Goods g;
		int choice = menu();
		switch(choice)
		{
		case 1:
			cout<<"*************************************************"<<endl;
			cout<<"商品代码"<<setw(15)<<"商品名称"<<setw(15)<<"商品价格"<<setw(13)<<"商品库存"<<endl;
			s.Print();
			cout<<"*************************************************"<<endl;
			break;
		case 2:
			cout<<"请输入要修改的商品代码"<<endl;			
			cin>>index;
			g.SetID(index);
			pos = s.Locate(g);
			if (pos == -1)
			{
				cout<<"当前索引号不存在，开始添加新记录："<<endl;
				string name;
				float price;
				int stock;
				cout<<"请输出商品的名称、价格和库存量："<<endl;
				cin>>name>>price>>stock;
				g.SetName(name);
				g.SetPrice(price);
				g.SetStock(stock);
				s.Insert(s.GetLength()+1,g);
				cout<<"*****************************"<<endl;
				cout<<"修改后的库存为："<<endl;
				cout<<"商品代码"<<setw(15)<<"商品名称"<<setw(15)<<"商品价格"<<setw(13)<<"商品库存"<<endl;
				s.Print();
				cout<<"*************************************************"<<endl;
			}
			else
			{
				int restock;
				cout<<"请输入库存修正量："<<endl;
				cin>>restock;
		 		s.GetData(pos).SetStock(restock);
				cout<<"修改后的库存为："<<endl;
				cout<<"*************************************************"<<endl;
				cout<<"商品代码"<<setw(15)<<"商品名称"<<setw(15)<<"商品价格"<<setw(13)<<"商品库存"<<endl;
				s.Print();
				cout<<"*************************************************"<<endl;
			}
			break;
		case 3:
			cout<<"请输入要删除的商品的代码："<<endl;
			cin>>index;
			g.SetID(index);
			pos = s.Locate(g);
			del = s.DeletePosition(pos);
			cout<<"删除成功！"<<endl;
			cout<<"当前库存为："<<endl;
			//cout<<"修改后的库存为："<<endl;
			cout<<"*************************************************"<<endl;
			cout<<"商品代码"<<setw(15)<<"商品名称"<<setw(15)<<"商品价格"<<setw(13)<<"商品库存"<<endl;
			s.Print();
			cout<<"*************************************************"<<endl;
			break;
		case 4:
			s.Sort();
			cout<<"排序后的库存表为："<<endl;
			cout<<"*************************************************"<<endl;
			cout<<"商品代码"<<setw(15)<<"商品名称"<<setw(15)<<"商品价格"<<setw(13)<<"商品库存"<<endl;
			s.Print();
			cout<<"*************************************************"<<endl;
			break;
		case 5:
			return 0;
		default:
			cout<<"错误的输入，请重选"<<endl;
		}
	}
	return 0;
}
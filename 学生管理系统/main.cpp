#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "linklist.cpp"
#include "Student.h"
using namespace std;

int menu()
{
	int choice;
	cout<<"    欢迎使用学籍管理系统！  "<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"-      1.显示学生信息      -"<<endl;
    cout<<"-      2.按学号查询        -"<<endl;
    cout<<"-      3.删除学生		  -"<<endl;
    cout<<"-      4.增加学生          -"<<endl;
    cout<<"-      5.修改学生信息      -"<<endl;
	cout<<"-      6.退出              -"<<endl;
	cout<<"----------------------------"<<endl;
	cout<<"请选择操作：";
	cin>>choice;
	return choice;
}

int main()
{
	Student student[100];
	int count = 0;
	int index,pos;
	Student g;
	ifstream in("data.txt");
	while (!in.eof())
	{
		in>>student[count];
		count++;
	}
	int id;
			string name;
			char sex;
			string major;
			int year,month,day;
	in.close();
	LinkList <Student> s(student,count);
	while (true)
	{
		int choice = menu();
		switch (choice)
		{
		case 1:
			cout<<"*************************************************"<<endl;
			cout<<setw(5)<<"学号"<<setw(15)<<"姓名"<<setw(15)<<"性别"<<setw(20)<<"专业"<<setw(15)<<"出生年月"<<endl;
			s.PrintLinkList();
			cout<<"*************************************************"<<endl;
			break;
		case 2:
			cout<<"请输入你想查询的学号："<<endl;
			cin>>index;
			g.SetID(index);
			pos = s.Locate(g);
			if (pos == 0)
			{
				cout<<"无当前学号！"<<endl;
			}
			else
			{
				cout<<setw(5)<<"学号"<<setw(15)<<"姓名"<<setw(15)<<"性别"<<setw(20)<<"专业"<<setw(15)<<"出生年月"<<endl;
				s.Get(pos).print();
			}
			cout<<"*************************************************"<<endl;
			break;
		case 3:
			cout<<"请输入想要删除的学生学号:"<<endl;
			cin>>index;
			g.SetID(index);
			pos = s.Locate(g);
			if (pos == 0)
			{
				cout<<"无当前学号！"<<endl;
			}
			else
			{
				g = s.Delete(pos);
				cout<<"删除成功！现在的学籍系统为："<<endl;
				cout<<"*************************************************"<<endl;
				cout<<setw(5)<<"学号"<<setw(15)<<"姓名"<<setw(15)<<"性别"<<setw(20)<<"专业"<<setw(15)<<"出生年月"<<endl;
				s.PrintLinkList();
				cout<<"*************************************************"<<endl;
			}
			break;
		case 4:
			cout<<"请输入学号、姓名、性别、专业、出生日期"<<endl;
			
			cin>>id>>name>>sex>>major>>year>>month>>day;
			g.SetID(id);
			g.SetName(name);
			g.SetSex(sex);
			g.SetMajor(major);
			g.SetBirthday(year,month,day);
			s.Insert(s.ListLength()+1,g);
			cout<<"修改后："<<endl;
			cout<<"*************************************************"<<endl;
			cout<<setw(5)<<"学号"<<setw(15)<<"姓名"<<setw(15)<<"性别"<<setw(20)<<"专业"<<setw(15)<<"出生年月"<<endl;
			s.PrintLinkList();
			cout<<"*************************************************"<<endl;
			break;
		case 5:
			cout<<"请输入你想修改的学生学号："<<endl;
			cin>>index;
			g.SetID(index);
			pos = s.Locate(g);
			if (pos == 0)
			{
				cout<<"无当前学号！"<<endl;
			}
			else
			{
			cout<<"请输入新的专业："<<endl;
			cin>>major;
			s.Get(pos).SetMajor(major);
			cout<<"修改后："<<endl;
			cout<<"*************************************************"<<endl;
			cout<<setw(5)<<"学号"<<setw(15)<<"姓名"<<setw(15)<<"性别"<<setw(20)<<"专业"<<setw(15)<<"出生年月"<<endl;
			s.PrintLinkList();
			cout<<"*************************************************"<<endl;
			}
			break;
		case 6:
			return 0;
		default:
			cout<<"错误的输入，请重选！"<<endl;
		}
	}
	return 0;

}
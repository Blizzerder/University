#include <iostream>
#include "SeqStack.cpp"

using namespace std;

int main()
{
	SeqStack<int , 100> s;
	s.Push(1);
	cout<<"插入第一个元素之后的栈为：";
	s.Print();
	s.Push(3);
	s.Push(5);
	cout<<"插入第二、三个元素之后的栈为：";
	s.Print();
	s.Pop();
	cout<<"删除栈顶元素之后的栈为：";
	s.Print();
	cout<<"栈顶元素为："<<s.Top()<<endl;
	return 0;
}
#include <iostream>
#include "SeqQueue.cpp"

using namespace std;

int main()
{
	SeqQueue<int , 3> s;
	s.EnQueue(1);							//1
	cout<<"插入1之后的头元素为：";
	cout<<s.GetQueue()<<endl;				
	s.EnQueue(2);							//2  1
	cout<<"插入2之后的头元素为：";
	cout<<s.GetQueue()<<endl;

	//cout<<s.Full()<<endl;
	s.EnQueue(3);
	cout<<"插入3之后的判满结果为：";
	cout<<s.Full()<<endl;
	cout<<"删除2之后的头元素为：";
	s.DeQueue();							//2
	cout<<s.GetQueue()<<endl;
	s.DeQueue();
	s.DeQueue();
	cout<<"再删除两次之后的判空结果为：";
	cout<<s.Empty()<<endl;
	return 0;
}

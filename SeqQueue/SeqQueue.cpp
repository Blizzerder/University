#include <iostream>
#include "SeqQueue¡£h.h"

using namespace std;

template <class T,int MaxSize>
SeqQueue<T,MaxSize>::SeqQueue()
{
	front = rear = 0;
	sum =0;
}

template <class T,int MaxSize>
void SeqQueue<T,MaxSize>::EnQueue(T x)
{
	if ((rear%MaxSize)==front&&sum == MaxSize)
	{
		cerr<<"ÉÏÒç"<<endl;
		exit(1);
	}
	rear = (rear+1) % MaxSize;
	data[rear] = x;
	//flag = true;
	sum++;
}
template <class T,int MaxSize>
T SeqQueue<T,MaxSize>::DeQueue()
{
	if (rear == front && sum == 0)
	{
		cerr<<"ÏÂÒç";
		exit(1);
	}
	front = (front+1) % MaxSize;
	sum--;
	return data[front];
}


template <class T,int MaxSize>
bool SeqQueue<T,MaxSize>::Empty()
{
	return (rear == front && sum == 0);
}

template <class T,int MaxSize>
T SeqQueue<T,MaxSize>::GetQueue()
{
	return data[front+1];
}

template <class T,int MaxSize>
bool SeqQueue<T,MaxSize>::Full()
{
	return (rear == front && sum == MaxSize);
}
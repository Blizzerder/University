#include <iostream>
#include "SeqQueue.h"

using namespace std;

template <class T,int MaxSize>
SeqQueue<T,MaxSize>::SeqQueue()
{
	front = rear = 0;
}

template <class T,int MaxSize>
void SeqQueue<T,MaxSize>::EnQueue(T x)
{
	if ((rear+1)%MaxSize==front)
	{
		cerr<<"ÉÏÒç"<<endl;
		exit(1);
	}
	rear = (rear+1) % MaxSize;
	data[rear] = x;
}
template <class T,int MaxSize>
T SeqQueue<T,MaxSize>::DeQueue()
{
	if (rear == front)
	{
		cerr<<"ÏÂÒç";
		exit(1);
	}
	front = (front+1) % MaxSize;
	return data[front];
}


template <class T,int MaxSize>
bool SeqQueue<T,MaxSize>::Empty()
{
	return rear == front;
}

template <class T,int MaxSize>
T SeqQueue<T,MaxSize>::GetQueue()
{
	return data[front+1];
}
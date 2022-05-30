#include <iostream>
#include "SeqStack.h"

using namespace std;

template <class T , int MaxSize>
SeqStack<T,MaxSize>::SeqStack()
{
	top = -1;
}

template <class T , int MaxSize>
void SeqStack<T,MaxSize>::Push(T x)
{
	if (IsFull() == 1)
	{
		cerr<<"ÉÏÒç";
		exit(1);
	}
	top++;
	data[top] = x;
}

template <class T , int MaxSize>
T SeqStack<T,MaxSize>::Pop()
{
	if (top == -1)
	{
		cerr<<"ÏÂÒç";
		exit(1);
	}
	T x = data[top];
	top--;
	return x;
}

template <class T , int MaxSize>
T SeqStack<T,MaxSize>::Top()
{
	if (top == -1)
	{
		cerr<<"ÏÂÒç";
		exit(1);
	}
	return data[top];
}

template <class T , int MaxSize>
bool SeqStack<T,MaxSize>::IsEmpty()
{
	return (top == -1);
}

template <class T , int MaxSize>
bool SeqStack<T,MaxSize>::IsFull()
{
	return (top == MaxSize-1);
}

template <class T , int MaxSize>
void SeqStack<T,MaxSize>::Print()
{
	int t = top;
	while (t!=-1)
	{
		cout<<data[t]<<" ";
		t--;
	}
	cout<<endl;
}
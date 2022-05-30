#include <iostream>
#include "SeqList.h"

template<class T, int MAXSIZE>
SeqList<T, MAXSIZE>::SeqList()
{
	length = 0;
}

template<class T, int MAXSIZE>
SeqList<T, MAXSIZE>::SeqList(T a[], int n)
{
	if (n>MAXSIZE)
	{
		cerr<<"参数非法";
		exit(1);
	}
	length = n;
	for (int i = 0; i < n; i++)
	{
		data[i] = a[i];
	}
}

template<class T, int MAXSIZE>
int SeqList<T, MAXSIZE>::GetLength()
{
	return length;
}

template<class T, int MAXSIZE>
T& SeqList<T, MAXSIZE>::GetData(int t)
{
	if (t<1 || t>MAXSIZE)
		cerr<<"查找位置错误";
	return data[t-1];
}

template <class T,int MaxSize>
int SeqList<T,MaxSize>::Locate(T item)
{
	for(int i=0;i<length;i++)
		if(data[i]==item)
			return i+1;
	return -1;
}

template<class T, int MAXSIZE>
void SeqList<T, MAXSIZE>::Print()
{
	for (int i = 0;i < length; i++)
		cout<<data[i]<<endl;
}

template<class T, int MAXSIZE>
void SeqList<T, MAXSIZE>::Insert(int i , T l)
{
	if (i < 1 || i > length + 1)
	{
		cerr<<"插入位置非法";
		exit(1);
	}
	if (length > MAXSIZE)
	{
		cerr<<"上溢";
		exit(1);
	}
	for (int j = length - 1;j >= i-1 ; j--)
	{
		data[j+1] = data[j];
	}
	data[i-1] = l;
	length++;	
}
template<class T, int MAXSIZE>
T SeqList<T, MAXSIZE>::DeletePosition(int i)
{
	if (i < 1 || i > length + 1)
	{
		cerr<<"删除位置非法";
		exit(1);
	}
	if (length == 0)
	{
		cerr<<"下溢";
		exit(1);
	}
	T x = data[i - 1];
	for (int j = i - 1; j<length ; j++)
	{
		data[j]=data[j+1]; 
	}
	length--;
	return x;
}	

template<class T, int MAXSIZE>
void SeqList<T, MAXSIZE>::Sort()
{
	for (int i = 0;i < length; i++)
		for (int j = i + 1; j<length;j++)
			if (data[i]>data[j])
			{
				T temp = data[i];
				data[i] = data[j];
				data[j] = temp;
			}
}

	
template<class T, int MAXSIZE>
void SeqList<T, MAXSIZE>::Merge(SeqList &L)
{
	if (length+L.length > MAXSIZE)
	{
		cerr<<"上溢";
		exit(1);
	}
	for (int j = 0;j < L.length; j++)
	{
		for (int i=length-1 ; i >= 0 && data[i] > L.data[j];i--)
			data[i+1]=data[i];
		data[i+1]=L.data[j];
		length++;
	}
}

template<class T, int MAXSIZE>
T SeqList<T, MAXSIZE>::DeleteMin()
{
	if (length == 0)
	{
		cerr<<"下溢";
		exit(1);
	}
	T a=data[0];
	int num = 0;
	for (int i = 1;i<length ;i++)
		if (a>data[i])
		{
			a=data[i];
			num = i;
		}
	data[num] = data[length-1];
	return a;
}
template<class T, int MAXSIZE>
void SeqList<T, MAXSIZE>::DeleteItem(T item)
{
	for (int i = 0;i<length;i++)
	{
		if (data[i] == item)
		{
			this->DeletePosition(i+1);
			i--;
		}
	}
}
template<class T, int MAXSIZE>	
void SeqList<T, MAXSIZE>::DeleteItem(T s,T t)
{
	if (s > t)
	{
		cerr<<"输入数据错误";
		exit(1);
	}
	for (int i = 0;i<length;i++)
	{
		if (data[i] >= s && data[i] <= t)
			{
			this->DeletePosition(i+1);
			i--;
		}
	}
}
template<class T, int MAXSIZE>	
void SeqList<T,MAXSIZE>::DeleteRepeat()
{
	for (int i=0;i<length;i++)
	{
		for (int j = i+1; j<length;j++)
			if (data[i] == data[j])
			{
				this->DeletePosition(j+1);
				length--;
				j--;
			}
	}
}
template<class T, int MAXSIZE>
void SeqList<T,MAXSIZE>::ReSortList()
{
	T temp = data[0];
	for (int i=1;i<length;i++)
	{
		if (data[i]<temp)
		{
			T y=data[i];
			for (int j=i-1;j>=0;j--)
				data[j+1]=data[j];
			data[0]=y;
		}
	}
}

template<class T, int MAXSIZE>
void SeqList<T,MAXSIZE>::Switch(int l,int r)
{
	for (int i = l,j = r;i<=j;i++,j--)
	{
		T t = data[i];
		data[i] = data[j];
		data[j] = t;
	}
}

template<class T, int MAXSIZE>
void SeqList<T,MAXSIZE>::MoveLeft(int n)
{
	if (n<=0)
	{
		cerr<<"错误的输入！";
		exit(1);
	}
	Switch(0,n-1);
	Switch(n,length-1);
	Switch(0,length-1);
}
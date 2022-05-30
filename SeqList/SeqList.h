#ifndef SEQLIST_H
#define SEQLIST_H

template <class T, int MAXSIZE>

class SeqList 
{
private:
	T data[MAXSIZE];
	int length;
public:
	SeqList();
	SeqList(T a[],int max);		
	int GetLength();			//
	T GetData(int t);			//
	int GetPosition(T eg,T *b);	//		
	void Print();				//
	void Insert(int i, T data);	//
	T DeletePosition(int i);	//
	void Sort();				//
/**********************
//扩展用法
**************************/
	void Merge(SeqList &L);		//有序合并顺序表*
	T DeleteMin();				//从顺序表中删除具有最小值的元素并返回最小值，空出的位置由最后一个值填补
	void DeleteItem(T item);	//从顺序表中删除具有给定值item的所有元素*
	void DeleteItem(T s,T t);	//从有序顺序表中删除值在s~t之间的所有元素*
	void DeleteRepeat();		//删除一个顺序表中所有重复的元素，使所有元素的值均不相同*
	void ReSortList();			//重新排列顺序表，使得以a1为界线，前面比a1小，后面比a1大
	void MoveLeft(int p);
	void Switch(int l,int r);
};

#endif
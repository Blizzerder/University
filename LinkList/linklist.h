#ifndef LINKLIST_H
#define LINKLIST_H

template <class T>
struct Node
{
	T data;
	Node<T> *next;
};

template <class T>
class LinkList
{
private:
	Node<T> *head;
public:
	LinkList();				//默认构造函数
	LinkList(T a[],int n);	//带参构造函数
	~LinkList();			//析构函数
	int ListLength();		//链表长度
	T Get(int pos);			//按位查找
	int Locate(T item);		//按值查找
	void PrintLinkList();	//链表打印
	void Insert(int i, T item);//链表的插入
	T Delete(int i);		//链表的删除
	void Invert();			//链表的转置
	void Merge(LinkList &L1,LinkList &L2);
};

#endif
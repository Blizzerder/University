#include <iostream>
#include "linklist.h"
using namespace std;

template <class T>
LinkList<T>::LinkList()
{
	head = new Node<T>;
	head->next = NULL;
}

template <class T>
LinkList<T>::LinkList(T a[],int n)
{
	head = new Node<T>;
	head->next= NULL;
	
	for (int i = 0;i < n;i++)
	{
		Node<T> *p=new Node<T>;
		p->data = a[i];
		p->next = head->next;
		head->next = p;
	}
}

template <class T>
LinkList<T>::~LinkList()
{
	while (head!=NULL)
	{
		Node<T> * cur = new Node<T>;
		cur = head;
		head = head->next;
		delete cur;
	}
	//cout<<"链表已被析构"<<endl;
}

template <class T>
int LinkList<T>::ListLength()
{
	Node<T>  *cur ;
	int j = 0;
	cur = head->next;
	while (cur)
	{
		cur = cur->next;
		j++;
	}
	return j;
}

template <class T>
T& LinkList<T>::Get(int pos)
{
	Node<T> *cur = head->next;
	int j=1;
	while (j<pos&&cur)
	{
		j++;
		cur = cur->next;
	}
	if (j>pos||!cur)
	{
		cerr<<"查找位置非法";
		exit(1);
	}
	return cur->data;
}

template <class T>
int LinkList<T>::Locate(T item)
{
	Node<T> *p ;
	p = head->next;
	int j = 1;
	while (p&&p->data != item)
	{
		j++;
		p = p->next;
	}
	if (p)
		return j;
	return 0;
}

template <class T>
void LinkList<T>::PrintLinkList()
{
	Node<T> *p;
	p = head->next;
	while (p)
	{
		cout<<p->data<<endl;
		p = p->next;
	}
	cout<<endl;
}

template <class T>
void LinkList<T>::Insert(int i,T item)
{
	Node<T> *p;
	p = head;
	int j = 0;
	while (p&&j<i - 1)
	{
		j++;
		p=p->next;
	}
	if (!p||j>(i - 1))
	{
		cerr<<"插入位置非法";
		exit(1);
	}
	else
	{
		Node<T> *s = new Node<T>;
		s->data = item;
		s->next = p->next;
		p->next = s;
	}
}

template <class T>
T LinkList<T>::Delete(int i)
{
	Node<T> *p = head;
	int j = 0;
	while (p&&j<i-1)
	{
		j++;
		p = p->next;
	}
	if (!p||!p->next)
	{
		cerr<<"删除位置非法";
		exit(1);
	}
	else
	{
		Node<T> *q = p->next;
		T x = q->data;
		p->next = q->next;
		delete q;
		return x;
	}
}

template <class T>
void LinkList<T>::Invert()
{
	Node<T> *p = head->next;
	head->next = NULL;
	while (p)
	{
		Node<T> *q = p;
		p = p -> next;
		q -> next = head -> next;
		head -> next = q;
	}
}

template <class T>
void LinkList<T>::Merge(LinkList<T> &L1,LinkList<T> &L2)
{
	Node<T> *p1 = L1.head->next;
	Node<T> *p2 = L2.head->next;
	Node<T> *p3 = L1.head;
	while ( p1 && p2 )
	{
		if (p1->data < p2->data)
		{
			p3->next = p1;
			p1 = p1->next;
			p3 = p3->next;
		}
		else
		{
			p3->next = p2;
			p2 = p2->next;
			p3 = p3->next;
		}
	}
	if (p1 != NULL)
		p3->next = p1;
	if (p2 != NULL)
		p3->next = p2;
	delete L2.head;
	L2.head = NULL;
}
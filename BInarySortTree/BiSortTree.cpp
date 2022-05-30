#include <iostream>

using namespace std;

struct BiNode
{
	int key;
	BiNode *lchild,*rchild;
};

class BiSortTree
{
	BiNode *root;  //根节点
	void Insert(BiNode * &ptr,int k)     //在以ptr为根的二叉排序树中插入值为k的结点
	{
		if (ptr==NULL)
		{
			ptr = new BiNode;
			ptr->key = k;
			ptr->lchild = ptr->rchild = NULL;
		}
		else
		{
			if (k<ptr->key)
				Insert(ptr->lchild,k);
			else
				if (k>ptr->key)
					Insert(ptr->rchild,k);
		}
	}
	void Free(BiNode * p)
	{
		if (p = NULL)
			return;
		Free(p->lchild);
		Free(p->rchild);
		delete p;
	}
	BiNode * Search(BiNode * ptr,int k)
	{
		if (ptr == NULL)
			return NULL;
		else
			if (ptr->key == k)
				return ptr;
			else
				if (ptr->key > k)
					return Search(ptr->lchild,k);
				else
					return Search(ptr->rchild,k);
	}
	BiNode * Search2(BiNode * ptr,int k)
	{
		while (ptr)
		{
			if (k == ptr->key)
				return ptr;
			else if (k<ptr->key)
				ptr = ptr->lchild;
			else
				ptr = ptr->rchild;
		}
		return NULL;
	}
	void Delete(BiNode * &ptr , int k)
	{
		if (ptr!=NULL)
		{
			if (k<ptr->key)
				Delete(ptr->lchild,k);
			else
				if (k>ptr->key)
					Delete(ptr->rchild,k);
				else
				{
					if (ptr->lchild!= NULL && ptr->rchild!=	NULL)
					{
						BiNode * temp = ptr->lchild;
						while (temp->rchild != NULL)
							temp = temp->rchild;
						ptr->key = temp->key;
						Delete(ptr->lchild,temp->key);
					}
					else
					{
						BiNode * temp = ptr;
						if (ptr->lchild == NULL)
							ptr = ptr->rchild;
						else
							if (ptr->rchild == NULL)
								ptr = ptr->lchild;
							delete temp;
					}
				}
		}
	}
	void InOrder(BiNode * p)
	{
		if (p == NULL)
			return;
		InOrder(p->lchild);
		cout<<p->key<<" ";
		InOrder(p->rchild);
	}
public:
	BiSortTree(int a[],int n)   //建立二叉排序树
	{
		root = NULL;
		for (int i = 0;i<n;i++)
			Insert(root,a[i]);
	}
	~BiSortTree()
	{
		Free(root);
	}
	void Insert(int k)
	{
		Insert(root,k);	
	}
	bool Search(int k)
	{
		return Search(root,k)!= NULL;
	}
	bool Search2(int k)
	{
		return Search2(root,k)!=NULL;
	}
	void Delete(int k)
	{
		Delete(root,k);
	}
	void InOrder()
	{
		InOrder(root);
	}
};
#ifndef TREE_H_
#define TREE_H_
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <class T>
struct BiNode
{
	T data;
	BiNode<T> *lchild;
	BiNode<T> *rchild;
};

template <class T>
class BiTree
{
private:
	BiNode<T> * root;   // 根指针
	void PreOrder(BiNode<T>*p);
	void InOrder(BiNode<T>*p);
	void PostOrder(BiNode<T>*p);
	BiNode<T>* CreateByPre(vector<T> &pre, int &i);
	BiNode<T>* CreateByPreMid(vector<T> &pre , vector<T> &mid ,int ipre , int imid ,int n);
	BiNode<T>* Copy(BiNode<T> *p);
	void Free(BiNode<T>* p);
	int Count(BiNode<T>*p);
	int Height(BiNode<T>*p);
	BiNode<T>* Search(BiNode<T>* p,T e);
	BiNode<T>* SearchParent(BiNode<T>* p,BiNode<T>* child);
public:
	BiTree() { root = NULL; }				//无参构造函数，构造空树
	BiTree(vector<T> &pre);					//先序序列构造二叉树
	BiTree(vector<T> &pre,vector<T> &mid);	//先序中序构造二叉树
	BiTree(BiTree<T> &tree);				//拷贝构造函数
	~BiTree();								//析构函数
	void PreOrder();						//先序遍历
	void InOrder();							//中序遍历
	void PostOrder();						//后序遍历
	void LevelOrder();						//层序遍历
	int Count();							//统计结点个数
	int Height();							//计算二叉树的高度
	BiNode<T> *Search(T e);					//根据值e查找结点
	BiNode<T> *SearchParent(BiNode<T>* child);//查找指定节点的父节点
};

#endif
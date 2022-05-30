#ifndef MATRIX_H_
#define MATRIX_H_
#include<vector>
template<class T>
struct Triple						//定义三元素的成员结构
{
	int r,c;						//横坐标、纵坐标
	T elem;							//元素值
};

template<class T>  
class SparseMatrix	
{	
	vector< Triple<T> >triList;    //以三元为元素构造数组
	int rows,cols,num;				//行数，列数，个数
public:
	SparseMatrix();					//无参构造函数
	SparseMatrix(Triple<T> * tlist, int rs , int cs ,int n);		//有参构造函数
	void Trans1(SparseMatrix &B);
	void Trans2(SparseMatrix &B);
	SparseMatrix& plus(SparseMatrix &B);
	SparseMatrix& mult(SparseMatrix &B);
	void print();
};

#include <iostream>
#include "Matrix.cpp"
#include <vector>
using namespace std;

int main()
{
	int rs = 4,ls = 5;
	int Matrix[4][5] = {{0,0,0,3,0},
						{1,0,0,0,0},
						{0,0,5,0,0},
						{0,0,0,0,8}};
	int Matrix2[4][5] = {{0,0,0,3,0},
						{0,0,0,2,0},
						{0,0,3,0,0},
						{0,6,0,0,0}};
	
	int n = 0;
	vector< Triple<int> > s1,s2;
	for (int i = 0 ; i < rs ; i++)
		for (int j = 0 ; j < ls ; j++)
		{
			if (Matrix[i][j] != 0)
			{
				Triple<int> k;
				k.r = i;
				k.c = j;
				k.elem = Matrix[i][j];
				s1.insert(s1.begin()+n,k);
				n++;
			}
		}
	
	SparseMatrix<int> a(s1,rs,ls,n);
	n = 0;
	for (i = 0 ; i < rs ; i++)
		for (int j = 0 ; j < ls ; j++)
		{
			if (Matrix2[i][j] != 0)
			{
				Triple<int> k;
				k.r = i;
				k.c = j;
				k.elem = Matrix2[i][j];
				s2.insert(s2.begin()+n,k);
				n++;
			}
		}
	SparseMatrix<int> a2(s2,rs,ls,n);
	cout<<"转置前的矩阵s1为："<<endl;
	a.print();
	cout<<"转置前的矩阵s2为："<<endl;
	a2.print();
	SparseMatrix<int> b;
	cout<<"转置后的矩阵s1为："<<endl;
	a.Trans2(b);
	b.print();
	a=a.plus(a2);
	cout<<"s1,s2相加后的矩阵为："<<endl;
	a.print();
	return 0;
}
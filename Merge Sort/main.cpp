#include <iostream>
using namespace std;

void Merge(int r[],int r1[],int s,int m,int t)
{
	int i = s;
	int j = m+1;
	int k = s;
	while (i<=m&&j<= t)
		if (r[i]<= r[j])
			r1[k++]=r[i++];
		else
			r1[k++]=r[j++];
	if (i<=m)
		while (i<=m)
			r1[k++] = r[i++];
		else
			while (j<=t)
				r1[k++] = r[j++];
}

void MergePass(int r[],int r1[],int n,int h)
{
	int i = 1;
	while (i<=n-2*h+1)
	{
		Merge(r,r1,i,i+h-1,i+2*h-1);
		i+=2*h;
	}
	if (i<n - h +1)
		Merge(r,r1,i,i+h-1,n);
	else
		for (int k = i;k<=n;k++)
			r1[k] = r[k];
}

void MergeSort1(int r[],int n)
{
	int h = 1;
	int  r1[20] ;
	while (h<n)
	{
		MergePass(r,r1,n,h);
		h = 2*h;
		MergePass(r1,r,n,h);
		h = 2 * h;
	}
}

void MergeSort2(int r[],int r1[],int s,int t)
{
	int r2[20];
	if (s==t)
		r1[s]=r[s];
	else
	{
		int m = (s+t)/2;
		MergeSort2(r,r2,s,m);
		MergeSort2(r,r2,m+1,t);
		Merge(r2,r1,s,m,t);
	}
}

int main()
{
	int r[10] = {9,5,4,9,8,7,6,3,2,1};
	int r1[20];
	MergeSort2(r,r1,1,10);
	for (int i = 1;i<10;i++)
		cout<<r1[i]<<" ";
	return 0;
}
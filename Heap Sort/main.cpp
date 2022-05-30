#include <iostream>
using namespace std;

void Sift(int r[],int k ,int m)
{
	int i = k;
	int j = 2 * i;
	while (j<=m)
	{
		if (j<m&&r[j]<r[j+1])
			j++;
		if (r[i]>r[j])
			break;
		else
		{
			int temp = r[i];
			r[i] = r[j];
			r[j] = temp;
			i = j;
			j = 2 * i;
		}
	}
}

void HeapSort(int r[],int n)
{
	for (int i = n/2;i>=1;i--)
		Sift(r,i,n);
	for ( i = 1;i < n;i++)
	{
		int temp = r[1];
		r[1] = r[n-i+1];
		r[n-i+1] = temp;
		Sift(r,1,n-i);
	}
}

int main()
{
	int r[10] = {9,5,4,9,8,7,6,3,2,1};
	HeapSort(r,10);
	for (int i = 0;i<10;i++)
		cout<<r[i]<<" ";
	return 0;
}
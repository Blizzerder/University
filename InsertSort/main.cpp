#include <iostream>

using namespace std;

void InsertSort(int r[],int n)
{
	for (int i = 1 ; i < n ; i++)
	{
		int temp = r[i];
		for (int j = i - 1;j>=0&&temp<r[j];j--)
			r[j+1] = r[j];
		r[j+1] = temp;
	}
}

void BinInsertSort(int r[],int n)
{
	for (int i = 1 ; i < n ; i++)
	{
		int temp  = r[i];
		int low = 0;
		int high = i - 1;
		while (low <= high)
		{
			int mid = (low+high)/2;
			if (temp<r[mid])
				high = mid-1;
			else
				low = mid + 1;
		}
		for (int j = i-1;j>=low;j--)
			r[j+1] = r[j];
		r[low] = temp;
	}
}

int main()
{
	int a[10] = {1,4,5,7,8,2,3,6,9,10};
	int b[10] = {3,4,23,41,5,6,33,1,5,6};
	InsertSort(a,10);
	BinInsertSort(b,10);
	for (int i = 0;i<10;i++)
		cout<<a[i]<<" ";
	cout<<endl;
	for (i = 0;i<10;i++)
		cout<<b[i]<<" ";
	cout<<endl;
	return 0;
}
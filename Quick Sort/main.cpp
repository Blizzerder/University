#include <iostream>

using namespace std;

int Partition(int r[],int i,int j)
{
	int temp = r[i];
	while (i<j)
	{
		while ( i<j && r[j]>=temp)
			j--;
		if (i<j)
			r[i++] = r[j];
		while (i<j && r[i]<=temp)
			i++;
		if (i<j)
			r[j--] = r[i];
	}
	r[i] = temp;
	return i;
}

void QuickSort(int r[],int i,int j)
{
	if (i<j)
	{
		int pivot = Partition(r,i,j);
		QuickSort(r,i,pivot - 1);
		QuickSort(r,pivot + 1,j);
	}
}

int main()
{
	int n = 10;
	int a[10] = {2,1,5,6,9,8,3,7,10,4};
	QuickSort(a,0,n-1);
	for (int i = 0;i<n;i++)
		cout<<a[i]<<endl;
	return 0;
}
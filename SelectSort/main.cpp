#include <iostream>

using namespace std;

void SelectSort(int r[],int n)
{
	for (int i =0;i<n-1;i++)
	{
		int k = i;
		for (int j = i+1;j<n;j++)
			if (r[j]<r[k])
				k = j;
		if (k!=j)
		{
			int temp = r[i];
			r[i] = r[k];
			r[k] = temp;
		}
	}
}

int main()
{
	int a[10]={1,4,7,3,6,8,124,64,5,9};
	SelectSort(a,10);
	for (int i = 0;i<10;i++)
		cout<<a[i]<<" ";
	cout<<endl;
	return 0;
}
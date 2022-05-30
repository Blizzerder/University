#include <iostream>

using namespace std;

void ShellSort(int r[],int n)
{
	for (int d = n / 2 ; d >= 1 ; d = d/2)
	{
		for (int i = d;i<n;i++)
		{
			int temp = r[i];
			for (int j = i-d;j>=0&&temp<r[j];j = j-d)
				r[j+d] = r[j];
			r[j+d] = temp;
		}
	}
}

int main()
{
	int a[10] = {1,4,5,7,8,2,3,6,9,10};
	ShellSort(a,10);
	for (int i = 0;i<10;i++)
		cout<<a[i]<<" ";
	cout<<endl;
	return 0;
}
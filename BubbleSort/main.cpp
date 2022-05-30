
#include <iostream>

using namespace std;

int BubbleSort(int a[],int n)
{
	int t = 0;
	for (int i = 1;i<n;i++)
		for (int j = 0;j<n-i;j++)
		{
			t++;
			if (a[j]>a[j+1])
			{
				int temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	return t;
}

int BubbleSort1(int r[],int n)
{
	int t = 0;
	bool exchange = true;
	int i = 1;
	while (exchange)
	{
		exchange = false;
		for (int j = 0;j<n-i;j++)
		{
			t++;
			if (r[j]>r[j+1])
			{
				int temp = r[j];
				r[j] = r[j+1];
				r[j+1] = temp;
				exchange = true;
			}
		}
		i++;
	}
	return t;
}

int BubbleSort2(int a[],int n)
{
	int t = 0;
	int k = n-1;
	for (int i =0;i<n-1;i++)
	{
		int pos = 0;
		int flag = 0;
		for (int j = 0;j < k;j++)
		{
			t++;
			if (a[j]>a[j+1])
			{
				int temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
				flag = 1;
				pos = j;
			}
		}
		if (flag == 0)
			return t;

		k =pos;
	}
	return t;
}

int BubbleSort3(int a[],int n)
{
	int t = 0;
	int k = n-1;
	int s = 0; //双向遍历的截止值
	for (int i = 0;i < n-1;i++)
	{
		int pos = 0;
		int flag = 0;
		for (int j = s;j < k;j++)
		{
			t++;
			if (a[j]>a[j+1])
			{
				int temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
				flag = 1;
				pos = j;
			}
		}
		if (flag == 0)
			return t;
		k = pos;
		for (j = k;j>s;j--)
		{
			t++;
			if (a[j]<a[j-1])
			{
				int temp = a[j];
				a[j] = a[j-1];
				a[j-1] = temp;
				flag = 1;
			}
		}
		s++;
		if (flag == 0)
			return t;
	}
	return t;
}

int main()
{
	int n = 10;
	int a[10] = {2,1,7,9,5,6,4,8,10,3

};
	int a1[10] = {2,1,7,9,5,6,4,8,10,3

};
	int a2[10] = {2,1,7,9,5,6,4,8,10,3

};
	int a3[10] = {2,1,7,9,5,6,4,8,10,3

};
	cout<<BubbleSort(a,n)<<endl;
	cout<<BubbleSort1(a1,n)<<endl;
	cout<<BubbleSort2(a2,n)<<endl;
	cout<<BubbleSort3(a3,n)<<endl;
	return 0;
}
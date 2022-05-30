#include <iostream>
#include <string>
using namespace std;

int next[100] = {0};

void GetNext(string t)
{
	int j = 0 , k = -1;
	int m = t.length();
	next[0] = -1;
	while (j < m - 1)
	{
		if (k == -1 || t[j] == t[k])
		{
			k++;
			j++;
			next[j] = k;
		}
		else
			k = next[k];
	}
}

int KMPmatching(string s ,string t)
{
	int i = 0 , j = 0;
	int n = s.length() , m = t.length();
	while ( i < n && j < m)
	{
		if (j == -1 || s[i] == t[j])
		{
			i++;
			j++;
		}
		else
			j = next[j];
	}
	if (j >= m)
	{
		return i - m;
	}
	else
		return -1;
}

int main()
{
	cout<<"请输入两个字符串："<<endl;
	string s,t;
	cin>>s>>t;
	GetNext(t);
	int k = KMPmatching(s,t);
	cout<<t<<"在"<<s<<"中第一次出现的位置为:";
	cout<<k<<endl;
	return 0;
}
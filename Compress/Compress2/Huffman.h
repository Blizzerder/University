#include<iostream>
#include<fstream>
using namespace std;

const int MaxSize=512;
struct Node                          //哈夫曼树的结点
{
	int str;                            //记录字符在数组中的位置
	int weight;                         //字符出现频率
	int lchild,rchild,parent;           //哈夫曼树各个指针变量
	char bits[30];                 //存储哈夫曼编码的数组
};

class HuffmanTree
{
	Node hufftree[MaxSize];          //存放哈夫曼树结点的数组
	int num;                            //结点数
public:
	HuffmanTree(int w[],int s[],int n);
	void Select(int n,int &s1,int &s2);
	void Huffmancode(char wen[]);       //哈夫曼编码    
	void Huffmandecode();               //哈夫曼译码
};
void HuffmanTree::Select(int n,int &s1,int &s2)
{
	s1=-1;
	s2=-1;
	for(int i=0;i<=n;i++)
	{
		if(hufftree[i].parent==-1) 
		{
			if(s1==-1) {s1=i;continue;}
	        if(s2==-1) {s2=i;continue;}
	        if(hufftree[i].weight<hufftree[s1].weight)
				s1=i;
	        else if(hufftree[i].weight<hufftree[s2].weight)
				s2=i;
		}
	}
}

HuffmanTree::HuffmanTree(int w[],int s[],int n)
{ 
	num=n;
	int i1,i2;
	i1=i2=0;
	for(int i=0;i<2*num-1;i++)//外部叶子结点数为num个时，内部结点数为n-1，整个哈夫曼树的需要的结点数为2*num-1.
	{
		hufftree[i].parent=-1;
		hufftree[i].lchild=-1;
		hufftree[i].rchild=-1;
	}
	for(int j=0;j<num;j++)
	{
		hufftree[j].weight=w[j];
		hufftree[j].str=s[j];
	}
	for(int k=num;k<2*num-1;k++)           //构建哈夫曼树
	{
		Select(k-1,i1,i2);   //在hufftree中找权值最小的两个结点i1和i2 
		hufftree[i1].parent=k;
		hufftree[i2].parent=k;
		hufftree[k].weight=hufftree[i1].weight+hufftree[i2].weight;
		hufftree[k].lchild=i1;
		hufftree[k].rchild=i2;
	}
}

void HuffmanTree::Huffmancode(char wen[])
{
	ifstream in(wen);
	ofstream out("b.txt");
	int start=MaxSize-1;
	int cha=0;
	char cd[MaxSize];           //存放一个编码
	cd[MaxSize-1]='\0';
	for(int i=0;i<num;i++)      
	{
		start=MaxSize-1;
		int c,f;
		for(c=i,f=hufftree[i].parent;f!=-1;c=f,f=hufftree[f].parent)
		{
			if(hufftree[f].lchild==c)   //置左分支编码0
				cd[--start]='0';
			else cd[--start]='1';       //置右分支编码1
		}
		strcpy(hufftree[i].bits,&cd[start]);//将编码存放在相应结点存储哈夫曼编码的数组中
	}
    for(char ch;in.get(ch);)  //将A文件中各个字符转变成相应的编码，写入文件B
	{
		if((int)ch<0) cha=(int)ch+256;
		else cha=(int)ch;
		for(int j=0;j<num;j++)
			if(hufftree[j].str==cha)
				out<<hufftree[j].bits;
	}
}

void HuffmanTree::Huffmandecode()
{
	ifstream in("b.txt");
	ofstream out("c.txt");
	int i=2*num-2;
	for(char b;in>>b;)   
	{
		if(b=='0')i=hufftree[i].lchild;
		else i=hufftree[i].rchild;
		if(hufftree[i].lchild==-1)
		{
			out<<(char)hufftree[i].str;
			i=2*num-2;
		}
	}
}

void runhuffman(char wen[])
{
	ifstream in(wen);
	int w[MaxSize];
	int weight[MaxSize];   //存放各个字符的频率
	int str[MaxSize];      //存放A文件中各个字符在数组w中的位置(下标)
	int i=0;
	int n=0;
	int cha=0;
	for(int j=0;j<MaxSize;j++)
		w[j]=0;
	for(char ch;in.get(ch);)         
	{
		if((int)ch<0) cha=(int)ch+256;   //中文的ASCII码值为负数，加上256使其可以存放在数组中
		else cha=(int)ch;
		w[cha]++;
	}
	for(int k=0;k<MaxSize;k++)
		if(w[k]!=0)
		{
			str[n]=k;
			weight[n]=w[k];
			n++;
		}
	HuffmanTree h(weight,str,n);  //构造哈夫曼树
	h.Huffmancode(wen);           //利用哈夫曼树进行文件压缩及解压
	h.Huffmandecode();
}

int compare(char wen[])
{
	ifstream ina(wen);
	ifstream inc("3.txt");
    char stringa[100000];
	int i=0;
	int flag=0;
	char stringc[100000];
	int j=0;
	int n = 0;
	char cha,chc;
	while (ina>>cha&&inc>>chc)
	{
		if (cha != chc)
			return  0;
	}
	return 1;
}
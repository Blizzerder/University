#include<iostream>
#include"Huffman.h"
using namespace std;

void runhuffman(char wen[]);
void compare(char wen[]);

void main()
{
	cout<<"**************************************"<<endl;
	cout<<"               压缩软件               "<<endl;
	cout<<"**************************************"<<endl;
	int c=1;
	char wenjian[20];
	while(c!=0)
	{
		cout<<"1.输入操作文件名"<<endl;
		cout<<"2.压缩并解压文件"<<endl;
		cout<<"3.比较文件"<<endl;
		cout<<"0.退出"<<endl;
		cout<<"请选择你要执行的操作：";
		cin>>c;
		switch(c)
		{
			case 1:cout<<"操作文件名为：";
				   cin>>wenjian;cout<<endl;break;
		    case 2:runhuffman(wenjian);cout<<endl;break;
			case 3:compare(wenjian);break;
			case 0:break;
     	    default:cout<<"您选择的操作码错误，请重新选择。"<<endl;
	
		};

	}

	cout<<"**************************************"<<endl;
	cout<<"                 感谢使用             "<<endl;
	cout<<"**************************************"<<endl;
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

void compare(char wen[])
{
	ifstream ina(wen);
	ifstream inc("c.txt");
    char stringa[100000];
	int i=0;
	int flag=0;
	char stringc[100000];
	int j=0;
    for(char cha;ina>>cha;)    //将文件A的内容读入数组stringa[]
	{
		stringa[i]=cha;
		i++;
	}
	stringa[i]='\0';
	for(char chc;inc>>chc;)    //将文件C的内容读入数组stringc[]
	{
		stringc[j]=chc;
		j++;
	}
	stringc[j]='\0';
	for(int k=0;stringa[k]!='\0'&&stringc[k]!='\0';k++)  
	if(stringa[k]!=stringc[k]) flag=0;
	if(stringa[k]=='\0'&&stringc[k]=='\0') flag=1;
	else flag=0;
    if(flag==0)
		cout<<"A文件与C文件不相同，压缩软件错误！"<<endl;
	else
		cout<<"A文件与C文件相同，压缩软件正确！"<<endl;
}
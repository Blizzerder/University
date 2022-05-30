#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "stdafx.h"
using namespace std;

struct Element
{
	unsigned char ch;
	unsigned long weight;
};

struct Node
{
	unsigned char ch;
	unsigned long weight;
	char* code;
	int parent,lchild,rchild;
};

class FileTree
{
private:
	vector<Node> hufftree;
	unsigned int char_kinds;
	unsigned int Element_num;
	unsigned long file_len;
public:
	void SelectSmall(int &least,int &less,unsigned int n)
	{
		unsigned int i;
		unsigned long min=ULONG_MAX;
		for(i=0;i<n;i++)
			if(hufftree[i].parent==-1 && hufftree[i].weight<min)
			{
				min=hufftree[i].weight;
				least=i;
			}
		hufftree[least].parent=-2;
		min=ULONG_MAX;
		for(i=0;i<n;i++)
			if(hufftree[i].parent==-1 && hufftree[i].weight<min)
			{
				min=hufftree[i].weight;
				less=i;
			}
	}
	void setData(Element *Elements)
	{	
		unsigned int i;
		Element_num=2*char_kinds-1;
		hufftree.resize(Element_num);
		for(i=0;i<char_kinds;i++)
		{
			hufftree[i].ch=Elements[i].ch;
			hufftree[i].weight=Elements[i].weight;
			hufftree[i].parent=hufftree[i].lchild=hufftree[i].rchild=-1;
		}
		for(i=char_kinds;i<Element_num;i++)
			hufftree[i].parent=-1;
		int least,less;
		for(i=char_kinds;i<Element_num;i++)
		{
			SelectSmall(least,less,i);
			hufftree[least].parent=hufftree[less].parent=i;
			hufftree[i].lchild=least;
			hufftree[i].rchild=less;
			hufftree[i].weight=hufftree[least].weight+hufftree[less].weight;
		}
	}
	void EnCode()
	{
		unsigned int i;
		int cur,next,index;
		char *code_temp=new char[256];
		code_temp[255]='\0';

		for(i=0;i<char_kinds;i++)
		{
			index=255;
			for(cur=i,next=hufftree[i].parent; next!=-1;cur=next,next=hufftree[next].parent)
				if(hufftree[next].lchild==cur)
					code_temp[--index]='0';
				else
					code_temp[--index]='1';
			hufftree[i].code=new char[256-index];
			strcpy(hufftree[i].code,&code_temp[index]);
		}
		delete []code_temp;
	}
	int compress(char *inName,char *outName)
	{
		unsigned int i,j;
		unsigned char char_temp;
		file_len=0;
		FILE *in,*out;
		Element Element_temp;
		char code_buf[256]="\0";
		unsigned int code_len;

		Element *Elements=new Element[256];

		for(i=0;i<256;i++)
		{
			Elements[i].weight=0;
			Elements[i].ch=(unsigned char)i;
		}

		in=fopen(inName,"rb");
		if(in==NULL)
			return -1;
		fread((char *)&char_temp,sizeof(unsigned char),1,in);
		while(!feof(in))
		{
			++Elements[char_temp].weight;
			++file_len;
			fread((char *)&char_temp,sizeof(unsigned char),1,in);
		}
		fclose(in);

		for(i=0;i<256-1;i++)
			for(j=i+1;j<256;j++)
				if(Elements[i].weight<Elements[j].weight)
				{
					Element_temp=Elements[i];
					Elements[i]=Elements[j];
					Elements[j]=Element_temp;
				}
					
		for(i=0;i<256;i++)
			if(Elements[i].weight==0)
				break;
			
		char_kinds=i;
			
		if(char_kinds==1)
		{
			out=fopen(outName,"wb");
			fwrite((char *)&char_kinds,sizeof(unsigned int),1,out);
			fwrite((char *)&Elements[0].ch,sizeof(unsigned char),1,out);
			fwrite((char *)&Elements[0].weight,sizeof(unsigned long),1,out);

			delete []Elements;
			fclose(out);
		}
		else
		{
			setData(Elements);
			delete []Elements;
			EnCode();
				
			out=fopen(outName,"wb");
			fwrite((char *)&char_kinds,sizeof(unsigned int),1,out);

			for(i=0;i<char_kinds;i++)
			{
				fwrite((char *)&hufftree[i].ch,sizeof(unsigned char),1,out);
				fwrite((char *)&hufftree[i].weight,sizeof(unsigned long),1,out);
			}
				
			fwrite((char *)&file_len,sizeof(unsigned long),1,out);
			in=fopen(inName,"rb");
			fread((char *)&char_temp,sizeof(unsigned char),1,in);
				
			while(!feof(in))
			{
				for(i=0;i<char_kinds;i++)
					if(char_temp == hufftree[i].ch)
						strcat(code_buf,hufftree[i].code);
				while(strlen(code_buf)>=8)
				{
					char_temp='\0';
					for(i=0;i<8;i++)
					{
						char_temp<<=1;
						if(code_buf[i]=='1')
							char_temp|=1;
					}
					fwrite((char *)&char_temp,sizeof(unsigned char),1,out);
					strcpy(code_buf,code_buf+8);
				}
				fread((char *)&char_temp,sizeof(unsigned char),1,in);
			}
			code_len=strlen(code_buf);
			if(code_len>0)
			{
				char_temp='\0';
				for(i=0;i<code_len;i++)
				{
					char_temp<<=1;
					if(code_buf[i]=='1')
						char_temp|=1;
				}
				char_temp<<=8-code_len;
				fwrite((char *)&char_temp,sizeof(unsigned char),1,out);
			}
			fclose(in);
			fclose(out);
		}
		return 1;
	}

int uncompress(char *inName,char *outName)
{
	unsigned int i;
	unsigned long writen_len=0;
	FILE *in,*out;
	unsigned code_temp;
	unsigned int root;

	in=fopen(inName,"rb");
	if(in==NULL)
		return -1;

	fread((char *)&char_kinds,sizeof(unsigned int),1,in);
	if(char_kinds==1)	
	{
		fread((char *)&code_temp,sizeof(unsigned char),1,in);
		fread((char *)&file_len,sizeof(unsigned long),1,in);
		out=fopen(outName,"wb");
		while(file_len--)
			fwrite((char *)&code_temp,sizeof(unsigned char),1,out);
		fclose(in);
		fclose(out);
	}
	else
	{
		Element_num=2*char_kinds-1;
		Element *Elements=new Element[Element_num];
		for(i=0;i<char_kinds;i++)
		{
			fread((char *)&Elements[i].ch,sizeof(unsigned char),1,in);
			fread((char *)&Elements[i].weight,sizeof(unsigned long),1,in);
		}
		setData(Elements);
		delete []Elements;

		fread((char *)&file_len,sizeof(unsigned long),1,in);
		out=fopen(outName,"wb");
		root=Element_num-1;
		while(1)
		{
			fread((char *)&code_temp,sizeof(unsigned char),1,in);

			for(i=0;i<8;i++)
			{
				if(code_temp & 128)
					root=hufftree[root].rchild;
				else
					root=hufftree[root].lchild;

				if(root<char_kinds)
				{
					fwrite((char *)&hufftree[root].ch,sizeof(unsigned char),1,out);
					++writen_len;
					if(writen_len==file_len)	break;
					root=Element_num-1;
				}
				code_temp<<=1;
			}
			if(writen_len==file_len)	break;
		}
		fclose(in);
		fclose(out);
	}
	return 1;
}
};
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
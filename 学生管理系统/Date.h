#ifndef DATE_H
#define DATE_H
#include <string>
#include <iostream>
using namespace std;

class Date
{
	int year;
	int month;
	int day;
public:
	Date(){}
	Date(int y,int m,int d)
	{
		year = y;
		month = m;
		day = d;
	}
	void init_date(int y,int m,int d)
	{
		year = y;
		month = m;
		day = d;
	}
	void init_date(Date d)
	{
		year = d.year;
		month = d.month;
		day = d.day;
	}
	void print()
	{
		cout<<year<<"/"<<month<<"/"<<day;
	}
};

#endif 
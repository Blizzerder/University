#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <iostream>
#include "Date.h"
using namespace std;



class Student
{
	int ID;
	string name;
	char sex;
	string major;
	Date birthday;
public:
	Student();
	Student(int ID , string name , char sex , string major , int year ,int month , int day);
	Student(int ID);
	void print();

	Student operator = (const Student &g);
	bool operator == (const Student &g);
	bool operator != (const Student &g);
	friend ostream & operator << (ostream &io , Student &g);
	friend istream & operator >> (istream &io , Student &g);
	

	int GetID();
	string GetName();
	char GetSex();
	string GetMajor();
	Date GetBirthday();

	void SetID(int id);
	void SetName(string name);
	void SetSex(char sex);
	void SetMajor(string major);
	void SetBirthday(int year , int month , int day);
};

#endif
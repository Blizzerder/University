#include "Student.h"
#include "Date.h"
#include <iostream>
#include <iomanip>

using namespace std;

Student::Student()
{}

Student::Student(int ID , string name , char sex , string major , int year ,int month , int day)
{
	this -> ID = ID;
	this -> name = name;
	this -> sex = sex;
	this -> major = major;
	birthday.init_date(year , month , day);
}

Student::Student(int ID)
{
	this -> ID = ID;
}

Student Student::operator =(const Student &g)
{
	this -> ID = g.ID;
	this -> name = g.name;
	this -> sex = g.sex;
	this -> major = g.major;
	birthday.init_date(g.birthday);
	return *this;
}

bool Student::operator ==(const Student &g)
{
	return (ID == g.ID);
}

bool Student::operator !=(const Student &g)
{
	return (ID != g.ID);
}

ostream & operator << (ostream &io , Student &g)
{
	io<<setw(5)<<g.ID<<setw(15)<<g.name<<setw(15)<<g.sex<<setw(20)<<g.major<<setw(15);
	g.birthday.print();
	return io;	
}

istream & operator >> (istream &io , Student &g)
{
	int year,month,day;
	io>>g.ID>>g.name>>g.sex>>g.major>>year>>month>>day;
	g.birthday.init_date(year,month,day);
	return io;
}

int Student::GetID()
{
	return ID;
}

string Student::GetName()
{
	return name;
}

char Student::GetSex()
{
	return sex;
}

string Student::GetMajor()
{
	return major;
}

Date Student::GetBirthday()
{
	return birthday;
}

void Student::SetID(int id)
{
	ID = id;
}

void Student::SetName(string name)
{
	this -> name = name;
}

void Student::SetSex(char sex)
{
	this -> sex = sex;
}

void Student::SetMajor(string major)
{
	this -> major = major;
}

void Student::SetBirthday(int year , int month , int day)
{
	birthday.init_date(year , month , day);
}

void Student::print()
{
	cout<<setw(5)<<ID<<setw(15)<<name<<setw(15)<<sex<<setw(20)<<major<<setw(15);
	birthday.print();
	cout<<endl;
}
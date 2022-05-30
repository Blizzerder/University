#include "Goods.h"
#include <iostream>
#include <iomanip>

Goods::Goods()
{
	
}

Goods::Goods(int ID,string name,float price,int stock)
{
	this->ID = ID;
	Name = name;
	Price = price;
	Stock = stock;
}

Goods Goods::operator = (const Goods &g)
{
	this->ID = g.ID;
	this->Name = g.Name;
	this->Price = g.Price;
	this->Stock = g.Stock;
	return *this;
}

bool Goods::operator > (const Goods &g)
{
	return (this->ID > g.ID);
}

bool Goods::operator == (const Goods &g)
{
	return (this->ID == g.ID);
}

ostream & operator << (ostream &io,Goods &g)
{
	io<<setw(5)<<g.ID<<setw(15)<<g.Name<<setw(15)<<g.Price<<setw(15)<<g.Stock;
	return io;
}

istream & operator >>(istream &io,Goods &g)
{
	io>>g.ID>>g.Name>>g.Price>>g.Stock;
	return io;
}

int Goods::GetID()
{
	return ID;
}

string Goods::GetName()
{
	return Name;
}

float Goods::GetPrice()
{
	return Price;
}

int Goods::GetStock()
{
	return Stock;
}

void Goods::SetID(int id)
{
	if (id < 0)
	{
		cerr<<"ÊäÈë±àºÅÓÐÎó£¡";
		exit(1);
	}
	ID = id;
}
void Goods::SetName(string name)
{
	Name = name;
}
void Goods::SetPrice(float price)
{
	Price = price;
}
void Goods::SetStock(int stock)
{
	Stock = stock;
}
#ifndef GOODS_H
#define GOODS_H
#include <string>
using namespace std;

class Goods
{
	int ID;			//商品编号
	string Name;	//商品名称
	float Price;	//商品价格
	int Stock;		//商品库存
public:
	Goods();
	Goods(int ID,string name,float price,int stock);
	Goods(int ID);

	Goods operator = (const Goods &g);
	bool operator > (const Goods &g);
	bool operator == (const Goods &g);
	friend ostream & operator << (ostream &io , Goods &g);
	friend istream & operator >> (istream &io , Goods &g);

	int GetID();
	string GetName();
	float GetPrice();
	int GetStock();

	void SetID(int id);
	void SetName(string name);
	void SetPrice(float price);
	void SetStock(int stock);
};

#endif
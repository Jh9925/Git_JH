#pragma once

#include<iostream>
#include<vector>
#include<Windows.h>

using namespace std;

class Item
{
private:
	// 장비 필요한거
	int Id;
	string Name;
	int Price = 0;
	int Hp = 0;
	int Atk = 0;
	int Def = 0;


public:
	Item(const int id, const string& name, const int price, const int hp, const int atk, const int def);
	virtual~Item();


	void PrintInfo_Item();

	// Get

	int I_GetId(); 
	string I_GetName();
	int I_GetPrice();
	int I_GetHp()const;
	int I_GetAtk()const;
	int I_GetDef()const;




};


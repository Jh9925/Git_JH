#pragma once

#include<iostream>
#include<vector>
#include<Windows.h>
#include "Equip.h"


using namespace std;

class Unit_Base
{
private:
	// 캐릭터 필요한거
	string Name=0;
	int Gold=0;
	int Hp=0;
	int Atk=0;
	int Def=0;
	
	// 플레이어 인벤토리 벡터
	vector<Item>Player_Inven;

	// 플레이어 장비창 벡터
	vector<Item>Player_EqipSlot;


public:
	Unit_Base(const string& name, const int gold, const int hp, const int atk, const int def);
	virtual~Unit_Base();


	void PrintInfo_Unit();

	// Get
	string GetName(); 
	int GetGold();
	int GetHp();
	int GetAtk();
	int GetDef();

	



	// Set


	



	// gold
	void addGold(int amount);		// { Gold += amount; }
	void subtractGold(int amount);  // { Gold -= amount; }

	// Hp
	void addHp();
	void subtractHp();

	// Atk
	void addAtk();
	void subtractAtk();

	// Def
	void addDef();
	void subtractDef();


	//add item
	// 상점에서 사기
	void BuyItem(Equip& item);
	// 상점에 팔기
	void SellItem(string& itemName);
	// 인벤에서 장비창으로 장착
	void addItem(string& itemName);
	// 장비창에서 해제 인벤으로
	void removeItem(string& itemName);



	void printInven();

};


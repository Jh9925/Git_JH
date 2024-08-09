#pragma once

#include<iostream>
#include<vector>
#include<Windows.h>
#include "Equip.h"


using namespace std;

class Unit_Base
{
private:
	// ĳ���� �ʿ��Ѱ�
	string Name=0;
	int Gold=0;
	int Hp=0;
	int Atk=0;
	int Def=0;
	
	// �÷��̾� �κ��丮 ����
	vector<Item>Player_Inven;

	// �÷��̾� ���â ����
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
	// �������� ���
	void BuyItem(Equip& item);
	// ������ �ȱ�
	void SellItem(string& itemName);
	// �κ����� ���â���� ����
	void addItem(string& itemName);
	// ���â���� ���� �κ�����
	void removeItem(string& itemName);



	void printInven();

};


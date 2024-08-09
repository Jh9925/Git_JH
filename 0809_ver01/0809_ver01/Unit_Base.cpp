#include "Unit_Base.h"
#include "GameScene.h"


Unit_Base::Unit_Base(const string& name, const int gold, const int hp, const int atk, const int def)
	:Name(name), Gold(gold), Hp(hp), Atk(atk), Def(def)
{
}

Unit_Base::~Unit_Base()
{
}

void Unit_Base::PrintInfo_Unit()
{
	cout << "==========================================" << endl;
	cout << GetName() << " 소지금: " << GetGold() << endl;
	cout << " 체력: " << GetHp() << ", 공격력: " << GetAtk() << ", 방어력: " << GetDef() << endl;
	cout << "==========================================" << endl;
}

string Unit_Base::GetName()
{
	return Name;
}

int Unit_Base::GetGold()
{
	return Gold;
}

int Unit_Base::GetHp()
{
	return Hp;
}

int Unit_Base::GetAtk()
{
	return Atk;
}

int Unit_Base::GetDef()
{
	return Def;
}

void Unit_Base::addGold(int amount)
{
	Gold += amount;
}

void Unit_Base::subtractGold(int amount)
{
	Gold -= amount;
}

void Unit_Base::addHp()
{
	for (const auto& slot : Player_EqipSlot)
	{
		Hp += slot.I_GetHp();
	}
}

void Unit_Base::subtractHp()
{
	for (const auto& slot : Player_EqipSlot)
	{
		Hp -= slot.I_GetHp();
	}
}

// 장비창에 있는 아이템의 공격력 합산.
void Unit_Base::addAtk()
{
	for (const auto& slot : Player_EqipSlot)
	{
		Atk += slot.I_GetAtk();
	}
}


void Unit_Base::subtractAtk()
{
	for (const auto& slot : Player_EqipSlot)
	{
		Atk -= slot.I_GetAtk();
	}
}


void Unit_Base::addDef()
{
	for (const auto& slot : Player_EqipSlot)
	{
		Def += slot.I_GetDef();
	}
}


void Unit_Base::subtractDef()
{
	for (const auto& slot : Player_EqipSlot)
	{
		Def -= slot.I_GetDef();
	}
}

// 상점에서 사기 인벤으로
void Unit_Base::BuyItem(Equip& itemName)
{
	Player_Inven.push_back(itemName);
	Gold = Gold - itemName.I_GetPrice();
}
// 인벤에서 상점에 팔기
void Unit_Base::SellItem(string& itemName)
{
	for (auto it = Player_Inven.begin(); it != Player_Inven.end(); it++)
	{
		if (it->I_GetName() == itemName)
		{
			Gold = Gold + (it->I_GetPrice() / 2);
			Player_Inven.erase(it);
			
			break;
		}
	}

}
// 인벤에서 장비슬롯으로 장착
void Unit_Base::addItem(string& itemName)
{
	for (auto it = Player_Inven.begin(); it != Player_Inven.end(); it++)
	{
		if (it->I_GetName() == itemName)
		{
			// 장비슬롯으로 보내고
			Player_EqipSlot.push_back(*it);
			// 인벤에서 지우기
			Player_Inven.erase(it);
			break;
		}
	}
}
// 장비슬롯에서 인벤으로 장비 해제
void Unit_Base::removeItem(string& itemName)
{
	for (auto it = Player_EqipSlot.begin(); it != Player_EqipSlot.end(); it++)
	{
		if (it->I_GetName() == itemName)
		{
			// 인벤으로 보내고
			Player_Inven.push_back(*it);
			// 장비슬롯에서 지우기
			Player_EqipSlot.erase(it);
			
			break;
		}
	}
}

// 인벤에있는 장비 출력
void Unit_Base::printInven()
{
	cout << " 인벤토리 : " << endl;
	for (auto& item : Player_Inven)
	{
		cout << item.I_GetName()<< "  체력: "<< item.I_GetHp() << "	공격력 : " << item.I_GetAtk() << "	방어력 : " << item.I_GetDef() << endl;
	}
}

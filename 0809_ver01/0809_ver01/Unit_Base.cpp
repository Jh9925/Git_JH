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
	cout << GetName() << " ������: " << GetGold() << endl;
	cout << " ü��: " << GetHp() << ", ���ݷ�: " << GetAtk() << ", ����: " << GetDef() << endl;
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

// ���â�� �ִ� �������� ���ݷ� �ջ�.
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

// �������� ��� �κ�����
void Unit_Base::BuyItem(Equip& itemName)
{
	Player_Inven.push_back(itemName);
	Gold = Gold - itemName.I_GetPrice();
}
// �κ����� ������ �ȱ�
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
// �κ����� ��񽽷����� ����
void Unit_Base::addItem(string& itemName)
{
	for (auto it = Player_Inven.begin(); it != Player_Inven.end(); it++)
	{
		if (it->I_GetName() == itemName)
		{
			// ��񽽷����� ������
			Player_EqipSlot.push_back(*it);
			// �κ����� �����
			Player_Inven.erase(it);
			break;
		}
	}
}
// ��񽽷Կ��� �κ����� ��� ����
void Unit_Base::removeItem(string& itemName)
{
	for (auto it = Player_EqipSlot.begin(); it != Player_EqipSlot.end(); it++)
	{
		if (it->I_GetName() == itemName)
		{
			// �κ����� ������
			Player_Inven.push_back(*it);
			// ��񽽷Կ��� �����
			Player_EqipSlot.erase(it);
			
			break;
		}
	}
}

// �κ����ִ� ��� ���
void Unit_Base::printInven()
{
	cout << " �κ��丮 : " << endl;
	for (auto& item : Player_Inven)
	{
		cout << item.I_GetName()<< "  ü��: "<< item.I_GetHp() << "	���ݷ� : " << item.I_GetAtk() << "	���� : " << item.I_GetDef() << endl;
	}
}

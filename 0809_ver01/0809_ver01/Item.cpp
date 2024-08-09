#include "Item.h"


Item::Item(const int id, const string& name, const int price, const int hp, const int atk, const int def)
    :Id(id), Name(name), Price(price), Hp(hp), Atk(atk), Def(def)
{
}

Item::~Item()
{
}

void Item::PrintInfo_Item()
{
    cout << "==========================================" << endl;
    cout << I_GetId() <<" | " << I_GetName() << " 가격: " << I_GetPrice() << endl;
    cout << " 체력: " << I_GetHp() << ", 공격력: " << I_GetAtk() << ", 방어력: " << I_GetDef() << endl;
    cout << "==========================================" << endl;
}

int Item::I_GetId()
{
    return Id;
}

string Item::I_GetName()
{
    return Name;
}

int Item::I_GetPrice()
{
    return Price;
}

int Item::I_GetHp()const
{
    return Hp;
}

int Item::I_GetAtk()const
{
    return Atk;
}

int Item::I_GetDef()const
{
    return Def;
}

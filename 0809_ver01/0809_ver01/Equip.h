#pragma once

#include "Item.h"

class Equip : public Item
{
public:
	Equip(const int id, const string& name, const int price, const int hp, const int atk, const int def);

};


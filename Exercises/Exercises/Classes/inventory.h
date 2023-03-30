#pragma once

#include <vector>

#include "item.h"

class Inventory
{
public:
	Inventory();
	~Inventory();

	void AddItem(Item &item);
	void RemoveItem(Item &item);
	void RemoveItemAtIndex(int index);

	Item *GetItem(Item &item);
	Item *GetItemAtIndex(int index);

	int GetItemCount() { return m_items.size(); }

private:
	std::vector<Item> m_items;

};

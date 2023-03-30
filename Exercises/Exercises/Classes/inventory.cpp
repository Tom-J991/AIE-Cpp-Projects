#include "inventory.h"

#include <algorithm>

Inventory::Inventory()
	: m_items(std::vector<Item>())
{ }
Inventory::~Inventory()
{ }

void Inventory::AddItem(Item &item)
{
	m_items.push_back(item);
}
void Inventory::RemoveItemAtIndex(int index)
{
	m_items.erase(m_items.begin() + index);
}
Item *Inventory::GetItemAtIndex(int index)
{
	return &m_items[index];
}

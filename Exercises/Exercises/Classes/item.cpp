#include "item.h"

Item::Item(const char* name, float weight, int stackCount, bool stackable)
	: m_name(name)
	, m_weight(weight)
	, m_stackCount(stackCount)
	, m_stackable(stackable)
{ }
Item::~Item()
{ }

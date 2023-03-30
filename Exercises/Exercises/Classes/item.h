#pragma once

class Item
{
public:
	Item(const char* name, float weight, int stackCount, bool stackable);
	~Item();

	const char* GetName() { return m_name; }

	void SetWeight(float weight) { this->m_weight = weight; }
	float GetWeight() { return m_weight; }

	void SetStackCount(int stackCount) { this->m_stackCount = stackCount; }
	int GetStackCount() { return m_stackCount; }

	void SetStackable(bool stackable) { this->m_stackable = stackable; }
	bool IsStackable() { return m_stackable; }

private:
	const char* m_name;
	float m_weight;
	int m_stackCount;
	bool m_stackable;

};

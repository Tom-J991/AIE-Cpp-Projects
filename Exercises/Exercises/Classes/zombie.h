#pragma once

class Zombie
{
public:
	Zombie(float health, float attack);
	~Zombie();

	void Damage(float damage);

	float GetHealth() { return m_health; }
	float GetAttack() { return m_attack; }

private:
	float m_health;
	float m_attack;

};

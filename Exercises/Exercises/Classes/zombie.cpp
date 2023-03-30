#include "zombie.h"

Zombie::Zombie(float health, float attack)
	: m_health(health)
	, m_attack(attack)
{ }
Zombie::~Zombie()
{ }

void Zombie::Damage(float damage)
{
	m_health -= damage;
}

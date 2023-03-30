#include <iostream>
#include <memory>

#include "item.h"
#include "inventory.h"
#include "zombie.h"

int main()
{
	std::shared_ptr<Zombie> zombie = std::make_shared<Zombie>(1.0f, 1.5f);
	std::cout << zombie->GetHealth() << std::endl;
	std::cout << zombie->GetAttack() << std::endl;

	std::shared_ptr<Item> glock = std::make_shared<Item>("Glock", 8.0f, 1, false);
	std::shared_ptr<Item> medkit = std::make_shared<Item>("Medkit", 2.5f, 1, false);
	
	std::unique_ptr<Inventory> inventory = std::make_unique<Inventory>();
	inventory->AddItem(*glock);
	inventory->AddItem(*medkit);
	
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			int index = y * 8 + x;
			if (index > inventory->GetItemCount()-1)
			{
				std::cout << "[ ]";
			}
			else
			{
				auto i = inventory->GetItemAtIndex(index);
				std::cout << "[" << i->GetName() << "]";
			}
		}
		std::cout << std::endl;
	}

	std::cin.ignore();

	return 0;
}
// PointerExercise.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Monster.h"
#include <iostream>
#include <conio.h>

void AttackMonster(Monster* defender, Monster* attacker);
void DisplayMonsterHealth(Monster* m);

int main()
{
    //Create monsters
    Monster dragon{ "Dragon", 200, 20 };
    Monster vampire{ "Vampire", 150, 10 };
    Monster zombie{ "Zombie", 50, 8 };
    Monster impossibleSlime{ "Impossible Slime", 5000, 500 };

    //create player
    Monster fighter{ "Fighter", 100, 25 };
    Monster barbarian{ "Barbarian", 150, 12 };
    Monster rogue{ "Rogue", 50, 33 };

    //pick a random enemy
    Monster* currentEnemy;
    srand(time(0)); //this generate a random seed
    int r = rand() % 3; //this generates a random number between 0-3 exclusive
    switch (r)
    {
        case 0: currentEnemy = &dragon; break;
        case 1: currentEnemy = &vampire; break;
        case 2: currentEnemy = &zombie; break;

            //without a default, C++ assumes the possibility that current is never assigned
            // and therefore returning an error later when we try to access it
        default: currentEnemy = &impossibleSlime; break;
    }

    //pick a random player
    Monster *currentPlayer;
    srand(time(0)); //this generate a random seed
    r = rand() % 3; //this generates a random number between 0-3 exclusive
    switch (r)
    {
    case 0: currentPlayer = &fighter; break;
    case 1: currentPlayer = &barbarian; break;
    case 2: currentPlayer = &rogue; break;

        //without a default, C++ assumes the possibility that current is never assigned
        // and therefore returning an error later when we try to access it
    default: currentPlayer = &fighter; break;
    }

    //fight until someone is defeated
    while (currentEnemy->health > 0 && currentPlayer->health > 0)
    {
        //player attacks current monster
        AttackMonster(currentEnemy, currentPlayer);
        DisplayMonsterHealth(currentEnemy);

        //wait for input then clear screen
        std::cin.ignore();
        system("cls");

        //current monster attacks player
        AttackMonster(currentPlayer, currentEnemy);
        DisplayMonsterHealth(currentPlayer);

        //wait for input then clear screen
        std::cin.ignore();
        system("cls");
    }
    
}

void AttackMonster(Monster* defender, Monster* attacker)
{
    defender->health -= attacker->damage;

    std::cout << attacker->name << " attacks the " << defender->name << " for "
        << attacker->damage << " damage!" << std::endl;
}

void DisplayMonsterHealth(Monster* m)
{
    std::cout << "The " << m->name << " has " << m->health << " health remaining..." << std::endl;
    
    if (m->health < 0)
    {
        std::cout << "The " << m->name << " was defeated!\n";
    }
}

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "hutils.h"
#include "ttrpg.h"
#include "helpers\create_monster.h"

using namespace std;
using namespace hUtils;

void adventure(Player &player, Monster &monster)
{
    int randArea = rand() % 2 + 1;
    int randEncounter = rand() % 4 + 1;

    

    cout << "\tYou wondered out to the grasslands and followed the road...\n";
    sleep(2000);

    switch(randArea){
        case 1: cout << "\tYou walked along the road next to a forest...\n";
            sleep(1000);

            switch(randEncounter){
                case 1:
                    cout << "\tYou encountered a Slime!\n\n";
                    createMonster(monster, "Slime", 15, 3, 4.8, 0.02, 0.1, 0.16, 0.25, 10);
                    break;
                case 2:
                    cout<<"\tYou encountered a Wolf!\n\n";
                    createMonster(monster, "Wolf", 50, 5.5, 7.9, 0.001, 0.05, 0.001, 0.05, 15);
                    break;
                case 3: 
                    cout<<"\tYou encountered a Goblin!\n\n";
                    createMonster(monster, "Goblin", 75, 6.8, 9, 0.05, 0.1, 0.0001, 0.001, 0.03);
                    break;
                case 4:
                    cout<<"\tYou did not encounter any monster...\n\n";
                    sleep(1000);
                    cout<<"\tGoing back to town for safety.\n\n";
                    sleep(500);
                    return;
            }
            battleMenu(player, monster);
            break;
        case 2:
            cout<<"\tYou saw a various camps and ruins...\n";
            sleep(1000);
            cout<<"\tLet's go and check.\n";
            sleep(1000);

            switch(randEncounter){
                case 1: 
                    cout<<"\tYou encountered a Goblin!\n";
                    createMonster(monster, "Goblin", 75, 6.8, 9, 0.05, 0.1, 0.0001, 0.001, 0.03);
                    break;
                case 2:
                    cout<<"\tYou encountered a Bandit!\n\n";
                    createMonster(monster, "Bandit", 100, 10.34, 16.79, 0.07, 0.15, 0.001, 0.05, 0.13);
                    break;
                case 3:
                    cout<<"\tYou encountered a Knight!\n";
                    sleep(500);
                    cout<<"\t'It stinks!'\n";
                    sleep(1000);
                    cout<<"\t'Is that a zombie with armour?!'\n\n";
                    createMonster(monster, "Knight", 100, 12.60, 19.5, 0.15, 0.20, 0.0, 0.0, 0.0);
                    break;
                case 4:
                    cout<<"\tYou did not encounter any monster...\n\n";
                    sleep(2000);
                    cout<<"\tGoing back to town for safety.\n\n";
                    sleep(500);
                    return;
            }
            battleMenu(player, monster);
            break;
    }
}
#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <algorithm>

#include "hutils.h"
#include "ttrpg.h"

using namespace hUtils;

//  A dice in a form of code.
int rollDice()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(0, 20);
    return dist(gen);
}
//  d20 Critical Move System.
double criticalMoveRoll(int roll)
{
    if(roll == 20){ //  Critical Success.
        text.toCentered("A critical hit!", 220, {}, true);
        return 2.0;
    }
    else if(roll >= 11){ //  Full Success.
        return 1.3;
    }
    else if(roll >= 6){ //  Partial Success.
        return 1.0;
    }
    else{ //  Failure.
        text.toCentered("A weak hit!", 180, {}, true);
        return 0.8;
    }
}
//  The player attacks and the monster take damage.
void physicalAttack(Player &player, Monster &monster)
{
    int roll= rollDice();
    double multiplier= criticalMoveRoll(roll); //  Critical move variable.
    double totalDmg= player.getTotalDamage() * multiplier; //  Final product of the damage.

    double dmgResisted = totalDmg * monster.getPhysicalResist();
    double reducedDmg  = totalDmg - dmgResisted;   
    monster.setCurrentHealth(std::max(0.0, monster.getCurrentHealth() - reducedDmg));

    double percentage  = (totalDmg > 0.0) ? (dmgResisted / totalDmg) * 100.0 : 0.0;

    if(totalDmg == 0.0){
        text.toCentered(player.getName() + " did not dealt any damage.");
        return;
    }

    text.toCentered(player.getName() + " dealt a total of " + text.toString(totalDmg, 1) +" damage!");

    if(!monster.isAlive()){
        text.toCentered(monster.getName() + " couldn't withstand the damage!\n", 160, {}, true);
    }
    else{
        text.toCentered(monster.getName() + " resisted " + text.toString(percentage, 1) + "%!");
    }
}
//  The monster attacks and the player take damage.
void takeDamage(Player &player, Monster &monster)
{
    int roll= rollDice();
    double multiplier = criticalMoveRoll(roll); //  Critical move variable.
    double totalDmg   = monster.damage*multiplier; //  Final product of the damage.

    double dmgResisted = totalDmg * player.getTotalResistance();
    double reducedDmg  = totalDmg - dmgResisted;

    player.setCurrentHealth(std::max(0.0, player.getCurrentHealth() - reducedDmg));

    double percentage = (monster.damage>0.0) ? (dmgResisted / monster.damage) * 100 : 0.0;

    text.toCentered(monster.getName() + " attacks with " + text.toString(monster.getDamage(), 1) + " damage!");

    if(!player.isAlive()){
        text.toCentered(player.getName() + " couldn't withstand the damage!\n", 160, {}, true);
    }
    else{
        text.toCentered(player.name + " resisted " + text.toString(percentage, 1) + "%!");
    }
}
//  Pokemon battle ahh.
void battleMenu(Player &player, Monster &monster)
{ 
    char choice;

    do{
        sleep(500); text.toLine();
        text.toCentered("What would you like to do?\n");
        text.toCentered("[A] Fight | [S] Block | [D] Flee");
        std::cout<< text.color(93) + "Choose: " + text.defaultText();
        std::cin >> choice;
        std::cout << '\n';
        choice = tolower(choice);

        sleep(500);
        switch(choice){
            case 'a': //  Player attacks monster.
                text.toCentered(player.getName() + " attacks with his " + player.getMainHand() + "!");
                if(monster.didDodge()){
                    sleep(2000);
                    text.toCentered(player.getName() + " missed the attack!", 133, {}, true);
                }
                else{
                    physicalAttack(player, monster);
                }
                sleep(1500);
                text.toCentered(monster.getName() + " has " + text.toString(monster.getCurrentHealth(), 1) + " health left.");
                break;
            case 's': //  Player chooses to block.
                if(player.getOffHand().empty()){
                    text.toCentered("'I don't have a shield equiped!'");
                    break;
                }
                text.toCentered(player.getName() + " blocks with his " + player.getOffHand() + "!");
                break;
            case 'd':
                text.toCentered("\tFleeing away from the enemy!\n", 208, {}, true);
                sleep(2000);
                return;
            default: text.toCentered("Invalid action! Please enter again.", 91);
                text.clearAll();
                continue;
        }
        sleep(1500);

        if(!monster.isAlive()){
            text.toCentered(monster.getName() + " has been defeated!", 76, {}, true);
            sleep(2000);
            return;
        }

        //  Monster attacks player.
        if(player.didDodge()){
            text.toCentered("\tThe monster missed the attack!", 133, {}, true);
        }
        else{
            takeDamage(player, monster);
        }
        sleep(1500);

        text.toCentered(player.getName() + " has " + text.toString(player.getCurrentHealth(), 1) + " health left.\n");
        sleep(2000);

        if(!player.isAlive()){
            text.toCentered(player.getName() + " has been defeated!\n", 160, {}, true);
        }
    }while(player.isAlive() && monster.isAlive());
}
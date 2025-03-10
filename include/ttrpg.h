#ifndef TTRPG_H
#define TTRPG_H

#include "entities/monster.h"
#include "entities/player.h"
#include "menus.h"

void adventure(Player &player, Monster &monster);

// Function to modify attributes (e.g., spend points).
void modifyAttributes(Player &player, std::string fileName);

//  The player attacks and the monster take damage.
void physicalAttack(Player &player, Monster &monster);
//  The monster attacks and the player take damage.
void takeDamage(Player &player, Monster &monster);
//  Pokemon battle ahh.
void battleMenu(Player &player, Monster &monster);

// Function to load an existing .txt file.
void characterLoad(Player &player, const std::string& fileName);
// Function to save progress.
void savePlayer(const Player &player, const std::string &filename);

// Function to create a new .txt file.
void newSave(Player &player, std::string fileName);

#endif
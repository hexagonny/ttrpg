#ifndef MENUUTILITY_H
#define MENUUTILITY_H

#include "ttrpg.h"

void allocationOption(Player &player,
                      std::string fileName);
void inventoryMenu   (Player &player);
void displayMainMenu (Player &player,
                      Monster &monster,
                      std::string fileName);
void displayInfo     (Player player);

#endif
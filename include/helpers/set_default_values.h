#ifndef SETDEFAULTS_H
#define SETDEFAULTS_H

#include "ttrpg.h"

void setDefaultValues(Player &player){
    player.setCurrentHealth(player.getTotalHealth());
    player.setCurrentMana(player.getTotalMana());
    player.setAllocation(2);
}

#endif
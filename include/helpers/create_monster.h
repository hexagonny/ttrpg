#ifndef MONSTERHELPER_H
#define MONSTERHELPER_H

#include "ttrpg.h"

//  Invent your own monsters!
void createMonster(Monster &monster, std::string name,
    double health,
    double minDamage, double maxDamage,
    double minPhyResist, double maxPhyResist,
    double minMagResist, double maxMagResist,
    double baseDodge)
{
    monster.setName(name);
    monster.setCurrentHealth(health);
    monster.setTotalHealth(health);
    monster.setDamage(monster.createRandStat(minDamage, maxDamage));
    monster.physicalResist= monster.createRandStat(minPhyResist, maxPhyResist);
    monster.magicResist= monster.createRandStat(minMagResist, maxMagResist);
}

#endif
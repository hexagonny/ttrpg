#ifndef CLASSPRESETHELPER_H
#define CLASSPRESETHELPER_H

#include "ttrpg.h"
#include "hutils.h"

// Helper function to create presets.
void createClassPreset(Player &player,
    int strength, int endurance, int intelligence, int dexterity,
    std::string char_class, std::string main, std::string off)
{
    player.setStrength(strength);
    player.setEndurance(endurance);
    player.setIntelligence(intelligence);
    player.setDexterity(dexterity);
    player.setCharClass(char_class);
    player.setMainHand(main);
    player.setOffHand(off);
}

#endif
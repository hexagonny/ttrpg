#ifndef MONSTEROBJECT_H
#define MONSTEROBJECT_H

#include <iostream>
#include <cstdlib>
#include <ctime>

//  A monster struct to pass the values from function to function.
struct Monster {
    //  Information
    std::string name;

    std::string getName() const { return name; }

    void setName(std::string& newName) { name = newName; }

    //  Health Points
    double total_health;
    double current_health;

    double getCurrentHealth() const { return current_health; }
    double getTotalHealth() const { return total_health; }

    void setCurrentHealth(double newCurrHealth) { current_health = newCurrHealth; }
    void setTotalHealth(double newTotalHealth) { total_health = newTotalHealth; }

    //  Attributes
    double damage;
    double physicalResist;
    double magicResist;
    double baseDodgeChance;

    double getDamage() const { return damage; }
    double getPhysicalResist() const { return physicalResist; }
    double getMagicalResist() const { return magicResist; }
    double getTotalDodgeChance() const
    {
        double defaultChance= 0.15;
        return baseDodgeChance  + defaultChance;
    }

    void setDamage        (double newDamage)      { damage = newDamage; }
    void setPhysicalResist(double newPhysResist)  { physicalResist = newPhysResist; }
    void setMagicalResist (double newMagicResist) { magicResist = newMagicResist; }
    void setDodgeChance   (double newDodgeChance) { baseDodgeChance = newDodgeChance; }

    double createRandStat(double min, double max) const
    {
        return min+static_cast<double>(rand()) / (RAND_MAX / (max - min));
    }

    bool isAlive() const
    {
        return current_health > 0;
    }
    bool didDodge() const
    {
        double totalValue = getTotalDodgeChance();
        double randomValue = static_cast<float>(rand()) / RAND_MAX;
        return randomValue < totalValue;
    }    
};

#endif
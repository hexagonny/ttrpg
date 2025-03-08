#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

//  The player struct to pass the values from function to function.
struct Player {
    //  Information
    std::string name;
    std::string char_class;

    std::string getName()      const { return name; }
    std::string getCharClass() const { return char_class; }

    void setName     (std::string& newName)      { name = newName; }
    void setCharClass(std::string& newCharClass) { char_class = newCharClass; }   

    //  Health Points
    double total_health;
    double current_health;

    double getCurrentHealth() const { return current_health; }
    double getTotalHealth()   const
    {
        double defaultHealth = 100.0;
        return defaultHealth + intelligence;
    }

    void setCurrentHealth(double newCurrHealth) { current_health = newCurrHealth; }
    void setTotalHealth(double newTotalHealth) { total_health = newTotalHealth; }

    //  Mana Points
    double total_mana;
    double current_mana;

    double getCurrentMana() const { return current_mana; }
    double getTotalMana()   const
    {
        double defaultMana = 60.0;
        return defaultMana + intelligence;
    }

    void setCurrentMana(double newCurrMana)  { current_mana = newCurrMana; }
    void setTotalMana  (double newTotalMana) { total_mana = newTotalMana; }

    // Level Points
    int level;
    double current_exp;
    double required_exp; //  Required experience points in order to level up.

    int    getLevel()       const { return level; }
    double getCurrentExp()  const { return current_exp; }
    double getRequiredExp() const { return required_exp; }

    void setLevel      (int newLevel)   { level = newLevel; }
    void setCurrentExp (int newCurrExp) { current_exp = newCurrExp; }
    void setRequiredExp(int newReqExp)  { current_exp = newReqExp; }

    // Attributes
    int strength;
    int endurance;
    int intelligence;
    int dexterity;
    int allocation_points;

    int getStrength()     const { return strength; }
    int getEndurance()    const { return endurance; }
    int getIntelligence() const { return intelligence; }
    int getDexterity()    const { return dexterity; }
    int getAllocation()   const { return allocation_points; }

    void setStrength    (int newStrength)     { strength = newStrength; }
    void setEndurance   (int newEndurance)    { endurance = newEndurance; }
    void setIntelligence(int newIntelligence) { intelligence = newIntelligence; }
    void setDexterity   (int newDexterity)    { dexterity = newDexterity; }
    void setAllocation  (int newAllocation)   { allocation_points = newAllocation; }
    
    //  Inventory and equipment
    std::string mainHand;
    std::string offHand;
    std::string helmet;
    std::string chestplate;
    std::string boots;

    std::string getMainHand() const { return mainHand; }
    std::string getOffHand()  const { return offHand; }
    //  Other equipments is for later.

    void setMainHand(std::string equipment) { mainHand = equipment; }
    void setOffHand (std::string equipment) { mainHand = equipment; }

    std::vector<std::string> items = { getMainHand(),getOffHand(),
        "Health Potion", "Bow", "Arrow",
        "Magic Scroll", "Helmet", "Armor", "Boots",
        "Ring", "Torch", "Rope", "Pickaxe", "Mana Potion"};

    //  Place-holder items.
    double tempWeaponDamage= 20.0;
    double tempHelm= 0.005;
    double tempChestp= 0.015;
    double tempBoots= 0.001;

    //  PLace-holder boots dodge chance bonus.
    double tempEquipBonus= 0.07;

    const double maxBonus= 50.0;

    double getTotalDamage() const
    {
        double baseDamage= (maxBonus * strength)/(100*(maxBonus+strength));
        return tempWeaponDamage*(1+baseDamage);
    }

    double getTotalResistance() const
    {
        double baseResistance= (maxBonus*endurance)/(100*(maxBonus+endurance));
        return tempHelm + tempChestp + tempBoots + baseResistance;
    }

    double getTotalDodgeChance() const
    {
        double defaultChance= 0.15;
        double baseDodgeChance= (maxBonus*dexterity)/(100*(maxBonus+dexterity));
        return tempEquipBonus + defaultChance + baseDodgeChance;
    }

    bool isAlive() const
    {
        return current_health > 0;
    }
    bool didDodge() const
    {
        double totalValue= getTotalDodgeChance();
        double randomValue= static_cast<float>(rand())/RAND_MAX;
        return randomValue < totalValue;
    }    
};

#endif
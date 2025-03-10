#include <iostream>
#include <fstream>
#include <unordered_map>
#include <functional>
#include <algorithm>

#include "hutils.h"
#include "ttrpg.h"

using namespace std;

void characterLoad(Player &player, const string& fileName) {
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Unable to open file " << fileName << "for loading.\n";
        return;
    }

    // Map attribute names to lambda functions that set player attributes
    unordered_map<string, function<void(const string&)>> attributeMap = {
        {"Name",        [&](const string& val) { player.setName(val); }},
        {"Class",       [&](const string& val) { player.setCharClass(val); }},
        {"CurrHealth",  [&](const string& val) { player.setCurrentHealth(stoi(val)); }},
        {"CurrMana",    [&](const string& val) { player.setCurrentMana(stod(val)); }},
        {"Strength",    [&](const string& val) { player.setStrength(stoi(val)); }},     // Used for total damage
        {"Endurance",   [&](const string& val) { player.setEndurance(stoi(val)); }},    // Used for total health
        {"Intelligence",[&](const string& val) { player.setIntelligence(stoi(val)); }}, // Used for total mana
        {"Dexterity",   [&](const string& val) { player.setDexterity(stoi(val)); }},
        {"Points",      [&](const string& val) { player.setAllocation(stoi(val)); }},
        {"Mainhand",    [&](const string& val) { player.setMainHand(val); }},
        {"Offhand",     [&](const string& val) { player.setOffHand(val); }}
    };

    string line;
    while (getline(inFile, line)) {
        size_t delimiterPosition = line.find('-');
        if (delimiterPosition != string::npos) {
            string key = line.substr(0, delimiterPosition);   // Extract key
            string value = line.substr(delimiterPosition + 1); // Extract value

            auto it = attributeMap.find(key);
            if (it != attributeMap.end()) {
                it->second(value);  // Call the corresponding setter function
            }
        }
    }

    inFile.close();

    // Ensure current health and mana do not exceed their calculated maximum values
    player.setCurrentHealth(min(player.getCurrentHealth(), player.getTotalHealth()));
    player.setCurrentMana  (min(player.getCurrentMana()  , player.getTotalMana()));

    hUtils::sleep(4000);
    hUtils::text.toCentered("Character Information Loaded!\n");
    hUtils::sleep(500);
    displayInfo(player);

    hUtils::text.toCentered("Going to character menu in...\n");
    for (int i = 1; i <= 3; i++) {
        hUtils::text.toCentered(to_string(i) + "..");
        hUtils::sleep(1000);
    }
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <filesystem>

#include "hutils.h"
#include "ttrpg.h"

using namespace std;
namespace fs = std::filesystem;

void characterLoad(Player &player, string fileName)
{
    //  Temporary variables to store the player's character attributes.
    string NAME, CLASS, MAIN, OFF;
    int HP, MP, STR, END, INT, DEX, POINTS;

    ifstream inFile(fileName);

    //  Read each line of the file.
    string line;
    while(getline(inFile, line)){
        //  Find the position of '-' character in the line.
        size_t delimiterPosition = line.find('-');

        //  If '-' is found, extract the attribute name and value.
        if (delimiterPosition != std::string::npos) {
            //  Extract value as a substring after the '-'.
            std::string value = line.substr(delimiterPosition+1);

            //  Check which attribute this value belongs to by looking at the prefix.
            if(line.find("Name")!=string::npos){
                NAME = value;
            }else if(line.find("Class")!=string::npos){
                CLASS = value;
            }else if(line.find("Health")!=string::npos) {
                HP = stod(value); //  Convert string to double.
            }else if(line.find("Mana")!=string::npos){
                MP = stod(value);
            }else if(line.find("Strength")!=string::npos){
                STR = stoi(value); //  Convert string to integer.
            }else if(line.find("Endurance")!=string::npos){
                END = stoi(value);
            }else if(line.find("Intelligence")!=string::npos){
                INT = stoi(value);
            }else if(line.find("Dexterity")!=string::npos){
                DEX = stoi(value);
            }else if(line.find("Points")!=string::npos){
                POINTS = stoi(value);
            }else if(line.find("Mainhand")!=string::npos){
                MAIN = value;
            }else if(line.find("Offhand")!=string::npos){
                OFF = value;
            }
        }
    }

    inFile.close();

    //  Pass the values to Player struct.
    player.setName(NAME);
    player.setCharClass(CLASS);
    player.setTotalHealth(HP);
    player.setCurrentHealth(player.getTotalHealth());
    player.setTotalMana(MP);
    player.setCurrentMana(player.getCurrentMana());
    player.setStrength(STR);
    player.setEndurance(END);
    player.setIntelligence(INT);
    player.setDexterity(DEX);
    player.setAllocation(POINTS);
    player.setMainHand(MAIN);
    player.setOffHand(OFF);

    hUtils::sleep(4000);

    //  Display after passing the values to playerStruct.
    hUtils::text.toCentered("Character Information Loaded!\n");
    hUtils::sleep(500);
    displayInfo(player);

    hUtils::text.toCentered("Going to character menu in...\n");
    for(int i=1; i <=3; i++){
        hUtils::text.toCentered(i + "..");
        hUtils::sleep(1000);
    }
}
void savePlayer(const Player &player, const string &fileName)
{
    ofstream outFile(fileName);
    if(outFile.is_open()){
        outFile << "Name-"         << player.getName()         << "\n";
        outFile << "Class-"        << player.getCharClass()    << "\n";
        outFile << "Health-"       << player.getCurrentHealth()<< "\n";
        outFile << "Mana-"         << player.getCurrentMana()  << "\n";
        outFile << "Strength-"     << player.getStrength()     << "\n";
        outFile << "Endurance-"    << player.getEndurance()    << "\n";
        outFile << "Intelligence-" << player.getIntelligence() << "\n";
        outFile << "Dexterity-"    << player.getDexterity()    << "\n";
        outFile << "Points-"       << player.getAllocation()   << "\n";
        outFile << "Mainhand-"     << player.getMainHand()     << "\n";
        outFile << "Offhand-"      << player.getOffHand()      << "\n";

        outFile.close();
        hUtils::text.toCentered("Changes saved to " + fileName, 160, {}, true);
    }
    else{
        hUtils::text.toCentered("Failed to open " + fileName + " for saving.\n", 91);
    }
}
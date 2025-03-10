#include <iostream>
#include <fstream>
#include <string>

#include "hutils.h"
#include "ttrpg.h"
#include "helpers\create_class_preset.h"
#include "helpers\set_default_values.h"

void newSave(Player &player, std::string fileName)
{
    int choice;

    hUtils::sleep(500);
    do{ //  Class selection.
        std::cout << "\tSelect your class:\n"
                  << "\t\t1. Warrior\n"
                  << "\t\t2. Mage\n"
                  << "\t\t3. Thief\n"
                  << "\t\t4. Tank\n"
                  << '\t';
        std::cin>>choice;

        //  Resets the error flags when std::cin fails to interpret the input.
        std::cin.clear();
        fflush(stdin);

        hUtils::text.clearAll();
        std::cout << "\tHello " << player.getName() << "," << '\n';
        switch(choice){
            case 1: //  Warrior's Pre-set.
                    createClassPreset(player, 3, 3, 0, 2, "Warrior", "Iron Sword", "Wooden Shield");
                    std::cout<<"\tThe Warrior class interacts with the combat system.\n\n";
                    break;
            case 2: //  Mage's Pre-set.
                    createClassPreset(player, 0, 2, 4, 2, "Mage", "Wooden Wand", "Talisman");
                    std::cout<<"\tThe Mage class interacts with the magic system.\n\n";
                    break;
            case 3: //  Thief's Pre-set.
                    createClassPreset(player, 3, 1, 0, 4, "Thief", "Iron Dagger", "Talisman");
                    std::cout<<"\tThe Thief class interacts with the skill check system.\n\n";
                    break;
            case 4: //  Tank's Pre-set.
                    createClassPreset(player, 3, 4, 0, 1, "Tank", "Iron Axe", "Iron Shield");
                    std::cout<<"\tThe Tank class interacts with the defense system.\n\n";
                    break;
            default: //  Invalid user input.
                    std::cout<<"\tPlease enter one of the 4 classes provided.\n\n";
                    break; 
        }
    }while(choice <1 || choice > 4);

    setDefaultValues(player);
    
    hUtils::sleep(2000);

    //  Display current changes.
    std::cout << "\tCurrent attribute values:\n";
    displayInfo(player);

    std::cout<<"\tYou have given "<<player.getAllocation()<<" extra points!\n\n";
    hUtils::sleep(300);

    allocationOption(player, fileName);

    std::cout<<"\tFinal attribute values:\n";
    displayInfo(player);

    savePlayer(player, fileName);
    hUtils::pause();
}

void savePlayer(const Player &player, const std::string &fileName)
{
    std::ofstream outFile(fileName);
    if(outFile.is_open()){
        outFile << "Name-"         << player.getName()         << "\n";
        outFile << "Class-"        << player.getCharClass()    << "\n";
        outFile << "CurrHealth-"   << player.getCurrentHealth()<< "\n";
        outFile << "CurrMana-"     << player.getCurrentMana()  << "\n";
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
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <string>

#include "hutils.h"
#include "ttrpg.h"
#include "helpers\create_class_preset.h"

using namespace std;

void newSave(Player &player, string fileName)
{
    int CLASS_CHOICE, CHOICE;

    hUtils::sleep(500);
    do{ //  Class selection.
        cout<<"\tSelect your class:\n"
            <<"\t\t1. Warrior\n"
            <<"\t\t2. Mage\n"
            <<"\t\t3. Thief\n"
            <<"\t\t4. Tank\n"
            <<'\t';
        cin>>CLASS_CHOICE;
        cout<<endl;

        //  Resets the error flags when std::cin fails to interpret the input.
        cin.clear();
        fflush(stdin);

        hUtils::sleep(500);
        cout<<"\tHello "<<player.name<<","<<'\n';
        switch(CLASS_CHOICE){
            case 1: //  Warrior's Pre-set.
                    createClassPreset(player, 3, 3, 0, 2, "Warrior", "Iron Sword", "Wooden Shield");
                    cout<<"\tThe Warrior class interacts with the combat system.\n\n";
                    break;
            case 2: //  Mage's Pre-set.
                    createClassPreset(player, 0, 2, 4, 2, "Mage", "Wooden Wand", "Talisman");
                    cout<<"\tThe Mage class interacts with the magic system.\n\n";
                    break;
            case 3: //  Thief's Pre-set.
                    createClassPreset(player, 3, 1, 0, 4, "Thief", "Iron Dagger", "Talisman");
                    cout<<"\tThe Thief class interacts with the skill check system.\n\n";
                    break;
            case 4: //  Tank's Pre-set.
                    createClassPreset(player, 3, 4, 0, 1, "Tank", "Iron Axe", "Iron Shield");
                    cout<<"\tThe Tank class interacts with the defense system.\n\n";
                    break;
            default: //  Invalid user input.
                    cout<<"\tPlease enter one of the 4 classes provided.\n\n";
                    break; 
        }
    }while(CLASS_CHOICE <1 || CLASS_CHOICE > 4);

    player.setTotalHealth(100.0);
    player.setTotalMana(60);
    player.setCurrentHealth(player.getTotalHealth());
    player.setCurrentMana(player.getTotalMana());
    player.setAllocation(2);
    hUtils::sleep(2000);

    //  Display current changes.
    cout<<"\tCurrent attribute values:\n";
    displayInfo(player);

    cout<<"\tYou have given "<<player.getAllocation()<<" extra points!\n\n";
    hUtils::sleep(300);

    allocationOption(player, fileName);

    cout<<"\tFinal attribute values:\n";
    displayInfo(player);

    savePlayer(player, fileName);
    hUtils::sleep(200);
    cout<<"\tCharacter saved successfully to "<<fileName<<"!"<<'\n';
}
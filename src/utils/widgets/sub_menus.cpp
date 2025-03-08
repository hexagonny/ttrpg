#include <iostream>
#include <vector>

#include "hutils.h"
#include "ttrpg.h"

using std::cout;
using std::cin;
using std::string;
using std::setw;
using std::left;

using namespace hUtils;

void allocationOption(Player &player, std::string fileName)
{
    char choice;
    text.toCentered("\tYou have " + std::to_string(player.getAllocation()) + " point currently.\n");
        sleep(1000);
        text.toCentered("\tWould you like to spend your unspent points? (y/n)");
        std::cout<< text.color(93) + "Choose: " + text.defaultText();
        cin >> choice;
        choice = tolower(choice);

        switch(choice){
            case 'y': modifyAttributes(player, fileName); break;
            case 'n': text.toCentered("Alright, make sure to spend them later."); break;
            default : text.toCentered("Invalid input!", 91); break;
        }
}

void displayInfo(Player player)
{   
    //  Bars that represent health, mana and exp.

    //  General Info.
    cout<<"\tPlayer Info:\n";
    text.toLeft("Name:"   + player.getName(),      2, {}, {}, 14);
    text.toLeft("Class:"  + player.getCharClass(), 2, {}, {}, 14);
    text.toLeft("Health:" + text.toString(player.getCurrentHealth(), 1)
                    + "/" + text.toString(player.getTotalHealth(),   1) + " HP", 2, {}, {}, 14);
    text.toLeft("Mana:"   + text.toString(player.getCurrentMana(),   1)
                    + "/" + text.toString(player.getTotalMana(),     1) + " MP\n", 2, {}, {}, 14);
    
    //  Attributes.
    cout<<"\tAttributes:\n";
    cout<<"\t\t"<<setw(14)<<left<<"Strength:"     << player.getStrength()     << '\n'
        <<"\t\t"<<setw(14)<<left<<"Endurance:"    << player.getEndurance()    << '\n'
        <<"\t\t"<<setw(14)<<left<<"Intelligence:" << player.getIntelligence() << '\n'
        <<"\t\t"<<setw(14)<<left<<"Dexterity:"    << player.getDexterity()    << '\n';
    cout<< '\n';
    pause();
}
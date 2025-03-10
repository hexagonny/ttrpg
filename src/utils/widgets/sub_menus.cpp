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
    text.toLine();

    text.toLeft("Player Info:", 1);
    text.toCentered(player.getName());
    text.toCentered("Class: " + player.getCharClass());
    bar.setBar(player.getCurrentHealth(), player.getTotalHealth(), 124);
    bar.setBar(player.getCurrentMana(), player.getTotalMana());

    text.toLine();
    
    cout<<"\tAttributes:\n";
    cout<<"\t\t"<<setw(14)<<left<<"Strength:"     << player.getStrength()     << '\n'
        <<"\t\t"<<setw(14)<<left<<"Endurance:"    << player.getEndurance()    << '\n'
        <<"\t\t"<<setw(14)<<left<<"Intelligence:" << player.getIntelligence() << '\n'
        <<"\t\t"<<setw(14)<<left<<"Dexterity:"    << player.getDexterity()    << '\n';

    text.toLine();

    cout<<"\tEquipments:\n";
    cout<<"\t\t"<<setw(14)<<left<<"Main-hand:" << player.getMainHand() << '\n'
        <<"\t\t"<<setw(14)<<left<<"Off-hand:"  << player.getOffHand()  << '\n';

    pause();
}
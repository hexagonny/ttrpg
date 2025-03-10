#include <iostream>
#include <iomanip>
#include <fstream>

#include "hutils.h"
#include "ttrpg.h"

using namespace hUtils;

void modifyAttributes(Player &player, std::string fileName)
{
    int choice, ALLOCATION;

    while(player.allocation_points > 0){ //  Continue until all points are spent.
        text.clearAll();
        text.toLine();
        text.toCentered("Modifying Attributes:", 93);
        text.toLine();
        text.toCentered("You have " + std::to_string(player.getAllocation()) + " points left.");
        text.toLeft("Choose an attribute to increase:", 1);
        text.toLeft("Strength", 2, {}, 1);
        text.toLeft("Endurance", 2, {}, 2);
        text.toLeft("Intelligence", 2, {}, 3);
        text.toLeft("Dexterity", 2, {}, 4);
        text.toLine();
        std::cout << text.color(93) + "Choose: " + text.defaultText();
        std::cin >> choice;

        std::cin.clear();
        fflush(stdin);

        if(choice < 1 || choice > 4){
            text.toCentered("Invalid choice. Please choose again.\n", 91);
            continue; //  Go back to the start of the loop.
        }

        text.clearLine(4);
        text.toCentered("How many points would you like to allocate?");
        text.toLine();
        std::cout << text.color(93) + "Allocate: " + text.defaultText();
        std::cin >> ALLOCATION;
        std::cout << '\n';

        if(ALLOCATION <= 0 || ALLOCATION > player.getAllocation()){
            text.toCentered("tInvalid allocation.", 91);
            sleep(500);
            text.toCentered("You can only allocate between 1 and "
                            + std::to_string(player.getAllocation()) + " points.\n");
            continue;
        }

        //  Deduct points and allocate them to the chosen attribute.
        switch(choice){
            case 1: player.strength     += ALLOCATION; break;
            case 2: player.endurance    += ALLOCATION; break;
            case 3: player.intelligence += ALLOCATION; break;
            case 4: player.dexterity    += ALLOCATION; break;
        }

        player.allocation_points-= ALLOCATION;

        text.toCentered("\tPoints allocated successfully!\n");
        sleep(1000);
    }
    pause();
    savePlayer(player, fileName);
}
#include <iostream>
#include <vector>

#include "hutils.h"
#include "ttrpg.h"

using std::cout;
using std::cin;
using std::string;

using namespace hUtils;

void statisticScreen(Player &player, std::string fileName)
{
    text.toCentered("Showing stats...\n", 93);
    sleep(1000); text.clearAll();

    displayInfo(player);

    sleep(8000);
    if(player.allocation_points>0){
        allocationOption(player, fileName);
    }
    pause();
}

void inventoryMenu(Player &player)
{
    const int PAGE_LIMIT = 5;
    int totalItems = player.items.size();
    int totalPages = (totalItems + PAGE_LIMIT - 1) / PAGE_LIMIT;
    int currentPage = 1;
    char choice;

    do{
        text.clearAll();
        
        text.toLine();
        text.toCentered("Inventory (Page " + std::to_string(currentPage) +
                   " of " + std::to_string(totalPages) + ")", 93);

        int start_index = (currentPage - 1) * PAGE_LIMIT;
        int end_index = (start_index + PAGE_LIMIT < totalItems) ? (start_index + PAGE_LIMIT) : totalItems;

        for (int i = start_index; i < end_index; i++) {
            text.toLeft(player.items[i], {}, {}, i + 1);
        }

        std::cout<<'\n';
        text.toCentered("[N] Next Page | [P] Previous Page | [E] Exit");
        std::cout<< text.color(93) + "Choose: " + text.defaultText();
        std::cin >> choice;
        choice = tolower(choice);

        if (choice == 'n' && currentPage < totalPages) {
            currentPage++;
        } else if (choice == 'p' && currentPage > 1) {
            currentPage--;
        }
    }while(choice != 'e');
}

void displayMainMenu(Player &player, Monster &monster, string fileName)
{
    char choice;
    do{
        text.clearAll(); sleep(500);
        text.toLine();
        text.toCentered("Character Skill Sheet", 93);
        text.toLine();
        table.setElements(
            "    [A] Character Stats", "    [S] Inventory",
            "    [Q] Gather Items",    "    [W] Adventure",
            "    [E] Exit Game"
        );
        table.toColumn("left", 37, 2);
        text.toLine();
        cout << text.color(93) + "\nPick a menu: " + text.defaultText();
        cin >> choice;
        choice = tolower(choice);

        cin.clear();
        fflush(stdin);

        text.clearAll();
        text.toLine();
        switch(choice){
            case 'a': statisticScreen(player,fileName); break;
            case 's': inventoryMenu(player); break;
            case 'w': 
                text.toCentered("Adventuring...\n", 93);
                sleep(2000);
                adventure(player, monster);
                break;
            case 'q':
                text.toCentered("Gathering...\n", 93);
                sleep(2000);
                break;
            case 'e': text.toCentered("Exiting the game in...\n", 93); return;
            default : text.toCentered("\tEnter a valid input!\n", 91); break;
        }
    }while(choice != 5);

    for(int i=1; i <=3; i++){
        text.toCentered(std::to_string(i) + "..");
        sleep(1000);
    }
}
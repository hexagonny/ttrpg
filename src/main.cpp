#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <filesystem>

#include "hutils.h"
#include "ttrpg.h"

using std::cout;
using std::cin;
using std::string;

bool fileExists(const string &fileName)
{
    return std::filesystem::exists(fileName);
}

int main()
{
    hUtils::setConsoleWindowSize(); hUtils::text.clearAll();
    
    Player  player; //  It's the player itself.
    Monster monster; //  It's the monster itself.

    string NAME; //  The name for the player's character.
    string FILE_NAME; //  The name for the player's save file.

    int choice;
    char choice2;

    hUtils::text.toCentered("Selecting a character save file...\n");
    hUtils::sleep(500);
    do{
        hUtils::text.toLeft("What would you like to do?");
        hUtils::text.toLeft("Create a new save file.", 1, {}, 1);
        hUtils::text.toLeft("Select an existing save file.", 1, {}, 2);
        std::cout<< hUtils::text.color(93) + "Choose: " + hUtils::text.defaultText();
        cin >> choice;

        cin.clear();
        fflush(stdin);

        switch(choice){
            case 1: //  Create new save file.
                while(player.name.empty()){
                    hUtils::text.clearAll();
                    hUtils::text.toCentered("Creating a new save file...\n");
                    hUtils::sleep(500);

                    std::cout<< hUtils::text.color(93) + "Character name: " + hUtils::text.defaultText();
                    cin >> player.name;
                    cout << '\n';

                    if(player.name.length() > 12){
                        hUtils::text.toCentered("Your name can't be over 12 characters!\n", 91);
                        continue;
                    }
                    else if(player.name.empty()){
                        hUtils::text.toCentered("You didn't enter your name!\n", 91);
                        continue;
                    }

                    FILE_NAME = player.name+"_save.txt";

                    hUtils::text.clearAll();
                    //  Check if the file already exists.
                    if(fileExists(FILE_NAME)){
                        char CHOICE;
                        hUtils::text.toLeft("A file with this character name already exists. Do you want to:");
                        hUtils::text.toLeft("Overwrite the file (o)", 1);
                        hUtils::text.toLeft("Create a new file with a different name (n)", 1);
                        std::cout<< hUtils::text.color(93) + "Choose (o/n): " + hUtils::text.defaultText();
                        cin >> CHOICE;

                        CHOICE= tolower(CHOICE);

                        if(CHOICE == 'n'){
                            cout<< hUtils::text.color(93) + "Enter a new filename (without extension): " + hUtils::text.defaultText();
                            cin >> FILE_NAME;
                            FILE_NAME = player.name;
                            FILE_NAME += "_save.txt";
                        }
                    }
                }
                newSave(player, FILE_NAME);
                break;
            case 2: //  Load a save file.
                hUtils::text.clearAll();
                hUtils::text.toCentered("Selecting an existing save file...\n");
                hUtils::sleep(500);

                cout << hUtils::text.color(93) + "Character name: " + hUtils::text.defaultText();
                cin >> NAME;
                cout << '\n';

                FILE_NAME = NAME + "_save.txt";

                //  Check if the file does not exist.
                if(!fileExists(FILE_NAME)){
                    hUtils::text.toCentered("File does not exist!\n", 91);
                    cout << hUtils::text.color(93) + "Please enter an existing name:" + hUtils::text.defaultText();
                    cin >> NAME;
                    FILE_NAME = NAME + "_save.txt";
                }
                characterLoad(player, FILE_NAME);
                break;
            default:
                hUtils::text.toCentered("Enter a valid input!\n", 91);
                break;
        } 
    }while(choice != 1 && choice != 2);

    cin.clear();
    fflush(stdin);

    //  Seed the random number generator.
    srand(static_cast<unsigned int>(time(0)));

    displayMainMenu(player, monster, FILE_NAME);

    return 0;
}
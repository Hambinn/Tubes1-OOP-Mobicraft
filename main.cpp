// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "components/Item.hpp"
#include "components/Inventory.hpp"
#include "components/Craft.hpp"
#include "components/Command.hpp"
#include "components/Exception.hpp"

using namespace std;


void readItems(vector<ItemNonTool> *itemsNT, vector<ItemTool> *itemsT, string fileName){
    ifstream itemConfigaFile(fileName.c_str());
    string line;
    vector<ItemNonTool> vectorOfItemsNt;
    vector<ItemTool> vectorOfItemsT;
    while (getline(itemConfigaFile, line)){
        stringstream iline(line);
        string elementsInLine;

        ItemNonTool itemNT;
        ItemTool itemT;
        vector<string> elementsInVector;
        
        int i=0;
        while (getline(iline,elementsInLine,' ')){
            elementsInVector.push_back(elementsInLine);
            i++;
        }
        if (elementsInVector[3] == "NONTOOL"){
            itemNT.ID=stoi(elementsInVector[0]);
            itemNT.Name=elementsInVector[1];
            itemNT.Type=elementsInVector[2];
            itemsNT->push_back(itemNT);
        } else if (elementsInVector[3] == "TOOL"){
            itemT.ID=stoi(elementsInVector[0]);
            itemT.Name=elementsInVector[1];
            itemsT->push_back(itemT);
        }
    }
    itemConfigaFile.close();
}

void printMobicraft() {
    cout << "              _     _                 __ _   " << endl;
    cout << "  /\\/\\   ___ | |__ (_) ___ _ __ __ _ / _| |_ " << endl;
    cout << " /    \\ / _ \\| '_ \\| |/ __| '__/ _` | |_| __|" << endl;
    cout << "/ /\\/\\ \\ (_) | |_) | | (__| | | (_| |  _| |_ " << endl;
    cout << "\\/    \\/\\___/|_.__/|_|\\___|_|  \\__,_|_|  \\__|" << endl;
}

int main() {
    string configPath = "./config";
    string itemConfigPath = configPath + "/item.txt";
    vector<ItemNonTool> listItemNonTool;
    vector<ItemTool> listItemTool;
    ListRecipe resep;
    // read item from config file
    readItems(&listItemNonTool, &listItemTool, itemConfigPath);

    Inventory inventory;
    Craft craft;

    printMobicraft();
    char commandString[100];
    cout << "Enter command:" << endl;
    cin.getline(commandString, 100);
    // Command *command = new Command(commandString, &inventory, &craft, listItemNonTool, listItemTool,&resep);
    Command command(commandString, &inventory, &craft, listItemNonTool, listItemTool,&resep);
    command.giveCommand();
    while (command.getCommandName()!="EXIT") {
        command.Clear();
        // cout << command.getCommandName() << " satu"<< endl;
        cout << "Enter command:" << endl;
        // cout << command.getCommandName() << " deleted"<< endl; // TIDAK TERDELETE, ADDIN BANTU KAMI T_T
        cin.getline(commandString, 100);
        command.setCommand(commandString);
        // Command *command = new Command(commandString, &inventory, &craft, listItemNonTool, listItemTool,&resep);
        // Command command(commandString, &inventory, &craft, listItemNonTool, listItemTool,&resep);
        // cout << command.getCommandName() << " dua"<< endl;
        command.giveCommand();
    }
    cout << "Program ended." << endl;
    
  return 0;
}
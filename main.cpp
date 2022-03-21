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


int main() {
    string configPath = "./config";
    string itemConfigPath = configPath + "/item.txt";
    vector<ItemNonTool> listItemNonTool;
    vector<ItemTool> listItemTool;
    // read item from config file
    readItems(&listItemNonTool, &listItemTool, itemConfigPath);

    Inventory inventory;
    Craft craft;

    char commandString[100];
    cin.getline(commandString, 100);
    while (commandString!="EXIT") {
        Command command(commandString, &inventory, &craft, listItemNonTool, listItemTool);
        command.giveCommand();
        cin.getline(commandString, 100);
    }

    // //Print List Non Tool (For Debug)
    // cout << "Item Non Tool Available : "<< endl;
    // for(int i=0; i < listItemNonTool.size(); i++)
    // cout << listItemNonTool[i].getID() << ", " << listItemNonTool[i].getName() << ", " << listItemNonTool[i].getType() << endl;

    // //Print List Non Tool (for Debug)
    // cout << "\nItem Tool Available : " << endl;
    // for(int i=0; i < listItemNonTool.size(); i++)
    // cout << listItemTool[i].getID() << ", " << listItemTool[i].getName() << endl;

//   // read recipes
//   for (const auto &entry :
//        filesystem::directory_iterator(configPath + "/recipe")) {
//     cout << entry.path() << endl;
//     // read from file and do something
//   }

//   // sample interaction
//   string command;
//   while (cin >> command) {
//     if (command == "EXPORT") {
//       string outputPath;
//       cin >> outputPath;
//       ofstream outputFile(outputPath);

//       // hardcode for first test case
//       outputFile << "21:10" << endl;
//       outputFile << "6:1" << endl;
//       for (int i = 2; i < 27; i++) {
//         outputFile << "0:0" << endl;
//       }

//       cout << "Exported" << endl;
//     } else if (command == "CRAFT") {
//       cout << "TODO" << endl;
//     } else if (command == "GIVE") {
//       string itemName;
//       int itemQty;
//       cin >> itemName >> itemQty;
//       cout << "TODO" << endl;
//     } else if (command == "MOVE") {
//       string slotSrc;
//       int slotQty;
//       string slotDest;
//       // need to handle multiple destinations
//       cin >> slotSrc >> slotQty >> slotDest;
//       cout << "TODO" << endl;
//     } else {
//       // todo
//       cout << "Invalid command" << endl;
//     }
//   }
  return 0;
}
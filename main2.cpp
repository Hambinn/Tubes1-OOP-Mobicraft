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

//BUAT DEBUG YG GA PAKE COMMAND :D
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
    //BUAT DEBUG YG GA PAKE COMMAND :D
    string configPath = "./config";
    string itemConfigPath = configPath + "/item.txt";
    vector<ItemNonTool> listItemNonTool;
    vector<ItemTool> listItemTool;
    ListRecipe resep;
    // read item from config file
    readItems(&listItemNonTool, &listItemTool, itemConfigPath);

    Inventory inventory;
    Craft craft;

    inventory.giveItem(listItemNonTool[3], 2);
    inventory.giveItem(listItemNonTool[4], 2);
    inventory.giveItem(listItemNonTool[5], 2);
    inventory.giveItem(listItemNonTool[6], 3);
    inventory.showItem();
    craft.showItem();

    //pindahin dr inv ke craft table
    cout << "pindahin dr inv ke craft table" << endl;
    vector<int> slot_craft = {7};
    craft.moveItem(&inventory, 0, 1, slot_craft);
    vector<int> slot_craft2 = {4};
    craft.moveItem(&inventory, 1, 1, slot_craft2);

    inventory.showItem();
    craft.showItem();

    //balikin dr craft table ke inv
    cout << "balikin dari craft table ke inv" << endl;
    vector<int> slot_inv = {6};
    craft.moveItemBack(&inventory, 4, 1, slot_inv);
    inventory.showItem();
    craft.showItem();

    // cout << "crafting" << endl;
    // pair<string,int> hasilCraft;
    // hasilCraft = craft.Crafting(&resep);

    // for (int i = 0; i < listItemNonTool.size(); i++){
    //     if (listItemNonTool[i].getName() == hasilCraft.first){
    //         inventory.giveItem(listItemNonTool[i], hasilCraft.second);
    //     }
    // }
    // inventory.showItem();
    // craft.showItem();
    
  return 0;
}
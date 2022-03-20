// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <dirent.h>
#include "components/Item.hpp"
#include "components/Inventory.hpp"
#include "components/ListRecipe.hpp"
#include "components/Recipe.hpp"
#include "components/Craft.hpp"

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
    Inventory *mobitaInv = new Inventory();
    Craft *mobiCraft = new Craft();
    
    // read item from config file
    readItems(&listItemNonTool, &listItemTool, itemConfigPath);

    //Print List Non Tool (For Debug)
    cout << "Item Non Tool Available : "<< endl;
    for(int i=0; i < listItemNonTool.size(); i++)
    cout << listItemNonTool[i].getID() << ", " << listItemNonTool[i].getName() << ", " << listItemNonTool[i].getType() << endl;

    //Print List Non Tool (for Debug)
    cout << "\nItem Tool Available : " << endl;
    for(int i=0; i < listItemTool.size(); i++)
    cout << listItemTool[i].getID() << ", " << listItemTool[i].getName() << endl;

    // Contoh give Item dari input
    /*
    string tes, tes2;
    int tes3;
    cout << "\nMasukkan ItemNonTool dengan GIVE ITEM QTY (Contoh : GIVE DIAMOND 5)" << endl;
    cin >> tes >> tes2 >> tes3;
    if (tes == "GIVE"){
        for (int i = 0; i < listItemNonTool.size(); i++){
            if (listItemNonTool[i].getName() == tes2){
                mobitaInv->giveItem(listItemNonTool[i], tes3);
                break;
            }
        }
        cout << "\nTidak ada Item NonTool dengan nama : " << tes2 << endl;
    }
   mobitaInv->giveItem(listItemTool[24],1);
    */
    mobitaInv->giveItem(listItemTool[1],1);
    mobitaInv->giveItem(listItemTool[1],1);
    mobitaInv->giveItem(listItemNonTool[0],9);
    mobitaInv->giveItem(listItemNonTool[11],5);
    mobitaInv->giveItem(listItemNonTool[6],5);

    // Coba lihat isi mobitaInv
    mobitaInv->showItem();
    // Coba lihat isi mobitaCraft
    mobiCraft->showItem();

    int slot_craft[3] = {0,1,4};
    mobiCraft->moveItem(mobitaInv, 3, 3, slot_craft);

    int slot_craft1[2] = {3,6};
    mobiCraft->moveItem(mobitaInv, 4, 2, slot_craft1);

    // Coba lihat isi mobitaInv
    mobitaInv->showItem();
    // Coba lihat isi mobitaCraft
    mobiCraft->showItem();
    
    // coba bikin resep
    ListRecipe lr;

    //crafting
    pair<string,int> hasilCraft;
    hasilCraft = mobiCraft->Crafting(&lr);  //buat yang hasilnya tool, dia return nama item & durability. buat yg non tool. return nama item & quantity

    // give item tool

    for (int i = 0; i < listItemTool.size(); i++){
        if (listItemTool[i].getName() == hasilCraft.first){
            mobitaInv->giveItem(listItemTool[i], 1, hasilCraft.second);
            break;
        }
    }

    // Coba lihat isi mobitaInv
    mobitaInv->showItem();
    // Coba lihat isi mobitaCraft
    mobiCraft->showItem();

    //print list resep buat debug
    /*
    map<string,int> type;
    map<string,int>::iterator it;
    
    for(int i=0; i < lr.get_neff(); i++){
        cout << endl;
        cout << "col" << lr.get_recipe(i).get_col() << endl;
        cout << "row" << lr.get_recipe(i).get_row() << endl;
        type =  lr.get_recipe(i).get_all_type();
        for (it = type.begin(); it != type.end(); it++) {
            cout << it->first << " ";
            cout << it->second << endl;
        }
        lr.get_recipe(i).display_recipe();
    }
    */
    

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
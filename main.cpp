// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "components/Item.hpp"
#include "components/Inventory.hpp"
using namespace std;


void readItems(vector<ItemNonTool> *itemsNT, vector<ItemTool> *itemsT, string fileName){

    ifstream itemConfigaFile(fileName.c_str());

    // to do: use exception in this block
    if (!itemConfigaFile){
        cerr <<"Cannot open the File: " <<fileName<<endl;
        exit(1);
    }

    string line;
    while (getline(itemConfigaFile, line)){
        ItemNonTool itemNT;
        ItemTool itemT;
        stringstream iline(line);
        vector<string> elementsInVector;
        string elementsInLine;
        int i=0;
        while (getline(iline,elementsInLine,' ')){
            elementsInVector.push_back(elementsInLine);
            //cout << elementsInVector[i] << endl;
            //cout << "i now" << i << endl;
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
    
    // read item from config file
    readItems(&listItemNonTool, &listItemTool, itemConfigPath);

    //Print List Non Tool (For Debug)
    cout << "Item Non Tool Available : "<< endl;
    for(int i=0; i < listItemNonTool.size(); i++)
    cout << listItemNonTool[i].getID() << ", " << listItemNonTool[i].getName() << ", " << listItemNonTool[i].getType() << endl;

    //Print List Non Tool (for Debug)
    cout << "\nItem Tool Available : " << endl;
    for(int i=0; i < listItemNonTool.size(); i++)
    cout << listItemTool[i].getID() << ", " << listItemTool[i].getName() << endl;

    // Contoh give Item 
    // Anggep user input GIVE DIAMOND 2 
    mobitaInv->giveItem(listItemNonTool[11], 2);
    // user input GIVE OAK_LOG 20
    mobitaInv->giveItem(listItemNonTool[0], 20);
    // user input GIVE DIAMOND 5
    mobitaInv->giveItem(listItemNonTool[11], 5);

    // Coba lihat isi mobitaInv
    mobitaInv->showItem();

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
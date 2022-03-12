// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "components/Item.hpp"
#include "components/Inventory.hpp"
using namespace std;

vector<Item> readItems(string fileName){

    ifstream itemConfigaFile(fileName.c_str());

    // to do: use exception in this block
    if (!itemConfigaFile){
        cerr <<"Cannot open the File: " <<fileName<<endl;
        exit(1);
    }

    string line;
    vector<Item> items;
    while (getline(itemConfigaFile, line)){
        Item item;
        istringstream iline(line);
        vector<string> elementsInVector;
        string elementsInLine;
        int i=0;
        while (getline(iline,elementsInLine,' ')){
            //cout << elementsInLine << endl << "==";
            elementsInVector.push_back(elementsInLine);
            cout << elementsInVector[i] << endl;
            cout << "i now" << i << endl;
            i++;
        }
        item.ID=stoi(elementsInVector[0]);
        item.Name=elementsInVector[1];
        items.push_back(item);
    }

    itemConfigaFile.close();
    return items;
}

int main() {
    string configPath = "./config";
    string itemConfigPath = configPath + "/item.txt";
    vector<Item> items;
  // read item from config file
    items = readItems(itemConfigPath);

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
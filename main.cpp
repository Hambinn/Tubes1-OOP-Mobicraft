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

ListRecipe createRecipe() {
    //make a map for item and its type
    map <string, string> item_to_type;
    string path = "./config/item.txt";
    fstream newfile(path);
    string tp;
    while (getline(newfile,tp)) {
        string s = tp;
        string delimiter = " ";
        size_t pos = 0;
        string token;
        string key = "";
        string value = "";
        int cnt = 0;
        while ((pos = s.find(delimiter)) != string::npos) {
            cnt++;
            token = s.substr(0, pos);
            if (cnt == 2){
                key = token;
            }
            if (cnt == 3) {
                value = token;
            }
            s.erase(0, pos + delimiter.length());
        }
        item_to_type[key] = value;
    }
    //Read all recipe
    vector<string> recipe_name;
    vector<string>::iterator it;
    int cnt_recipe = 0;
    struct dirent *d;
    DIR *dr;
    dr = opendir("./config/recipe");
    if(dr!=NULL)
    {
        for(d=readdir(dr); d!=NULL; d=readdir(dr))
        {
            recipe_name.push_back(d->d_name);
            cnt_recipe++;
        }
        closedir(dr);
    }
    else
        cout<<"Error Occurred!" << endl;
    //delete 2 elemen awal yg tidak digunakan
    it = recipe_name.begin();
    recipe_name.erase(it);
    it = recipe_name.begin();
    recipe_name.erase(it);
    cnt_recipe -= 2;
    ListRecipe list_recipe(cnt_recipe);
    for (auto i = recipe_name.begin(); i != recipe_name.end(); i++){
        string path = "./config/recipe/";
        path += *i;
        fstream newfile(path); //open a file to perform read operation using file object
        string tp;
        getline(newfile,tp);
        //get the size
        int row = int(tp[0]) - 48;  //use this because the max size of row is 3
        int col = int(tp[2]) - 48;  //use this because the max size of column is 3
        //create recipe
        Recipe re1(row,col);
        //read recipe
        for (int i = 0; i < row; i++) {
            getline(newfile,tp);
            string temp = "";
            int cnt_col = 0;
            for (int j = 0; j < tp.length(); j++) {
                if ((tp[j] == ' ') || (j == tp.length()-1)) {
                    if (j == tp.length()-1) {
                        temp += tp[j];
                        if ((item_to_type[temp] == "") || (item_to_type[temp] == "-")){
                            re1.set_recipe(temp,i,cnt_col);
                        }
                        else{
                            re1.set_recipe(item_to_type[temp],i,cnt_col);
                        }
                        cnt_col++;
                    }
                    else{
                        if ((item_to_type[temp] == "") || (item_to_type[temp] == "-")){
                            re1.set_recipe(temp,i,cnt_col);
                        }
                        else{
                            re1.set_recipe(item_to_type[temp],i,cnt_col);
                        }
                        temp = "";
                        cnt_col++;
                    }
                }
                else{
                    temp += tp[j];
                }
            }
        }
        getline(newfile,tp);
        string temp = "";
        string result;
        int num_of_result;
        for (int i = 0; i < tp.length(); i++) {
            if (tp[i] == ' '){
                result = temp;
                temp = "";
            }
            else if (i == tp.length()-1) {
                temp += tp[i];
                num_of_result = stoi(temp);
            }
            else{
                temp += tp[i];
            }
        }
        newfile.close(); //close the file object
        re1.set_result(result);
        re1.set_num_of_result(num_of_result);
        list_recipe.add_recipe(re1);
    }
    return list_recipe;
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
    mobitaInv->giveItem(listItemNonTool[3],2);

    // Coba lihat isi mobitaInv
    mobitaInv->showItem();
    // Coba lihat isi mobitaCraft
    mobiCraft->showItem();

    int slot_craft[1] = {0};
    mobiCraft->moveItem(mobitaInv, 0, 1, slot_craft);

    int slot_craft1[1] = {1};
    mobiCraft->moveItem(mobitaInv, 1, 1, slot_craft1);

    // Coba lihat isi mobitaInv
    mobitaInv->showItem();
    // Coba lihat isi mobitaCraft
    mobiCraft->showItem();

    
    // coba bikin resep
    ListRecipe lr = createRecipe();

    map<string,int> type;
    map<string,int>::iterator it;
    pair<string,int> hasilCraft;

    hasilCraft = mobiCraft->Crafting(&lr);  //buat yang hasilnya tool, dia return nama item & durability. buat yg non tool. return nama item & quantity

    for (int i = 0; i < listItemNonTool.size(); i++){
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
    
    for(int i=0; i < lr.get_neff(); i++){
        cout << endl;
        cout << "col" << lr.get_recipe(i).get_col() << endl;
        cout << "row" << lr.get_recipe(i).get_row() << endl;
        lr.get_recipe(i).display_recipe();
    }
    

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
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Item.hpp"
#include "Inventory.hpp"
#include "Craft.hpp"
#include "Recipe.hpp"
#include "ListRecipe.hpp"
#include <fstream>
#include <map>
#include<dirent.h>

using namespace std;

//Asumsi GiveCommand bakal selalu Item Non Tool
void giveCommand(Inventory *myInv, string Name, int Qty){
    bool found = false;
    int idx = 0;
    if (Qty > 0 && Qty <= 64){

        //Cek apakah item dengan nama "Name" sudah ada di inventory
        for (int i=0; i<MAX_Inventory; i++){
            if(myInv->getItemName(i) == Name && myInv->getItemNonTool(i).getQuantity() <64 ){
                found = true;
                idx = i;
                break;
            }
        }

        //Jika ada, tambah Qty pada item tersebut
        if(found){
            int newQty = myInv->getItem(idx).myNonTool.getQuantity() + Qty;
            myInv->setItemNonTool(idx,1,Name, newQty);

        //Jika tidak, buat item baru pada inventory dengan indeks terkecil
        } else {
            int i = 0;
            while (myInv->getItem(i).myNonTool.getID() != 0)
            {
                i++;
            }
            myInv->setItemNonTool(i,1,Name,Qty);
        }
    }
}

void moveCommand(Inventory *myInv,  Craft *myCraft, int slot_inv, int N, int* slot_craft){
    try{
        myCraft->isCraftInvSlotEmpty(N, slot_craft);
        if (myInv->getItem(slot_inv).myNonTool.getQuantity() >= N){
            int newQty = myInv->getItem(slot_inv).myNonTool.getQuantity() - N;
            string Name = myInv->getItem(slot_inv).myNonTool.getName();   
            myInv->setItemNonTool(slot_inv,1,Name, newQty);

            for (int i=0; i<N; i++){
                myCraft->setItemNonTool(slot_craft[i],1,Name,1);
            }

        }
    }catch(const char* err){
        cout << err << endl;
    }
}

void showCommand(Inventory myInv, Craft myCraft){
    //Show Craft
    cout << "\nCraft :\n" << endl;
    for (int i=0; i< MAX_Craft; i++){
        cout << "[C " << myCraft.getItemNonTool(i).getName() << " " << myCraft.getItemNonTool(i).getQuantity() << "] ";
        if ((i+1) % 3 == 0){
            cout << endl;
        }
    }

    //Show Inventory
    cout << "\nInventory :\n" << endl;
    for (int i=0; i< MAX_Inventory; i++){

        // Print jika isinya item NonTool
        if (myInv.isFilledNonTool(i) && !myInv.isFilledTool(i)){
            cout << "[I " << myInv.getItemNonTool(i).getName() << " " << myInv.getItemNonTool(i).getQuantity() << "] ";
            if ((i+1) % 9 == 0){
                cout << endl;
            }
        } 
        
        //Print jika isinya item Tool
        else if (!myInv.isFilledNonTool(i) && myInv.isFilledTool(i)){
            cout << "[I " << myInv.getItemNonTool(i).getName() << " " << myInv.getItemTool(i).getDurability() << "] ";
            if ((i+1) % 9 == 0){
                cout << endl;
            }
        }

        //Print jika tidak ada item
        else if (!myInv.isFilledNonTool(i) && !myInv.isFilledTool(i)){
            cout << "[I " << "-" << " " << 0 << "] ";
            if ((i+1) % 9 == 0){
                cout << endl;
            }
        }
    }
    cout << "-------------------------- buat debug --------------------------" << endl;
}

ListRecipe createRecipe() {
    //make a map for item and its type
    map <string, string> item_to_type;
    string path = "../config/item.txt";
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
    dr = opendir("../config/recipe");
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
        string path = "../config/recipe/";
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

int main(){
    Inventory *mobitaInv = new Inventory();
    Craft *mobitaCraft = new Craft();

    //Give
    // GIVE <ITEM_NAME> <ITEM_QTY>
    // GIVE OAK_WOOD 10
    giveCommand(mobitaInv, "Oak", 15);
    giveCommand(mobitaInv, "Stick", 21);
    giveCommand(mobitaInv, "Oak", 16);
    giveCommand(mobitaInv, "Torch", 65);
    giveCommand(mobitaInv, "Stick", 2);
    giveCommand(mobitaInv, "Iron", 10);

    //Move
    // MOVE <INVENTORY_SLOT_ID> N <CRAFTING_SLOT_ID_1>
    // MOVE I0 N C0 C1 C2 ... CN
    showCommand(*mobitaInv, *mobitaCraft);

    int slot_craft[2] = {4,7};
    moveCommand(mobitaInv, mobitaCraft, 0, 2, slot_craft);
    showCommand(*mobitaInv, *mobitaCraft);


    int slot_craft2[3] = {0,1,2};
    moveCommand(mobitaInv, mobitaCraft, 2, 3, slot_craft2);

    //Show
    showCommand(*mobitaInv, *mobitaCraft);

    // //gagal mindahin gara2 ada craft table yang udah keisi
    int slot_craft3[2] = {8,7};
    moveCommand(mobitaInv, mobitaCraft, 2, 2, slot_craft3);

    map<string,int> tool;
    map<string,int> type;
    map<string,int>::iterator it;


    // //Cara pakai createRecipe
    ListRecipe lr = createRecipe();

    mobitaCraft->Crafting(mobitaInv, &lr);

    /*
    cara pake get all type recipe
    for(int i=0; i < lr.get_neff(); i++){
        cout << endl;
        lr.get_recipe(i).display_recipe();
        cout << "-----type-----" << endl;
        type = lr.get_recipe(i).get_all_type();
        for (it = type.begin(); it != type.end(); it++) {
            cout << it->first << " ";
            cout << it->second << endl;
        }
    }
    */


    return 0;
} 
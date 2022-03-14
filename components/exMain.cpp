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
#include<dirent.h>

using namespace std;

void giveCommand(Inventory *myInv, string Name, int Qty){
    bool found = false;
    int idx = 0;
    if (Qty > 0 && Qty <= 64){
        //Cek apakah item dengan nama "Name" sudah ada di inventory
        for (int i=0; i<MAX_Inventory; i++){
            if(myInv->getItem(i).getName() == Name && myInv->getItem(i).getQuantity() <64 ){
                found = true;
                idx = i;
                break;
            }
        }
        //Jika ada, tambah Qty pada item tersebut
        if(found){
            int newQty = myInv->getItem(idx).getQuantity() + Qty;
            myInv->setItem(idx,1,Name, newQty);
        //Jika tidak, buat item baru pada inventory dengan indeks terkecil
        } else {
            int i = 0;
            while (myInv->getItem(i).getID() != 0)
            {
                i++;
            }
            myInv->setItem(i,1,Name,Qty);
        }
    }
}

void moveCommand(Inventory *myInv,  Craft *myCraft, int slot_inv, int N, int* slot_craft){
    try{
        myCraft->isCraftInvSlotEmty(N, slot_craft);
        if (myInv->getItem(slot_inv).getQuantity() >= N){
            int newQty = myInv->getItem(slot_inv).getQuantity() - N;
            string Name = myInv->getItem(slot_inv).getName();   
            myInv->setItem(slot_inv,1,Name, newQty);

            for (int i=0; i<N; i++){
                myCraft->setItem(slot_craft[i],1,Name,1);
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
        cout << "[C " << myCraft.getItem(i).getName() << " " << myCraft.getItem(i).getQuantity() << "] ";
        if ((i+1) % 3 == 0){
            cout << endl;
        }
    }

    //Show Inventory
    cout << "\nInventory :\n" << endl;
    for (int i=0; i< MAX_Inventory; i++){
        cout << "[I " << myInv.getItem(i).getName() << " " << myInv.getItem(i).getQuantity() << "] ";
        if ((i+1) % 9 == 0){
            cout << endl;
        }
    }
    cout << "-------------------------- buat debug --------------------------" << endl;
}

ListRecipe createRecipe() {
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
                        re1.set_recipe(temp,i,cnt_col);
                        cnt_col++;
                    }
                    else{
                        re1.set_recipe(temp,i,cnt_col);
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

    // //Cara pakai createRecipe
    ListRecipe lr = createRecipe();
    return 0;
} 
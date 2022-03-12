#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Item.hpp"
#include "Inventory.hpp"
#include "Craft.hpp"
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
    if (myInv->getItem(slot_inv).getQuantity() >= N){
        int newQty = myInv->getItem(slot_inv).getQuantity() - N;
        string Name = myInv->getItem(slot_inv).getName();
        myInv->setItem(slot_inv,1,Name, newQty);

        for (int i=0; i<N; i++){
            myCraft->setItem(slot_craft[i],1,Name,1);
        }
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
    cout << endl;
}

// int main(){
//     Inventory *mobitaInv = new Inventory();
//     Craft *mobitaCraft = new Craft();

//     //Give
//     // GIVE <ITEM_NAME> <ITEM_QTY>
//     // GIVE OAK_WOOD 10
//     giveCommand(mobitaInv, "Oak", 15);
//     giveCommand(mobitaInv, "Stick", 21);
//     giveCommand(mobitaInv, "Oak", 16);
//     giveCommand(mobitaInv, "Torch", 65);
//     giveCommand(mobitaInv, "Stick", 2);
//     giveCommand(mobitaInv, "Iron", 10);

//     //Move
//     // MOVE <INVENTORY_SLOT_ID> N <CRAFTING_SLOT_ID_1>
//     // MOVE I0 N C0 C1 C2 ... CN

//     int slot_craft[2] = {4,7};
//     moveCommand(mobitaInv, mobitaCraft, 0, 2, slot_craft);

//     int slot_craft2[3] = {0,1,2};
//     moveCommand(mobitaInv, mobitaCraft, 2, 3, slot_craft2);

//     //Show
//     showCommand(*mobitaInv, *mobitaCraft);

//     return 0;
// }
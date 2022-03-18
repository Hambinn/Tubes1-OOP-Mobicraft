#include <iostream>
#include "Inventory.hpp"
using namespace std;


Inventory::Inventory(){
    for (int i=0; i<MAX_Inventory; i++){
        this->myItem[i] = ItemTotal();
    }
}

Inventory::Inventory(ItemTotal initialItem){
    for (int i=0; i<MAX_Inventory; i++){
        this->myItem[i] = initialItem;
    }
}

Inventory::Inventory(const Inventory& other){
    for (int i=0; i<MAX_Inventory; i++){
        this->myItem[i] = other.myItem[i];
    }
}

Inventory::~Inventory(){

}

ItemTotal Inventory::getItem(int idx){
    return this->myItem[idx];
}


bool Inventory::isFilledTool(int idx){
    return this->getItem(idx).filled_Tool;
}

bool Inventory::isFilledNonTool(int idx){
    return this->getItem(idx).filled_NonTool;
}

string Inventory::getItemName(int idx){
    //Jika di inventory ada Item NonTool
    if (this->isFilledNonTool(idx)){
        return this->getItem(idx).myNonTool.getName();
    } 
    //Jika di inventory ada Item Tool
    else if (this->isFilledTool(idx)){
        return this->getItem(idx).myTool.getName();
    }
    //Jika tidak ada keduanya
    else {
        return "-";
    }
}

ItemNonTool Inventory::getItemNonTool(int idx){
    return this->getItem(idx).myNonTool;
}

void Inventory::setItemNonTool(int idx, int t_id, string t_name, int t_Qty){
    this->myItem[idx].myNonTool.ID = t_id;
    this->myItem[idx].myNonTool.Name = t_name;
    this->myItem[idx].myNonTool.Quantity = t_Qty;
    this->myItem[idx].filled_NonTool = true;
    this->myItem[idx].filled_Tool = false;
}

void Inventory::deleteItemNonTool(int idx){
    this->myItem[idx].myNonTool.ID = 0;
    this->myItem[idx].myNonTool.Name = "-";
    this->myItem[idx].myNonTool.Quantity = 0;
    this->myItem[idx].filled_NonTool = false;
    this->myItem[idx].filled_Tool = false;
}


ItemTool Inventory::getItemTool(int idx){
    return this->getItem(idx).myTool;
}

void Inventory::setItemTool(int idx, int t_id, string t_name, int t_Dty){
    this->myItem[idx].myTool.ID = t_id;
    this->myItem[idx].myTool.Name = t_name;
    this->myItem[idx].myTool.Durability = t_Dty;
    this->myItem[idx].filled_NonTool = false;
    this->myItem[idx].filled_Tool = false;
}

void Inventory::deleteItemTool(int idx){
    this->myItem[idx].myTool.ID = 0;
    this->myItem[idx].myTool.Name = "-";
    this->myItem[idx].myTool.Durability = 0;
    this->myItem[idx].filled_NonTool = false;
    this->myItem[idx].filled_Tool = false;
}

void Inventory::giveItem(ItemNonTool itemNT, int Qty){
    bool found = false;
    int idx = 0;
    if (Qty > 0 && Qty <= 64){

        //Cek apakah item dengan nama "Name" sudah ada di inventory
        for (int i=0; i<MAX_Inventory; i++){
            if(this->getItemName(i) == itemNT.getName() && this->getItemNonTool(i).getQuantity() < 64 ){
                found = true;
                idx = i;
                break;
            }
        }

        //Jika ada, tambah Qty pada item tersebut
        if(found){
            int newQty = this->getItem(idx).myNonTool.getQuantity() + Qty;
            this->setItemNonTool(idx, itemNT.getID(), itemNT.getName(), newQty);

        //Jika tidak, buat item baru pada inventory dengan indeks terkecil
        } else {
            int i = 0;
            while (this->getItem(i).myNonTool.getID() != 0)
            {
                i++;
            }
            if (i > 0 && i < 27){
                this->setItemNonTool(i,itemNT.getID(), itemNT.getName(), Qty);
            } else {
                // jadi throw ntar
                cout << "Slot Inventory Penuh";
            }
        }
    }
}

void Inventory::discardItem(int idx, int Qty){
    //discard Item Non Tool
    if (this->isFilledNonTool(idx)){
        if (this->getItem(idx).myNonTool.getQuantity() > Qty){
            int newQty = this->getItem(idx).myNonTool.getQuantity() - Qty;
            this->myItem[idx].myNonTool.Quantity = newQty;
        } else if (this->getItem(idx).myNonTool.getQuantity() == Qty){
            this->deleteItemNonTool(idx);
        } else {
            //throw
            cout << "jumlah Quantity Item kurang";
        }
    } 
    //discard Item Tool
    else if(this->isFilledTool(idx)){
        if (Qty == 1){
            this->deleteItemTool(idx);
        } else {
            //throw
            cout << "Qty Item Tool tidak valid";
        }
    }
    //Tidak ada Item pada idx
    else {
        //throw
        cout << "tidak ada item";
    }
}

//Move Item dari Inventory ke Inventory
void Inventory::moveItem(int src, int dest){
    if (this->getItemName(src) == "-" || this->getItemName(dest) == "-"){
        //throw
        cout << "slot tidak memiliki item";
    } else {
        int Qty1 = this->getItem(src).myNonTool.getQuantity();
        int Qty2 = this->getItem(dest).myNonTool.getQuantity();

        if (Qty1 + Qty2 <= 64){
            int newQty = Qty1 + Qty2;
            this->myItem[dest].myNonTool.Quantity = newQty;
            this->deleteItemNonTool(src);
        } else {
            int newQty1 = 64 - Qty1;
            int newQty2 = 64;
            this->myItem[src].myNonTool.Quantity = Qty1 - newQty1;
            this->myItem[dest].myNonTool.Quantity = newQty2;
        }
    }
} 
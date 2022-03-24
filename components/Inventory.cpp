#include <iostream>
#include <fstream>
#include <sstream>
#include "Inventory.hpp"
#include "Exception.hpp"
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

void Inventory::isInvSlotIsNotEmpty(int idx) {
    if (!(this->isFilledNonTool(idx) || this->isFilledTool(idx))) {
        throw Exception<int>(2,idx);
    }
}

ItemNonTool Inventory::getItemNonTool(int idx){
    return this->getItem(idx).myNonTool;
}

void Inventory::setItemNonTool(int idx, int t_id, string t_name, int t_Qty, string t_typ){
    this->myItem[idx].myNonTool.ID = t_id;
    this->myItem[idx].myNonTool.Name = t_name;
    this->myItem[idx].myNonTool.Quantity = t_Qty;
    this->myItem[idx].myNonTool.Type = t_typ;
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

void Inventory::setQtyItemNonTool(int idx, int new_Qty){
    this->myItem[idx].myNonTool.Quantity = new_Qty;
}

ItemTool Inventory::getItemTool(int idx){
    return this->getItem(idx).myTool;
}

void Inventory::setItemTool(int idx, int t_id, string t_name, int t_Dty){
    this->myItem[idx].myTool.ID = t_id;
    this->myItem[idx].myTool.Name = t_name;
    this->myItem[idx].myTool.Durability = t_Dty;
    this->myItem[idx].filled_NonTool = false;
    this->myItem[idx].filled_Tool = true;
}

void Inventory::deleteItemTool(int idx){
    this->myItem[idx].myTool.ID = 0;
    this->myItem[idx].myTool.Name = "-";
    this->myItem[idx].myTool.Durability = 0;
    this->myItem[idx].filled_NonTool = false;
    this->myItem[idx].filled_Tool = false;
}

void Inventory::showItem(){
    cout << "\nInventory :\n" << endl;
    for (int i=0; i< MAX_Inventory; i++){
        // Print jika isinya item NonTool
        if (this->isFilledNonTool(i) && !this->isFilledTool(i)){
            cout << "[I " << this->getItemNonTool(i).getName() << " " << this->getItemNonTool(i).getQuantity() << "] ";
            if ((i+1) % 9 == 0){
                cout << endl;
            }
        } 
        
        //Print jika isinya item Tool
        else if (!this->isFilledNonTool(i) && this->isFilledTool(i)){
            cout << "[I " << this->getItemTool(i).getName() << " " << this->getItemTool(i).getDurability() << "] ";
            if ((i+1) % 9 == 0){
                cout << endl;
            }
        }

        //Print jika tidak ada item
        else if (!this->isFilledNonTool(i) && !this->isFilledTool(i)){
            cout << "[I " << "-" << " " << 0 << "] ";
            if ((i+1) % 9 == 0){
                cout << endl;
            }
        }
    }
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
            if (newQty <= 64){
                this->setItemNonTool(idx, itemNT.getID(), itemNT.getName(), newQty, itemNT.getType());
            } else {
                this->setItemNonTool(idx, itemNT.getID(), itemNT.getName(), 64, itemNT.getType());
                int newQty_1 = newQty - 64;
                giveItem(itemNT, newQty_1);
            }
            

        //Jika tidak, buat item baru pada inventory dengan indeks terkecil
        } else {
            int i = 0;
            while (this->getItemName(i) != "-")
            {
                i++;
            }
            if (i >= 0 && i < 27){
                this->setItemNonTool(i,itemNT.getID(), itemNT.getName(), Qty, itemNT.getType());
            } else {
                throw new Exception<string>(1);
            }
        }
    } else {
        int Qty_1 = Qty - 64;
        giveItem(itemNT, 64);
        giveItem(itemNT,Qty_1);
    }
}
void Inventory::giveItem(ItemTool itemT, int Qty){
    if (Qty == 1){
        int i = 0;
        while (this->getItemName(i) != "-")
        {
            i++;
        }
        if (i >= 0 && i < 27){
            this->setItemTool(i, itemT.getID(), itemT.getName(), 10);
        } else {
            throw Exception<string>(1);
        }
    } else {
        throw Exception<string>(4);
    }
}

void Inventory::giveItem(ItemTool itemT, int Qty, int t_Dty){
    if (Qty == 1){
        int i = 0;
        while (this->getItemName(i) != "-")
        {
            i++;
        }
        if (i >= 0 && i < 27){
            this->setItemTool(i, itemT.getID(), itemT.getName(), t_Dty);
        } else {
            throw Exception<string>(1);
        }
    } else {
        throw Exception<string>(4);
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
            throw Exception<int>(5, Qty);
        }
    } 
    //discard Item Tool
    else if(this->isFilledTool(idx)){
        if (Qty == 1){
            this->deleteItemTool(idx);
        } else {
            throw Exception<string>(1);
            cout << "Qty Item Tool tidak valid";
        }
    }
    //Tidak ada Item pada idx
    else {
        throw Exception<int>(6, idx);
    }
}

//Move Item dari Inventory ke Inventory
void Inventory::moveItem(int src, int dest){
    if (src <= 26 && dest <= 26){
        if (this->getItemName(src) == "-" || this->getItemName(dest) == "-"){
            if (this->getItemName(src) == "-"){
                throw Exception<int>(3, src);
            } else if (this->getItemName(dest) == "-"){
                throw Exception<int>(3, dest);
            }
        } else if (this->getItemName(src) != this->getItemName(dest)){
            throw Exception<int>(16, src);
        } else {
            int Qty1 = this->getItem(src).myNonTool.getQuantity();
            int Qty2 = this->getItem(dest).myNonTool.getQuantity();

            if (Qty1 + Qty2 <= 64){
                int newQty = Qty1 + Qty2;
                this->myItem[dest].myNonTool.Quantity = newQty;
                this->deleteItemNonTool(src);
            } else {
                int newQty1 = 64 - Qty2;
                int newQty2 = 64;
                this->myItem[src].myNonTool.Quantity = Qty1 - newQty1;
                this->myItem[dest].myNonTool.Quantity = newQty2;
            }
        }
    }
    else {
        throw Exception<int>(17, src);
    }
} 

void Inventory::useItem(int idx){
    if (this->isFilledTool(idx)){
        this->myItem[idx].myTool.Durability -= 1;
        if (this->getItemTool(idx).getDurability() == 0){
            this->deleteItemTool(idx);
        }
    }
    else {
        throw Exception<int>(2, idx);
    }
}

void Inventory::exportInventory(string fileName) {
    ofstream fileOutput(fileName);
    if (!fileOutput.is_open()){
        throw new Exception<string>(8, fileName);
    }
    for (int i=0; i< MAX_Inventory; i++){
        // Print jika isinya item NonTool
        if (this->isFilledNonTool(i) && !this->isFilledTool(i)){
           fileOutput << this->getItemNonTool(i).getID() << ":" << this->getItemNonTool(i).getQuantity() << endl;
        } 
        
        //Print jika isinya item Tool
        else if (!this->isFilledNonTool(i) && this->isFilledTool(i)){
           fileOutput << this->getItemNonTool(i).getID()  << ":" << this->getItemTool(i).getDurability() << endl;
        }

        //Print jika tidak ada item
        else if (!this->isFilledNonTool(i) && !this->isFilledTool(i)){
           fileOutput << "0:0" << endl;
        }
    }

    fileOutput.close();
}
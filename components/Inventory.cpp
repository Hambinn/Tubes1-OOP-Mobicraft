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
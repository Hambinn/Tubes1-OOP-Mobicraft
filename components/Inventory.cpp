#include <iostream>
#include "Inventory.hpp"
using namespace std;


Inventory::Inventory(){
    for (int i=0; i<MAX_Inventory; i++){
        this->myItem[i] = ItemNonTool();
    }
}

Inventory::Inventory(ItemNonTool initialItem){
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

ItemNonTool Inventory::getItem(int idx){
    return this->myItem[idx];
}

void Inventory::setItem(int idx, int t_id, string t_name, int t_Qty){
    this->myItem[idx].ID = t_id;
    this->myItem[idx].Name = t_name;
    this->myItem[idx].Quantity = t_Qty;

}
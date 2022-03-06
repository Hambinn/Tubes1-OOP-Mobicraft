#include <iostream>
#include "Inventory.hpp"
using namespace std;

Inventory::Inventory(){
    for (int i=0; i<MAX_Inventory; i++){
        this->myItem[i] = Item();
    }
}

Inventory::Inventory(Item initialItem){
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

Item Inventory::getItem(int idx){
    return this->myItem[idx];
}

void Inventory::setItem(int idx, int t_id, string t_name, int t_Qty){
    this->myItem[idx].ID = t_id;
    this->myItem[idx].Name = t_name;
    this->myItem[idx].Quantity = t_Qty;
}

Craft::Craft() : Inventory(){
    for (int i=0; i<MAX_Craft; i++){
        this->craftItem[i] = Item();
    }
}

Craft::Craft(Item initialItem){
    for (int i=0; i<MAX_Craft; i++){
        this->craftItem[i] = initialItem;
    }
}

Craft::Craft(const Craft& other){
    for (int i=0; i<MAX_Craft; i++){
        this->craftItem[i] = other.craftItem[i];
    }
}

Craft::~Craft(){

}

Item Craft::getItem(int idx){
    return this->craftItem[idx];
}

void Craft::setItem(int idx, int t_id, string t_name, int t_Qty){
    this->craftItem[idx].ID = t_id;
    this->craftItem[idx].Name = t_name;
    this->craftItem[idx].Quantity = t_Qty;
}
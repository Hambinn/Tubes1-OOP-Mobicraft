#include <iostream>
#include "Craft.hpp"
using namespace std;

Craft::Craft(){
    for (int i=0; i<MAX_Craft; i++){
        this->craftItem[i] = ItemTotal();
    }
}

Craft::Craft(ItemTotal initialItem){
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

ItemTotal Craft::getItem(int idx){
    return this->craftItem[idx];
}


bool Craft::isFilledTool(int idx){
    return this->getItem(idx).filled_Tool;
}

bool Craft::isFilledNonTool(int idx){
    return this->getItem(idx).filled_NonTool;
}

string Craft::getItemName(int idx){
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

ItemNonTool Craft::getItemNonTool(int idx){
    return this->getItem(idx).myNonTool;
}

void Craft::setItemNonTool(int idx, int t_id, string t_name, int t_Qty){
    this->craftItem[idx].myNonTool.ID = t_id;
    this->craftItem[idx].myNonTool.Name = t_name;
    this->craftItem[idx].myNonTool.Quantity = t_Qty;
    this->craftItem[idx].filled_NonTool = true;
    this->craftItem[idx].filled_Tool = false;
}


ItemTool Craft::getItemTool(int idx){
    return this->getItem(idx).myTool;
}

void Craft::setItemTool(int idx, int t_id, string t_name, int t_Dty){
    this->craftItem[idx].myTool.ID = t_id;
    this->craftItem[idx].myTool.Name = t_name;
    this->craftItem[idx].myTool.Durability = t_Dty;
    this->craftItem[idx].filled_NonTool = false;
    this->craftItem[idx].filled_Tool = false;
}


void Craft::isCraftInvSlotEmty(int N, int* slot_idx){
    int i = 0;
    for (i; i < N; i++){
        if(this->getItemName(i) != "-"){
            throw "gagal mindahin, ada slot craft table yang sudah terisi";
        }
    }
};
#include <iostream>
#include "Craft.hpp"
using namespace std;

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


void Craft::isCraftInvSlotEmty(int N, int* slot_idx){
    int i = 0;
    for (i; i < N; i++){
        if(this->craftItem[slot_idx[i]].Name != "-"){
            throw "gagal mindahin, ada slot craft table yang sudah terisi";
        }
    }
};
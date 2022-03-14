#include <iostream>
#include "Item.hpp"
using namespace std;

Item::Item(){
    this->ID = 0;
    this->Name = "-";
}

Item::Item(int ID, string Name){
    this->ID = ID;
    this->Name = Name;  
}

Item::Item(const Item& other){
    this->ID = other.ID;
    this->Name = other.Name;    
}

int Item::getID(){
    return this->ID;
}
string Item::getName(){
    return this->Name;
}

ItemNonTool::ItemNonTool() : Item(){
    this->Type = "-";
    this->Quantity = 0;
}

ItemNonTool::ItemNonTool(int ID, string Name, string Type, int Quantity) : Item(ID, Name){
    this->Type = Type;
    this->Quantity = Quantity;
}
ItemNonTool::ItemNonTool(const ItemNonTool& other){
    this->ID = other.ID;
    this->Name = other.Name;
    this->Type = other.Type;
    this->Quantity = other.Quantity;
}

string ItemNonTool::getType(){
    return this->Type;
}

int ItemNonTool::getQuantity(){
    return this->Quantity;
}

void ItemNonTool::setType(string Type){
    this->Type = Type;
}

void ItemNonTool::setQuantity(int Qty){
    this->Quantity = Qty;
}

void ItemNonTool::addQuantity(int Qty){
    this->Quantity += Qty;
}

void ItemNonTool::substractQuantity(int Qty){
    this->Quantity -= Qty;
}

ItemTool::ItemTool() : Item(){
    this->Durability = 0;
}

ItemTool::ItemTool(int ID_T, string Name_T, int Durability) : Item(ID_T, Name_T){
    this->Durability = Durability;
}

ItemTool::ItemTool(const ItemTool& other){
    this->ID = other.ID;
    this->Name = other.Name;
    this->Durability = other.Durability;
}

int ItemTool::getDurability(){
    return this->Durability;
}

void ItemTool::setDurability(int Dty){
    this->Durability = Dty;
}

void ItemTool::addDurability(int Dty){
    this->Durability += Dty;
}

void ItemTool::substractDurability(int Dty){
    this->Durability -= Dty;
}
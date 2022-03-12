#include <iostream>
#include "Item.hpp"
using namespace std;

Item::Item(){
    this->ID = 0;
    this->Name = "-";
    this->Quantity = 0;
}

Item::Item(int ID, string Name, int Quantity){
    this->ID = ID;
    this->Name = Name;
    this->Quantity = Quantity;
}

Item::Item(const Item& other){
    this->ID = other.ID;
    this->Name = other.Name;
    this->Quantity = other.Quantity;
}

Item::~Item(){

}

int Item::getID(){
    return this->ID;
}

string Item::getName(){
    return this->Name;
}

int Item::getQuantity(){
    return this->Quantity;
}

void Item::setQuantity(int Qty){
    if (Qty <= 64){
        this->Quantity = Qty;
    }
}

void Item::addQuantity(int Qty){
    if (this->Quantity + Qty <= 64){
        this->Quantity += Qty;
    }
}

void Item::substractQuantity(int Qty){
    if (this-> Quantity - Qty >= 0){
        this->Quantity -= Qty;
    }
}
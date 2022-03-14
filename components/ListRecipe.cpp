#include "ListRecipe.hpp"
#include <iostream>

int ListRecipe::nEff = 0;

ListRecipe::ListRecipe() {
    this->size = 5;
    this->list = new Recipe[this->size];
}

ListRecipe::ListRecipe(int size){
    this->size = size;
    this->list = new Recipe[this->size];
}

ListRecipe::ListRecipe(const ListRecipe& lr){
    this->size = lr.size;
    this->list = new Recipe[this->size];
    nEff = lr.nEff;
    for (int i = 0; i < lr.nEff; i++) {
        this->list[i] = lr.list[i];
    }
}

ListRecipe::~ListRecipe(){
    delete[] list;
}

void ListRecipe::add_recipe(Recipe r) {
    this->list[nEff] = r;
    nEff++;
}

int ListRecipe::get_neff() const {
    return nEff;
}

Recipe ListRecipe::get_recipe(int idx) const{
    return this->list[idx];
}

ListRecipe& ListRecipe::operator=(const ListRecipe& lr) {
    this->size = lr.size;
    nEff = lr.nEff;
    delete[] list;
    this->list = new Recipe[this->size];
    for (int i = 0; i < lr.nEff; i++) {
        this->list[i] = lr.list[i];
    }
    return *this;
}
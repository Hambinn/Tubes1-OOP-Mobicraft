#include "Recipe.hpp"
#include <string>
#include <iostream>

Recipe::Recipe() {
    this->row = 3;
    this->col = 3;
    this->items = new string[this->row*this->col];
    this->itemsMirror = new string[this->row*this->col];
    this->result = "none";
    this->numResult = 0;
}

Recipe::Recipe(int row, int col) {
    this->row = row;
    this->col = col;
    this->items = new string[this->row*this->col];
    this->itemsMirror = new string[this->row*this->col];
    this->result = "none";
    this->numResult = 0;
}

Recipe::Recipe(const Recipe& r) {
    this->items = new string[r.row*r.col];
    this->itemsMirror = new string[r.row*r.col];
    this->row = r.row;
    this->col = r.col;

    for (int i = 0; i < (r.row*r.col); i++) {
        this->items[i] = r.items[i];
    }

    for (int i = 0; i < (r.row*r.col); i++) {
        this->itemsMirror[i] = r.itemsMirror[i];
    }

    this->result = r.result;
    this->numResult = r.numResult;
}

Recipe::~Recipe() {
    delete[] this->items;
    delete[] this->itemsMirror;
}

void Recipe::set_recipe(string item, int row, int col) {
    //to set recipe based on coordinat => elements[row][col] and the mirroring
    int idx = col+row*this->col;
    int idxm = this->col-col-1+(row*this->col);
    this->items[idx] = item;
    this->itemsMirror[idxm] = item;
}

void Recipe::set_result(string result) {
    //set result from the recipe
    this->result = result;
}

void Recipe::set_num_of_result(int numResult) {
    //set num fo result from the recipe
    this->numResult = numResult;
}

string Recipe::get_result() const {
    //get result from the recipe
    return this->result;
}

int Recipe::get_num_of_result() const {
    //get num of result from the recipe
    return this->numResult;
}

int Recipe::get_row() const {
    return this->row;
}

int Recipe::get_col() const {
    return this->col;
}
    
void Recipe::display_recipe() const {
    cout << "-----Original-----" << endl;
    for (int i = 0; i < this->row*this->col; i++) {
        if ((i+1) % this->col == 0){
            cout << this->items[i] << endl;
        }
        else{
            cout << this->items[i] << " ";
        }
    }
    cout << "-----Mirrored-----" << endl;
    for (int i = 0; i < this->row*this->col; i++) {
        if ((i+1) % this->col == 0){
            cout << this->itemsMirror[i] << endl;
        }
        else{
            cout << this->itemsMirror[i] << " ";
        }
    }
}

string Recipe::get_item(int row, int col) const{
    int idx = col+row*this->col;
    return this->items[idx];
}

string Recipe::get_item_mirror(int row, int col) const{
    int idxm = this->col-col-1+(row*this->col);
    return this->itemsMirror[idxm];
}

Recipe& Recipe::operator=(const Recipe& r) {
    this->result = r.result;
    this->numResult = r.numResult;
    this->row = r.row;
    this->col = r.col;
    delete[] this->items;
    delete[] this->itemsMirror;

    this->items = new string[r.row*r.col];
    for (int i = 0; i < (r.row*r.col); i++) {
        this->items[i] = r.items[i];
    }

    this->itemsMirror = new string[r.row*r.col];
    for (int i = 0; i < (r.row*r.col); i++) {
        this->itemsMirror[i] = r.itemsMirror[i];
    }
    return *this;
}

map<string,int> Recipe::get_all_type() const {
    map<string,int> type;
    for (int i = 0 ; i < (this->row*this->col); i++) {
        type[this->items[i]] += 1;
    }
    return type;
}
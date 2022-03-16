#include "Recipe.hpp"
#include <string>
#include <iostream>

Recipe::Recipe() {
    this->row = 3;
    this->col = 3;
    this->items = new string*[3];
    for (int i = 0; i < 3; i++) {
        this->items[i] = new string[3];
    }
    this->itemsMirror = new string*[3];
    for (int i = 0; i < 3; i++) {
        this->itemsMirror[i] = new string[3];
    }

    this->result = "none";
    this->numResult = 0;
}

Recipe::Recipe(int row, int col) {
    this->row = row;
    this->col = col;
    
    this->items = new string*[this->row];
    for (int i = 0; i < this->row; i++) {
        this->items[i] = new string[this->col];
    }

    this->itemsMirror = new string*[this->row];
    for (int i = 0; i < this->row; i++) {
        this->itemsMirror[i] = new string[this->col];
    }

    this->result = "none";
    this->numResult = 0;
}

Recipe::Recipe(const Recipe& r) {
    this->items = new string*[r.row];
    for (int i = 0; i < r.row; i++) {
        this->items[i] = new string[r.col];
    }

    this->itemsMirror = new string*[r.row];
    for (int i = 0; i < r.row; i++) {
        this->itemsMirror[i] = new string[r.col];
    }

    for (int i = 0; i < r.row; i++) {
        for (int j = 0; j < r.col; j++) {
            this->items[i][j] = r.items[i][j];
        }
    }

    for (int i = 0; i < r.row; i++) {
        for (int j = 0; j < r.col; j++) {
            this->itemsMirror[i][j] = r.itemsMirror[i][j];
        }
    }
    this->result = r.result;
    this->numResult = r.numResult;
    this->row = r.row;
    this->col = r.col;
}

Recipe::~Recipe() {
    for (int i = 0; i < this->row; i++) {
        delete[] this->items[i];
    }
    delete[] this->items;

    for (int i = 0; i < this->row; i++) {
        delete[] this->itemsMirror[i];
    }
    delete[] this->itemsMirror;
}

void Recipe::set_recipe(string item, int row, int col) {
    //to set recipe based on coordinat => elements[row][col] and the mirroring
    this->items[row][col] = item;
    this->itemsMirror[row][this->col-col-1] = item;
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
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            if (j != this->col-1) {
                cout << this->items[i][j] << " ";
            }
            else{
                cout << this->items[i][j] << endl;
            }
        }
    }
    cout << "-----Mirrored-----" << endl;
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            if (j != this->col-1) {
                cout << this->itemsMirror[i][j] << " ";
            }
            else{
                cout << this->itemsMirror[i][j] << endl;
            }
        }
    }
}

Recipe& Recipe::operator=(const Recipe& r) {
    this->result = r.result;
    this->numResult = r.numResult;
    this->row = r.row;
    this->col = r.col;

    for (int i = 0; i < this->row; i++) {
        delete[] this->items[i];
    }
    delete[] this->items;

    for (int i = 0; i < this->row; i++) {
        delete[] this->itemsMirror[i];
    }
    delete[] this->itemsMirror;

    this->items = new string*[r.row];
    for (int i = 0; i < r.row; i++) {
        this->items[i] = new string[r.col];
    }

    this->itemsMirror = new string*[r.row];
    for (int i = 0; i < r.row; i++) {
        this->itemsMirror[i] = new string[r.col];
    }

    for (int i = 0; i < r.row; i++) {
        for (int j = 0; j < r.col; j++) {
            this->items[i][j] = r.items[i][j];
        }
    }

    for (int i = 0; i < r.row; i++) {
        for (int j = 0; j < r.col; j++) {
            this->itemsMirror[i][j] = r.itemsMirror[i][j];
        }
    }
    return *this;
}

map<string,int> Recipe::get_all_type() const {
    map<string,int> type;
    for (int i = 0 ; i < this->row; i++) {
        for (int j = 0; j < this->col; j++){
            type[this->items[i][j]] += 1;
        }
    }
    return type;
}


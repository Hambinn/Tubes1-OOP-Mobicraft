#ifndef __RECIPE_HPP__
#define __RECIPE_HPP__

#include <iostream>
#include <string>
using namespace std;

class Recipe{
private:
    string** items;
    string** itemsMirror;
    string result;
    int row;
    int col;
    int numResult;
public:
    Recipe() {
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

    Recipe(int row, int col) {
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

    Recipe(const Recipe& r) {
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
    }

    ~Recipe() {
        for (int i = 0; i < this->row; i++) {
            delete[] this->items[i];
        }
        delete[] this->items;

        for (int i = 0; i < this->row; i++) {
            delete[] this->itemsMirror[i];
        }
        delete[] this->itemsMirror;
    }

    void set_recipe(string item, int row, int col) {
        //to set recipe based on coordinat => elements[row][col] and the mirroring
        this->items[row][col] = item;
        this->itemsMirror[row][this->col-col-1] = item;
    }

    void set_result(string result) {
        //set result from the recipe
        this->result = result;
    }

    void set_num_of_result(int numResult) {
        //set num fo result from the recipe
        this->numResult = numResult;
    }

    string get_result() const {
        //get result from the recipe
        return this->result;
    }

    int get_num_of_result() const {
        //get num of result from the recipe
        return this->numResult;
    }

    void display_recipe() const {
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
        cout << "Result: " << this->result << endl;
    }
};

#endif
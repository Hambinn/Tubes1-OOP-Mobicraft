#ifndef __RECIPE_HPP__
#define __RECIPE_HPP__

#include <iostream>
#include <string>
#include <map>
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
    Recipe();
    Recipe(int row, int col);
    Recipe(const Recipe& r);
    ~Recipe();

    void set_recipe(string item, int row, int col);
    void set_result(string result);
    void set_num_of_result(int numResult);
    string get_result() const;
    int get_num_of_result() const;
    int get_row() const;
    int get_col() const;
    string get_item(int row, int col) const;
    string get_item_mirror(int row, int col) const;
    void display_recipe() const;
    Recipe& operator=(const Recipe& r);
    map<string,int> get_all_type() const;
};

#endif
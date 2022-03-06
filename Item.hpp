#ifndef __ITEM_HPP__
#define __ITEM_HPP__

#include <iostream>
using namespace std;

class Item {
public :
    int ID;
    string Name;
    int Quantity;
public :
    Item();
    Item(int ID, string Name, int Quantity);
    Item(const Item& other);
    ~Item();

    int getID();
    string getName();
    int getQuantity();

    void setQuantity(int Qty);

    void addQuantity(int Qty);
    void substractQuantity(int Qty);

    // Item& operator+=(const Item&);
    // Item& operator-=(const Item&);
};

#endif
#ifndef __INVENTORY_HPP__
#define __INVENTORY_HPP__

#include <iostream>
#include "Item.hpp"

#define MAX_Inventory 27
#define MAX_Craft 9

class Inventory{
private:
    Item myItem[MAX_Inventory];
public:
    Inventory();
    Inventory(Item initialItem);
    Inventory(const Inventory& other);
    ~Inventory();

    virtual Item getItem(int idx);
    virtual void setItem(int idx, int t_id, string t_name, int t_Qty);
    // void giveItem(int idx, Item I);
    // void discardItem(int idx, int Qty);
};

#endif
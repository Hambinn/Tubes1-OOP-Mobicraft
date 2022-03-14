#ifndef __INVENTORY_HPP__
#define __INVENTORY_HPP__

#include <iostream>
#include <vector>
#include "Item.hpp"
using namespace std;

#define MAX_Inventory 27
#define MAX_Craft 9



class Inventory {
private :
    ItemNonTool myItem[MAX_Inventory]; //Ini masih non tool doang, bingung gmn bisa msukin tool ama nontool dua"nya
public:
    Inventory();
    Inventory(ItemNonTool initialItem);
    Inventory(const Inventory& other);
    ~Inventory();

    ItemNonTool getItem(int idx);
    void setItem(int idx, int t_id, string t_name, int t_Qty);
    // void giveItem(int idx, Item I);
    // void discardItem(int idx, int Qty);
};

#endif
#ifndef __CRAFT_HPP__
#define __CRAFT_HPP__

#include <iostream>
#include "Item.hpp"
#include "Inventory.hpp"

class Craft : public Inventory {
private :
    Item craftItem[MAX_Craft];
public :
    Craft();
    Craft(Item initialItem);
    Craft(const Craft& other);
    ~Craft();

    Item getItem(int idx);
    void setItem(int idx, int t_id, string t_name, int t_Qty);

};

#endif
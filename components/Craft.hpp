#ifndef __CRAFT_HPP__
#define __CRAFT_HPP__

#include <iostream>
#include "Item.hpp"
#include "Inventory.hpp"

class Craft{
private :
    ItemNonTool craftItem[MAX_Craft];
public :
    Craft();
    Craft(ItemNonTool initialItem);
    Craft(const Craft& other);
    ~Craft();

    ItemNonTool getItem(int idx);
    void setItem(int idx, int t_id, string t_name, int t_Qty);

    void isCraftInvSlotEmty(int N, int* slot_idx);


};

#endif
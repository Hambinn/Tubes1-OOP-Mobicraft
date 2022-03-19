#ifndef __CRAFT_HPP__
#define __CRAFT_HPP__

#include <iostream>
#include "Item.hpp"
#include "Inventory.hpp"
#include <map>

#define MAX_Craft 9

class Craft{
private :
    ItemTotal craftItem[MAX_Craft];
public :
    Craft();
    Craft(ItemTotal initialItem);
    Craft(const Craft& other);
    ~Craft();

    ItemTotal getItem(int idx);  
    bool isFilledTool(int idx);
    bool isFilledNonTool(int idx);
    string getItemName(int idx);

    string getType(int idx);

    ItemNonTool getItemNonTool(int idx);
    void setItemNonTool(int idx, int t_id, string t_name, int t_Qty);

    ItemTool getItemTool(int idx);
    void setItemTool(int idx, int t_id, string t_name, int t_Dty);

    void isCraftInvSlotEmpty(int N, int* slot_idx);

    bool isCraftInvSlotEmpty(int idx);

    map<string,int> getSumOfToolandNonTool();

    map<string,int> getSumOfType();

    void moveItem(Inventory *myInv, int idx_inv, int N, int* idx_craft);

    void Crafting(Inventory *myInv,  Craft *myCraft);


};

#endif
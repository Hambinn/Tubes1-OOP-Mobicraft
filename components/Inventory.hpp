#ifndef __INVENTORY_HPP__
#define __INVENTORY_HPP__

#include <iostream>
#include <vector>
#include "Item.hpp"
using namespace std;

#define MAX_Inventory 27

class Inventory {
private :
    ItemTotal myItem[MAX_Inventory]; 
public:
    Inventory();
    Inventory(ItemTotal initialItem);
    Inventory(const Inventory& other);
    ~Inventory();

    ItemTotal getItem(int idx);  
    bool isFilledTool(int idx);
    bool isFilledNonTool(int idx);
    string getItemName(int idx);
    void isInvSlotIsNotEmpty(int idx);

    ItemNonTool getItemNonTool(int idx);
    void setItemNonTool(int idx, int t_id, string t_name, int t_Qty, string t_typ);
    void deleteItemNonTool(int idx);
    void setQtyItemNonTool(int idx, int new_Qty);

    ItemTool getItemTool(int idx);
    void setItemTool(int idx, int t_id, string t_name, int t_Dty);
    void deleteItemTool(int idx);

    //Command
    void showItem();
    void giveItem(ItemNonTool itemNT, int Qty);
    void giveItem(ItemTool itemT, int Qty);
    void giveItem(ItemTool itemT, int Qty, int t_Dty);
    void discardItem(int idx, int Qty);
    void moveItem(int src, int dest);                     //Move Item dari Inventory ke Inventory
    void useItem(int idx);
    void exportInventory(string fileName);
 
};

#endif
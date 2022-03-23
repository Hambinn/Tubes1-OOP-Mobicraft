#ifndef __CRAFT_HPP__
#define __CRAFT_HPP__

#include <iostream>
#include "Item.hpp"
#include "Inventory.hpp"
#include "ListRecipe.hpp"
#include "Recipe.hpp"
#include <map>
#include <list>

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
    void setItemNonTool(int idx, int t_id, string t_name, int t_Qty, string t_typ);
    void deleteItemNonTool(int idx);

    ItemTool getItemTool(int idx);
    void setItemTool(int idx, int t_id, string t_name, int t_Dty);
    void deleteItemTool(int idx);

    void deleteAllItem();

    void isCraftInvSlotEmpty(int N, vector<int> slot_idx);

    bool isCraftInvSlotEmpty(int idx);

    map<string,int> getSumOfToolandNonTool();
    map<string,int> getSumOfType();
    map<string,int> getNameAndDurabilityTool();


    // command
    void moveItem(Inventory *myInv, int idx_inv, int N, vector<int> idx_craft);
    void moveItemBack(Inventory *myInv, int idx_inv, int N, vector<int> idx_craft);
    bool findKecocokanRecipe(ListRecipe *resep, int idx_recipe);
    bool findKecocokanRecipeMirrored(ListRecipe *resep, int idx_recipe);
    pair<string,int> Crafting(ListRecipe *resep);
    void showItem();


};

#endif
#ifndef __ITEM_HPP__
#define __ITEM_HPP__

#include <iostream>
using namespace std;

enum Category {
    Tool,
    NonTool,
};

class Item {
public:
    int ID;
    string Name;
public:
    Item();
    Item(int ID, string Name);
    Item(const Item& other);
    // ~Item();

    int getID();
    string getName();

    virtual Category getCategory() = 0;
    // virtual string getType() = 0;
    // virtual void setType(string Type) = 0;
    // virtual int getQuantity() = 0;
    // virtual void setQuantity(int Qty) = 0;
    // virtual int getDurability() = 0;
    // virtual void setDurability(int Dty) = 0;
};

class ItemNonTool : public Item {
public:
    string Type;
    int Quantity;
public:
    ItemNonTool();
    ItemNonTool(int ID, string Name, string Type, int Quantity);
    ItemNonTool(const ItemNonTool& other);

    Category getCategory(){return NonTool;}

    string getType();
    int getQuantity();

    void setType(string Type);
    void setQuantity(int Qty);
    void addQuantity(int Qty);
    void substractQuantity(int Qty);
};

class ItemTool : public Item {
public :
    int Durability;
public :
    ItemTool();
    ItemTool(int ID_T, string Name_T, int Durability);
    ItemTool(const ItemTool& other);

    Category getCategory(){return Tool;}

    int getDurability();

    void setDurability(int Dty);
    void addDurability(int Dty);
    void substractDurability(int Dty);
};

// class ItemTotal : public ItemNonTool, public ItemTool {

// public :
//     ItemTotal();
// };



#endif
#include <iostream>
#include "Craft.hpp"
using namespace std;

Craft::Craft(){
    for (int i=0; i<MAX_Craft; i++){
        this->craftItem[i] = ItemTotal();
    }
}

Craft::Craft(ItemTotal initialItem){
    for (int i=0; i<MAX_Craft; i++){
        this->craftItem[i] = initialItem;
    }
}

Craft::Craft(const Craft& other){
    for (int i=0; i<MAX_Craft; i++){
        this->craftItem[i] = other.craftItem[i];
    }
}

Craft::~Craft(){

}

ItemTotal Craft::getItem(int idx){
    return this->craftItem[idx];
}


bool Craft::isFilledTool(int idx){
    return this->getItem(idx).filled_Tool;
}

bool Craft::isFilledNonTool(int idx){
    return this->getItem(idx).filled_NonTool;
}

string Craft::getItemName(int idx){
    //Jika di inventory ada Item NonTool
    if (this->isFilledNonTool(idx)){
        return this->getItem(idx).myNonTool.getName();
    } 
    //Jika di inventory ada Item Tool
    else if (this->isFilledTool(idx)){
        return this->getItem(idx).myTool.getName();
    }
    //Jika tidak ada keduanya
    else {
        return "-";
    }
}

string Craft::getType(int idx){
    //Jika di inventory ada Item NonTool
    return this->getItem(idx).myNonTool.getType();
}

ItemNonTool Craft::getItemNonTool(int idx){
    return this->getItem(idx).myNonTool;
}

void Craft::setItemNonTool(int idx, int t_id, string t_name, int t_Qty){
    this->craftItem[idx].myNonTool.ID = t_id;
    this->craftItem[idx].myNonTool.Name = t_name;
    this->craftItem[idx].myNonTool.Quantity = t_Qty;
    this->craftItem[idx].filled_NonTool = true;
    this->craftItem[idx].filled_Tool = false;
}

void Craft::deleteItemNonTool(int idx){
    this->craftItem[idx].myNonTool.ID = 0;
    this->craftItem[idx].myNonTool.Name = "-";
    this->craftItem[idx].myNonTool.Quantity = 0;
    this->craftItem[idx].filled_NonTool = false;
    this->craftItem[idx].filled_Tool = false;
}

ItemTool Craft::getItemTool(int idx){
    return this->getItem(idx).myTool;
}

void Craft::setItemTool(int idx, int t_id, string t_name, int t_Dty){
    this->craftItem[idx].myTool.ID = t_id;
    this->craftItem[idx].myTool.Name = t_name;
    this->craftItem[idx].myTool.Durability = t_Dty;
    this->craftItem[idx].filled_NonTool = false;
    this->craftItem[idx].filled_Tool = false;
}

void Craft::deleteItemTool(int idx){
    this->craftItem[idx].myTool.ID = 0;
    this->craftItem[idx].myTool.Name = "-";
    this->craftItem[idx].myTool.Durability = 0;
    this->craftItem[idx].filled_NonTool = false;
    this->craftItem[idx].filled_Tool = false;
}

void Craft::deleteAllTool(){
    for(int i = 0; i < MAX_Craft; i++){
        this->deleteItemTool(i);
    }
};

void Craft::isCraftInvSlotEmpty(int N, int* slot_idx){
    int i = 0;
    for (i; i < N; i++){
        if(this->getItemName(i) != "-"){
            throw "gagal mindahin, ada slot craft table yang sudah terisi";
        }
    }
};

bool Craft::isCraftInvSlotEmpty(int idx){
    return (this->getItemName(idx) == "-");
};

map<string,int> Craft::getSumOfToolandNonTool(){
    map<string,int> type;       // key: Tool atau Nontool, value: jumlahnya
    type["Tool"] = 0;
    type["NonTool"] = 0;

    for (int i = 0 ; i < MAX_Craft; i++) {
        if(this->isCraftInvSlotEmpty(i) == false){
            if(this->getItem(i).filled_NonTool == true){
                type["NonTool"] ++;
            }else{
                type["Tool"] ++;
            }
        }
    }
    return type;
};

map<string,int> Craft::getSumOfType(){
    map<string,int> type;       // key: Type, kalo gaada type, simpen nama itemnya, value: jumlahnya

    for (int i = 0 ; i < MAX_Craft; i++) {
        if(this->isCraftInvSlotEmpty(i) == false){
            if(this->getItem(i).myNonTool.getType() != "-"){
                type[this->getItem(i).myNonTool.getType()] ++;
            }else{
                type[this->getItem(i).myNonTool.getName()] ++;
            }
        }
    }
    return type;
};

map<string,int> Craft::getNameAndDurabilityTool(){
    map<string,int> nameDurability;       // key: nama Item, value: durabilitynya, kalo sama dijumlah

    for (int i = 0 ; i < MAX_Craft; i++) {
        if(this->isCraftInvSlotEmpty(i) == false){
            nameDurability[this->getItem(i).myTool.getName()] = nameDurability[this->getItem(i).myTool.getName()] + this->getItem(i).myTool.getDurability();
        }
    }
    return nameDurability;
};

//Move dari Inventory ke Craft
void Craft::moveItem(Inventory *myInv, int idx_inv, int N, int* idx_craft){
    //Move Item NonTool
    if (myInv->isFilledNonTool(idx_inv)){
        try{
            this->isCraftInvSlotEmpty(N, idx_craft);
            if (myInv->getItemNonTool(idx_inv).getQuantity() >= N){
                int newQty = myInv->getItem(idx_inv).myNonTool.getQuantity() - N;
                myInv->getItem(idx_inv).myNonTool.setQuantity(newQty);
                for (int i=0; i<N; i++){
                    this->setItemNonTool(idx_craft[i], myInv->getItemNonTool(idx_inv).getID() ,myInv->getItemNonTool(idx_inv).getName(),1);
                } 
                if (myInv->getItemNonTool(idx_inv).getQuantity() == 0){
                    myInv->deleteItemNonTool(idx_inv);
                }
            }
        }catch(const char* err){
            cout << err << endl;
        }
    }
    //Move Item Tool
    if (myInv->isFilledTool(idx_inv)){
        try{
            this->isCraftInvSlotEmpty(N, idx_craft);
            if (N == 1){
                this->setItemNonTool(idx_craft[0], myInv->getItemTool(idx_inv).getID() ,myInv->getItemTool(idx_inv).getName(),myInv->getItemTool(idx_inv).getDurability());
                myInv->deleteItemTool(idx_inv);
            }
        }catch(const char* err){
            cout << err << endl;
        }
    }
}

void Craft::Crafting(Inventory *myInv, ListRecipe *resep){
    cout << "CRAFTINGGGG!!!!! :D" << endl;
    map<string,int> allToolNonTool;
    map<string,int>::iterator it;

    allToolNonTool = this->getSumOfToolandNonTool();
    

    /*
    for (it = allToolNonTool.begin(); it != allToolNonTool.end(); it++) {
        cout << it->first << " ";
        cout << it->second << endl;
    }
    */   

    if(allToolNonTool["Tool"] != 0 && allToolNonTool["NonTool"] == 0){
        cout << "isinya tool semuaa" << endl;

        map<string,int> nameAndDurability;
        nameAndDurability = this->getNameAndDurabilityTool();
        this->deleteAllTool();

        if(nameAndDurability.size() != 1){
            cout << "item tool berbeda, gabisa di craft";
        }else{
            cout << "jadi item baru" << endl;
        }

    }else if(allToolNonTool["NonTool"] != 0 && allToolNonTool["Tool"] == 0){
        cout << "isinya nontoolll" << endl;

        map<string,int> allType;
        allType = this->getSumOfType();

        /*
        for (it = allType.begin(); it != allType.end(); it++) {
            cout << it->first << " ";
            cout << it->second << endl;
        }
        cout << allType.size() << endl;
        */
    }else{
        cout << "ada tool & nontoll, gatau harus apa" << endl;
    }
    

};


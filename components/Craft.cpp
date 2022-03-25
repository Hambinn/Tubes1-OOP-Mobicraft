#include <iostream>
#include "Craft.hpp"
#include "Exception.hpp"
// #include <bits/stdc++.h>
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

void Craft::setItemNonTool(int idx, int t_id, string t_name, int t_Qty, string t_typ){
    this->craftItem[idx].myNonTool.ID = t_id;
    this->craftItem[idx].myNonTool.Name = t_name;
    this->craftItem[idx].myNonTool.Quantity = t_Qty;
    this->craftItem[idx].myNonTool.Type = t_typ;
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
    this->craftItem[idx].filled_Tool = true;
}

void Craft::deleteItemTool(int idx){
    this->craftItem[idx].myTool.ID = 0;
    this->craftItem[idx].myTool.Name = "-";
    this->craftItem[idx].myTool.Durability = 0;
    this->craftItem[idx].filled_NonTool = false;
    this->craftItem[idx].filled_Tool = false;
}

void Craft::deleteAllItem(){
    for(int i = 0; i < MAX_Craft; i++){
        if(this->isCraftInvSlotEmpty(i) == false){
            if(this->getItem(i).filled_NonTool == true){
                this->deleteItemNonTool(i);
            }else{
                this->deleteItemTool(i);
            }
        }
    }
};

void Craft::isCraftInvSlotEmpty(int N, vector<int> slot_idx){
    int i = 0;
    for (i; i < N; i++){
        if(this->getItem(slot_idx[i]).filled_NonTool != false || this->getItem(slot_idx[i]).filled_Tool != false){
            throw Exception<string>(7);
        }
    }
};

bool Craft::isCraftInvSlotEmpty(int idx){
    return (this->getItem(idx).filled_NonTool == false && this->getItem(idx).filled_Tool == false);
};

map<string,int> Craft::getSumOfToolandNonTool(){
    map<string,int> type;       // key: Tool atau Nontool, value: jumlahnya
    type["Tool"] = 0;
    type["NonTool"] = 0;

    for (int i = 0 ; i < MAX_Craft; i++) {
        if(this->isCraftInvSlotEmpty(i) == false){
            if(this->isFilledTool(i) != true){
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
        // cout << "masuk sini" << endl;
        // cout << this->getItem(i).myNonTool.getType() << endl;
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
void Craft::moveItem(Inventory *myInv, int idx_inv, int N, vector<int> idx_craft){
    //Move Item NonTool
    if (myInv->isFilledNonTool(idx_inv)){
        try{
            this->isCraftInvSlotEmpty(N, idx_craft);
            myInv->isInvSlotIsNotEmpty(idx_inv);
            if (myInv->getItemNonTool(idx_inv).getQuantity() >= N){
                int newQty = myInv->getItem(idx_inv).myNonTool.getQuantity() - N;
                myInv->setQtyItemNonTool(idx_inv, newQty);
                //myInv->getItem(idx_inv).myNonTool.setQuantity(newQty);
                for (int i=0; i<N; i++){
                    this->setItemNonTool(idx_craft[i], myInv->getItemNonTool(idx_inv).getID() ,myInv->getItemNonTool(idx_inv).getName(),1, myInv->getItemNonTool(idx_inv).getType());
                } 
                if (myInv->getItemNonTool(idx_inv).getQuantity() == 0){
                    myInv->deleteItemNonTool(idx_inv);
                }
            }
            else {
                throw Exception<int>(5, N);
            }
        }catch(Exception<string> &exception){
            exception.printMessage();
        }catch(Exception<int> &exception){
            exception.printMessage();
        }
    }
    //Move Item Tool
    else if (myInv->isFilledTool(idx_inv)){
        try{
            this->isCraftInvSlotEmpty(N, idx_craft);
            if (N == 1){
                this->setItemTool(idx_craft[0], myInv->getItemTool(idx_inv).getID() ,myInv->getItemTool(idx_inv).getName(),myInv->getItemTool(idx_inv).getDurability());
                myInv->deleteItemTool(idx_inv);
            }
        }catch(const char* err){
            cout << err << endl;
        }
    }
    //item not found
    else {
        throw Exception<int>(3, idx_inv);
    }
}

// move item dari craft table ke inventory
void Craft::moveItemBack(Inventory *myInv, int idx_craft, int N, vector<int> idx_inv){
    //Move Item NonTool
    if(this->isFilledNonTool(idx_craft)){
        if(myInv->getItemNonTool(idx_inv[0]).getName() == "-"){
            myInv->setItemNonTool(idx_inv[0],this->getItemNonTool(idx_craft).getID(), this->getItemNonTool(idx_craft).getName(), 1, this->getItemNonTool(idx_craft).getType());
            this->deleteItemNonTool(idx_craft);
        }else if (this->getItemName(idx_craft) == myInv->getItemNonTool(idx_inv[0]).getName()){\
            int newQty = myInv->getItem(idx_inv[0]).myNonTool.getQuantity() + 1;
            if (newQty <= 64){
                myInv->setQtyItemNonTool(idx_inv[0], newQty);
                this->deleteItemNonTool(idx_craft);
            } else {
                throw Exception<int>(1, idx_craft);
            }
        } else {
            throw Exception<int>(16, idx_craft);
        }
    }else if(this->isFilledTool(idx_craft)){ // move item tool
        if(myInv->getItemName(idx_inv[0]) != "-"){
            throw Exception<string>(4);
        }else{
            myInv->setItemTool(idx_inv[0], this->getItemTool(idx_craft).getID(), this->getItemTool(idx_craft).getName(), this->getItemTool(idx_craft).getDurability());
            this->deleteItemTool(idx_craft);
        }
    }
    //item not found
    else {
        throw Exception<int>(3, idx_craft);
    }

}

bool Craft::findKecocokanRecipe(ListRecipe *resep, int idx_recipe){
    bool found = false;
    if((resep->get_recipe(idx_recipe).get_row() == 3) && (resep->get_recipe(idx_recipe).get_col() == 3)){
        found = true;
        int i = 0;
        int j = 0;
        while(i < 3){
            j = 0;
            while(j < 3){
                if((resep->get_recipe(idx_recipe).get_item(i,j) == "-") && (isCraftInvSlotEmpty((3 * i) + j) == false)){
                    found = false;
                    break;
                }else{
                    if(resep->get_recipe(idx_recipe).get_item(i,j) != this->getItem((3 * i) + j).myNonTool.getType()){
                        if(resep->get_recipe(idx_recipe).get_item(i,j) != this->getItem((3 * i) + j).myNonTool.getName()){
                            found = false;
                            break;
                        }
                    }
                }
                j++;
            }
            if(found == false){
                break;
            }else{
                i++;
            }
        }
    }else{
        found = true;
        int i = 0;
        int j, k;
        while(i < MAX_Craft){
            if(this->isCraftInvSlotEmpty(i) == false){
                break;
            }else{
                i++;
            }
        }

        int rowCraft = i / 3;
        int colCraft = i % 3;
        j = 0;
        while(j < resep->get_recipe(idx_recipe).get_row()){
            k = 0;
            while(k < resep->get_recipe(idx_recipe).get_col()){
                if((3 * (rowCraft + j)) + (colCraft + k) > 9){
                    found = false;
                    break;
                }else{
                    if((resep->get_recipe(idx_recipe).get_item(j,k) == "-") && (isCraftInvSlotEmpty((3 * (rowCraft + j)) + (colCraft + k)) == false)){
                        found = false;
                        break;
                    }else{
                        if(resep->get_recipe(idx_recipe).get_item(j,k) != this->getItem((3 * (rowCraft + j)) + (colCraft + k)).myNonTool.getType()){
                            if(resep->get_recipe(idx_recipe).get_item(j,k) != this->getItem((3 * (rowCraft + j)) + (colCraft + k)).myNonTool.getName()){
                                found = false;
                                break;
                            }
                        } 
                    }
                }
                k++;
            }
            if(found == false){
                break;
            }else{
                j++;
            }
        }
    }
    return found;
};

bool Craft::findKecocokanRecipeMirrored(ListRecipe *resep, int idx_recipe){
    bool found = false;
    if((resep->get_recipe(idx_recipe).get_row() == 3) && (resep->get_recipe(idx_recipe).get_col() == 3)){
        found = true;
        int i = 0;
        int j = 0;
        while(i < 3){
            j = 0;
            while(j < 3){
                if((resep->get_recipe(idx_recipe).get_item_mirror(i,j) == "-") && (isCraftInvSlotEmpty((3 * i) + j) == false)){
                    found = false;
                    break;
                }else{
                    if(resep->get_recipe(idx_recipe).get_item_mirror(i,j) != this->getItem((3 * i) + j).myNonTool.getType()){
                        if(resep->get_recipe(idx_recipe).get_item_mirror(i,j) != this->getItem((3 * i) + j).myNonTool.getName()){
                            found = false;
                            break;
                        }
                    }
                }
                j++;
            }
            if(found == false){
                break;
            }else{
                i++;
            }
        }
    }else{
        found = true;
        int i = 0;
        int j, k;
        while(i < MAX_Craft){
            if(this->isCraftInvSlotEmpty(i) == false){
                break;
            }else{
                i++;
            }
        }

        int rowCraft = i / 3;
        int colCraft = i % 3;
        j = 0;
        while(j < resep->get_recipe(idx_recipe).get_row()){
            k = 0;
            while(k < resep->get_recipe(idx_recipe).get_col()){
                if((3 * (rowCraft + j)) + (colCraft + k) > 9){
                    found = false;
                    break;
                }else{
                    if((resep->get_recipe(idx_recipe).get_item_mirror(j,k) == "-") && (isCraftInvSlotEmpty((3 * (rowCraft + j)) + (colCraft + k)) == false)){
                        found = false;
                        break;
                    }else{
                        if(resep->get_recipe(idx_recipe).get_item_mirror(j,k) != this->getItem((3 * (rowCraft + j)) + (colCraft + k)).myNonTool.getType()){
                            if(resep->get_recipe(idx_recipe).get_item_mirror(j,k) != this->getItem((3 * (rowCraft + j)) + (colCraft + k)).myNonTool.getName()){
                                found = false;
                                break;
                            }
                        } 
                    }
                }
                k++;
            }
            if(found == false){
                break;
            }else{
                j++;
            }
        }
    }
    return found;
};

pair<string,int> Craft::Crafting(ListRecipe *resep){
    map<string,int> allToolNonTool;
    map<string,int>::iterator it;
    pair<string,int> result;

    allToolNonTool = this->getSumOfToolandNonTool();
    if(allToolNonTool["Tool"] != 0 && allToolNonTool["NonTool"] == 0){      //tool semua
        map<string,int> nameAndDurability;
        nameAndDurability = this->getNameAndDurabilityTool();

        if(nameAndDurability.size() != 1){
            throw Exception<string>(14);
        }else{
            for (it = nameAndDurability.begin(); it != nameAndDurability.end(); it++) {
                result.first = it->first;
                if(it->second > 10){
                    result.second = 110;
                }else{
                    result.second = 100 + it->second;
                }
            }
            //this->deleteAllItem();
        }

    }else if(allToolNonTool["NonTool"] != 0 && allToolNonTool["Tool"] == 0){        // nontool semua
        map<string,int> allType;
        allType = this->getSumOfType();
        int i = 0;
        string allTypeArray[allType.size()][2];
        map<string,int> type;
        map<string,int>::iterator it1;
        int indexOfResep = 0;
        bool found = false;
        int j, k;

        for (it = allType.begin(); it != allType.end(); it++) {
            allTypeArray[i][0] = it->first;
            allTypeArray[i][1] = to_string(it->second);
            i++;
        }
       
        i = 0;
        while(i < resep->get_neff() && found == false){
            type = resep->get_recipe(i).get_all_type();

            j = 0;
            found = true;
            while(j < allType.size()){
                k = stoi(allTypeArray[j][1]);
                if(type[allTypeArray[j][0]] != k){
                    found = false;
                    break;
                }
                j++;
            }
            if(found == true){
                if(this->findKecocokanRecipe(resep, i) == true){
                    //this->deleteAllItem();
                    result.first = resep->get_recipe(i).get_result();
                    result.second = resep->get_recipe(i).get_num_of_result();
                    break;
                }else{
                    if(this->findKecocokanRecipeMirrored(resep, i) == true){
                        //this->deleteAllItem();
                        result.first = resep->get_recipe(i).get_result();
                        result.second = resep->get_recipe(i).get_num_of_result();
                        break;
                    }else{
                        found = false;
                    }
                }
            }
            i++;
        }
        if(found == false){
            throw Exception<string>(13);
        }

    }else{
        if(allToolNonTool["Tool"] == 0 && allToolNonTool["NonTool"] == 0){
            throw Exception<string>(15);
        }else{
            throw Exception<string>(12);
        }
    }
    return result;
};

void Craft::showItem(){
    cout << "\nCrafting Table :\n" << endl;
    for (int i=0; i< MAX_Craft; i++){
        // Print jika isinya item NonTool
        if (this->isFilledNonTool(i) && !this->isFilledTool(i)){
            cout << "[C " << this->getItemNonTool(i).getName() << " " << this->getItemNonTool(i).getQuantity() << "] ";
            if ((i+1) % 3 == 0){
                cout << endl;
            }
        } 
        
        //Print jika isinya item Tool
        else if (!this->isFilledNonTool(i) && this->isFilledTool(i)){
            cout << "[C " << this->getItemTool(i).getName() << " " << this->getItemTool(i).getDurability() << "] ";
            if ((i+1) % 3 == 0){
                cout << endl;
            }
        }

        //Print jika tidak ada item
        else if (!this->isFilledNonTool(i) && !this->isFilledTool(i)){
            cout << "[C " << "-" << " " << 0 << "] ";
            if ((i+1) % 3 == 0){
                cout << endl;
            }
        }
    }
}

void Craft::giveItemHasilCrafting(Inventory* myInv, ItemNonTool itemNT, int Qty){
    bool found = false;
    bool full = true;
    int idx = 0;
    if (Qty > 0 && Qty <= 64){

        //Cek apakah item dengan nama "Name" sudah ada di inventory
        for (int i=0; i<MAX_Inventory; i++){
            if(myInv->getItemName(i) == itemNT.getName() && myInv->getItemNonTool(i).getQuantity() < 64 ){
                found = true;
                idx = i;
                break;
            } 
        }
        for (int i=0; i<MAX_Inventory; i++){
            if (myInv->getItemName(i) == "-"){
                full = false;
                break;
            } else if (myInv->isFilledNonTool(i) && myInv->getItemName(i) == itemNT.getName() && myInv->getItemNonTool(i).getQuantity() + Qty < 64){
                full = false;
                break;
            }
        }

        if (full){
            throw Exception<int>(1,idx);
        }

        //Jika ada, tambah Qty pada item tersebut
        if(found){
            int newQty = myInv->getItem(idx).myNonTool.getQuantity() + Qty;
            if (newQty <= 64){
                myInv->setItemNonTool(idx, itemNT.getID(), itemNT.getName(), newQty, itemNT.getType());
                this->deleteAllItem();
            } else {
                myInv->setItemNonTool(idx, itemNT.getID(), itemNT.getName(), 64, itemNT.getType());
                int newQty_1 = newQty - 64;
                giveItemHasilCrafting(myInv, itemNT, newQty_1);
            }
            

        //Jika tidak, buat item baru pada inventory dengan indeks terkecil
        } else {
            int i = 0;
            while (myInv->getItemName(i) != "-")
            {
                i++;
            }
            if (i >= 0 && i < 27){
                myInv->setItemNonTool(i,itemNT.getID(), itemNT.getName(), Qty, itemNT.getType());
                this->deleteAllItem();
            } else {
                throw new Exception<string>(1);
            }
        }
    } else {
        int Qty_1 = Qty - 64;
        giveItemHasilCrafting(myInv, itemNT, 64);
        giveItemHasilCrafting(myInv, itemNT,Qty_1);
    }
}
void Craft::giveItemHasilCrafting(Inventory* myInv, ItemTool itemT, int Qty){
    bool full = true;
    for (int i=0; i<MAX_Inventory; i++){
        if (myInv->getItemName(i) == "-"){
            full = false;
            break;
        } 
    }
    if (full){
        throw Exception<int>(1,Qty);
    }
    if (Qty == 1){
        int i = 0;
        while (myInv->getItemName(i) != "-")
        {
            i++;
        }
        if (i >= 0 && i < 27){
            myInv->setItemTool(i, itemT.getID(), itemT.getName(), 10);
            this->deleteAllItem();
        } else {
            throw Exception<string>(1);
        }
    } else {
        throw Exception<string>(4);
    }
}

void Craft::giveItemHasilCrafting(Inventory* myInv, ItemTool itemT, int Qty, int t_Dty){
    bool full = true;
    for (int i=0; i<MAX_Inventory; i++){
        if (myInv->getItemName(i) == "-"){
            full = false;
            break;
        } 
    }
    if (full){
        throw Exception<int>(1,Qty);
    }
    if (Qty == 1){
        int i = 0;
        while (myInv->getItemName(i) != "-")
        {
            i++;
        }
        if (i >= 0 && i < 27){
            myInv->setItemTool(i, itemT.getID(), itemT.getName(), t_Dty);
            this->deleteAllItem();
        } else {
            throw Exception<string>(1);
        }
    } else {
        throw Exception<string>(4);
    }
}


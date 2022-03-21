#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <iterator>
#include "Command.hpp"
#include "Inventory.hpp"
#include "Craft.hpp"
#include "ListRecipe.hpp"
using namespace std;

Command::Command(string s, Inventory* i, Craft* c, vector<ItemNonTool> listItemNonTool, vector<ItemTool> listItemTool){
    this->command = s;
    this->commandParsed = parseCommand(command);
    this->inventory = i;
    this->craft = c;
    this->listItemNonTool = listItemNonTool;
    this->listItemTool = listItemTool;
}

Command::Command(Command& c){
    this->command = c.command;
    this->commandParsed = c.commandParsed;
    this->inventory = c.inventory;
    this->craft = c.craft;
    this->listItemNonTool = c.listItemNonTool;
    this->listItemTool = c.listItemTool;
}

vector<string> Command::parseCommand(string command){
    vector<string> v;
    stringstream ss(command);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    copy(begin, end, back_inserter(v));
    return v;
}

// void Command::show(){
//     inventory->showItem();
// }



void Command::giveCommand(){
    if(this->commandParsed[0] == "SHOW"){ //SHOW
        inventory->showItem();
    }else if(this->commandParsed[0] == "GIVE"){ // GIVE A N
        for(int i = 0;i<this->listItemNonTool.size();i++){
            if(this->listItemNonTool[i].Name == this->commandParsed[1]){
                inventory->giveItem(this->listItemNonTool[i], stoi(this->commandParsed[2]));
                break;
            }
        }
        for(int i = 0;i<this->listItemTool.size();i++){
            if(this->listItemTool[i].Name == this->commandParsed[1]){
                inventory->giveItem(this->listItemTool[i], stoi(this->commandParsed[2]));
                break;
            }
        }
        cout << "\nTidak ada Item yang cocok" << endl;
    }else if(this->commandParsed[0] == "DISCARD"){ // DISCARD A N
        this->commandParsed[1].erase(0,1);
        inventory->discardItem(stoi(this->commandParsed[1]), stoi(this->commandParsed[2]));
    }else if(this->commandParsed[0] == "MOVE"){ // MOVE A N TO B
        if(this->commandParsed[3][0] == 'C' && this->commandParsed[1][0] == 'I'){
            this->commandParsed[1].erase(0,1);
            int n = stoi(this->commandParsed[2]);
            vector<int> slot;
            for(int i=0;i<n;i++){
                slot[i] = stoi(this->commandParsed[i+3]);
            }
            craft->moveItem(this->inventory,stoi(this->commandParsed[1]), n, slot);
        }else if(this->commandParsed[3][0] == 'I' && this->commandParsed[1][0] == 'C'){
            // belom di implemen
        }else if(this->commandParsed[3][0] == 'I' && this->commandParsed[1][0] == 'I'){
            this->commandParsed[1].erase(0,1);
            this->commandParsed[3].erase(0,1);
            inventory->moveItem(stoi(this->commandParsed[1]), stoi(this->commandParsed[2]));
        }
    }else if(this->commandParsed[0] == "USE"){
        this->commandParsed[1].erase(0,1);
        this->inventory->useItem(stoi(this->commandParsed[1]));
    }else if(this->commandParsed[0] == "CRAFT"){
        ListRecipe listRecipe;
        pair<string,int> hasilCraft;
        hasilCraft = craft->Crafting(&listRecipe);

        for (int i = 0; i < listItemTool.size(); i++){
        if (listItemTool[i].getName() == hasilCraft.first){
            inventory->giveItem(listItemTool[i], 1, hasilCraft.second);
            break;
        }
    }
    }else if(this->commandParsed[0] == "EXPORT"){
        cout << "EXPORT" << endl;
    }
}


int main(){
    vector<ItemNonTool> listItemNonTool;
    vector<ItemTool> listItemTool;
    Inventory inventory;
    Craft craft;

    char s[100];
    cin.getline(s, 100);
    Command c(s, &inventory, &craft, listItemNonTool, listItemTool);
    c.giveCommand();
    
    return 0;
}

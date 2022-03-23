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
#include "Exception.hpp"
using namespace std;

Command::Command(string s, Inventory* i, Craft* c, vector<ItemNonTool> listItemNonTool, vector<ItemTool> listItemTool,ListRecipe* l) {
    this->command = s;
    this->commandParsed = parseCommand(command);
    this->inventory = i;
    this->craft = c;
    this->resep = l;
    this->listItemNonTool = listItemNonTool;
    this->listItemTool = listItemTool;
}

Command::Command(Command& c){
    this->command = c.command;
    this->commandParsed = c.commandParsed;
    this->inventory = c.inventory;
    this->craft = c.craft;
    this->resep = c.resep;
    this->listItemNonTool = c.listItemNonTool;
    this->listItemTool = c.listItemTool;
}

void Command::Clear(){
    this->command.clear();
    this->commandParsed.clear();
    // cout << "terdeleded" << endl;
}

void Command::setCommand(string s){
    this->command = s;
    this->commandParsed = parseCommand(command);
}

vector<string> Command::parseCommand(string command){
    vector<string> v;
    stringstream ss(command);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    copy(begin, end, back_inserter(v));
    return v;
}

string Command::getCommandName(){
   return this->commandParsed[0];  
 }

void Command::giveCommand(){
    // cout << getCommandName() << endl;
    try{
        if(this->commandParsed[0] == "SHOW"){ //SHOW
            craft->showItem();
            inventory->showItem();
        }else if(this->commandParsed[0] == "GIVE"){ // GIVE A N
            for(int i = 0;i<this->listItemNonTool.size();i++){
                if(this->listItemNonTool[i].Name == this->commandParsed[1]){
                    inventory->giveItem(this->listItemNonTool[i], stoi(this->commandParsed[2]));
                    break;
                    cout << "\nTidak ada Item yang cocok" << endl;
                }
            }
            for(int i = 0;i<this->listItemTool.size();i++){
                if(this->listItemTool[i].Name == this->commandParsed[1]){
                    inventory->giveItem(this->listItemTool[i], stoi(this->commandParsed[2]));
                    break;
                    cout << "\nTidak ada Item yang cocok" << endl;
                }
            }
            
        }else if(this->commandParsed[0] == "DISCARD"){ // DISCARD A N
            this->commandParsed[1].erase(0,1);
            inventory->discardItem(stoi(this->commandParsed[1]), stoi(this->commandParsed[2]));

        }else if(this->commandParsed[0] == "MOVE"){ // MOVE A N TO B
            if(this->commandParsed[3][0] == 'C' && this->commandParsed[1][0] == 'I'){
                this->commandParsed[1].erase(0,1);
                int n = stoi(this->commandParsed[2]);
                vector<int> slot;
                for(int i=0;i<n;i++){
                    this->commandParsed[i+3].erase(0,1);
                    slot.push_back(stoi(this->commandParsed[i+3]));
                    // slot[i] = stoi(this->commandParsed[i+3]);
                }
                craft->moveItem(inventory,stoi(this->commandParsed[1]), n, slot);
            }else if(this->commandParsed[3][0] == 'I' && this->commandParsed[1][0] == 'C'){
                // belom di implemen
                vector<int> slot;
                this->commandParsed[3].erase(0,1);
                this->commandParsed[1].erase(0,1);
                slot.push_back(stoi(this->commandParsed[1]));
                craft->moveItemBack(inventory,stoi(this->commandParsed[3]), stoi(this->commandParsed[1]), slot);
            }else if(this->commandParsed[3][0] == 'I' && this->commandParsed[1][0] == 'I'){
                this->commandParsed[1].erase(0,1);
                this->commandParsed[3].erase(0,1);
                inventory->moveItem(stoi(this->commandParsed[1]), stoi(this->commandParsed[2]));
            }
        }else if(this->commandParsed[0] == "USE"){
            this->commandParsed[1].erase(0,1);
            this->inventory->useItem(stoi(this->commandParsed[1]));
        }else if(this->commandParsed[0] == "CRAFT"){
            pair<string,int> hasilCraft;
            hasilCraft = craft->Crafting(this->resep);
            bool found = false;
            
            for (int i = 0; i < listItemTool.size(); i++){
                if (listItemTool[i].getName() == hasilCraft.first){
                    inventory->giveItem(listItemTool[i], 1, hasilCraft.second);
                    found = true;
                }
            }
            if(!found){
                for (int i = 0; i < listItemNonTool.size(); i++){
                    if (listItemNonTool[i].getName() == hasilCraft.first){
                        inventory->giveItem(listItemNonTool[i], hasilCraft.second);
                        inventory->showItem();
                        craft->showItem();
                        found = true;
                    }
                }
            }
        }else if(this->commandParsed[0] == "EXPORT"){
            inventory->exportInventory(commandParsed[1]);
        }
        this->command.clear();
        this->commandParsed.clear();
    }catch (Exception<int> &exception) {
        cout << "berhasil catch 1" << endl;
        exception.printMessage();
    } catch (Exception<string> &exception) {
        cout << "berhasil catch 2" << endl;
        exception.printMessage();
    }
}


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <iterator>
#include "Command.hpp"
using namespace std;

Command::Command(string s, Inventory* i, Craft* c){
    this->command = s;
    this->commandParsed = parseCommand();
    this->inventory = i;
    this->craft = c;
}

Command::Command(Command& c){
    this->command = c.command;
    this->commandParsed = c.commandParsed;
    this->inventory = c.inventory;
    this->craft = c.craft;
}

vector<string> Command::parseCommand(){
    vector<string> v;
    stringstream ss(command);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    copy(begin, end, back_inserter(v));
    return v;
}

vector<string> Command::show(vector<string> v){
    vector<string> result;
    return result;
}



void Command::giveCommand(){
    if(this->commandParsed[0] == "SHOW"){
        cout << "SHOW" << endl;
    }else if(this->commandParsed[0] == "GIVE"){
        cout << "GIVE" << endl;
    }else if(this->commandParsed[0] == "DISCARD"){
        cout << "DISCARD" << endl;
    }else if(this->commandParsed[0] == "MOVE"){
        cout << "MOVE" << endl;
    }else if(this->commandParsed[0] == "USE"){
        cout << "USE" << endl;
    }else if(this->commandParsed[0] == "CRAFT"){
        cout << "CRAFT" << endl;
    }else if(this->commandParsed[0] == "EXPORT"){
        cout << "EXPORT" << endl;
    }
}


int main(){
    Inventory inventory;
    Craft craft;
    string s;
    cin >> s;
    Command c(s, &inventory, &craft);
    c.parseCommand();
    c.giveCommand();
    
    return 0;
}

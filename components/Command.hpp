#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "Inventory.hpp"
#include "Craft.hpp"
#include "Item.hpp"
using namespace std;


class Command{
    private:
        string command;
        vector<string> commandParsed;
        Inventory* inventory;
        Craft* craft;
        vector<ItemNonTool> listItemNonTool;
        vector<ItemTool> listItemTool;
    public:
        Command(string s, Inventory* i, Craft* cr, vector<ItemNonTool> listItemNonTool, vector<ItemTool> listItemTool);   
        Command(Command& c);
        vector<string> parseCommand(string command);
        void giveCommand();
        string getCommandName();
        vector<string> give(vector<string>);
        vector<string> discard(vector<string>);
        vector<string> move(vector<string>);
        vector<string> use(vector<string>);
        vector<string> crafts(vector<string>);
        vector<string> exports(vector<string>);
};

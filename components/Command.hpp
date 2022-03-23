#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "Inventory.hpp"
#include "Craft.hpp"
#include "Item.hpp"
#include "ListRecipe.hpp"
using namespace std;


class Command{
    private:
        string command;
        vector<string> commandParsed;
        ListRecipe* resep;
        Inventory* inventory;
        Craft* craft;
        vector<ItemNonTool> listItemNonTool;
        vector<ItemTool> listItemTool;
    public:
        Command(string s, Inventory* i, Craft* cr, vector<ItemNonTool> listItemNonTool, vector<ItemTool> listItemTool,ListRecipe* l );   
        Command(Command& c);
        void Clear();
        void setCommand(string s);
        vector<string> parseCommand(string command);
        void giveCommand();
        string getCommandName();
};

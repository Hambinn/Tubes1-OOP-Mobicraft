#include "ListRecipe.hpp"
#include <iostream>
#include <dirent.h>
#include <fstream>
#include <vector>
using namespace std;

int ListRecipe::nEff = 0;

ListRecipe::ListRecipe() {
    //Read all recipe name and count it
    vector<string> recipe_name;
    vector<string>::iterator it;
    int cnt_recipe = 0;
    struct dirent *d;
    DIR *dr;
    dr = opendir("./config/recipe");
    if(dr!=NULL)
    {
        for(d=readdir(dr); d!=NULL; d=readdir(dr))
        {
            recipe_name.push_back(d->d_name);
            cnt_recipe++;
        }
        closedir(dr);
    }
    else
        cout<<"Error Occurred!" << endl;
    //delete 2 elemen awal yg tidak digunakan
    it = recipe_name.begin();
    recipe_name.erase(it);
    it = recipe_name.begin();
    recipe_name.erase(it);
    cnt_recipe -= 2;
    this->size = cnt_recipe;
    this->list = new Recipe[this->size];

    //get all type from item.txt
    map <string, string> item_to_type;
    string path = "./config/item.txt";
    fstream newfile(path);
    string tp;
    while (getline(newfile,tp)) {
        string s = tp;
        string delimiter = " ";
        size_t pos = 0;
        string token;
        string key = "";
        string value = "";
        int cnt = 0;
        while ((pos = s.find(delimiter)) != string::npos) {
            cnt++;
            token = s.substr(0, pos);
            if (cnt == 2){
                key = token;
            }
            if (cnt == 3) {
                value = token;
            }
            s.erase(0, pos + delimiter.length());
        }
        item_to_type[key] = value;
    }

    //read every recipe from config
    for (auto i = recipe_name.begin(); i != recipe_name.end(); i++){
        string path = "./config/recipe/";
        path += *i;
        fstream newfile(path);
        string tp;
        getline(newfile,tp);
        //get the size
        int row = int(tp[0]) - 48;  //use this because the max size of row is 3
        int col = int(tp[2]) - 48;  //use this because the max size of column is 3
        //create recipe
        Recipe recipe(row,col);
        //read recipe
        for (int i = 0; i < row; i++) {
            getline(newfile,tp);
            string temp = "";
            int cnt_col = 0;
            for (int j = 0; j < tp.length(); j++) {
                if ((tp[j] == ' ') || (j == tp.length()-1)) {
                    if (j == tp.length()-1) {
                        temp += tp[j];
                        if ((item_to_type[temp] == "") || (item_to_type[temp] == "-")){
                            recipe.set_recipe(temp,i,cnt_col);
                        }
                        else{
                            recipe.set_recipe(item_to_type[temp],i,cnt_col);
                        }
                        cnt_col++;
                    }
                    else{
                        if ((item_to_type[temp] == "") || (item_to_type[temp] == "-")){
                            recipe.set_recipe(temp,i,cnt_col);
                        }
                        else{
                            recipe.set_recipe(item_to_type[temp],i,cnt_col);
                        }
                        temp = "";
                        cnt_col++;
                    }
                }
                else{
                    temp += tp[j];
                }
            }
        }
        getline(newfile,tp);
        string temp = "";
        string result;
        int num_of_result;
        for (int i = 0; i < tp.length(); i++) {
            if (tp[i] == ' '){
                result = temp;
                temp = "";
            }
            else if (i == tp.length()-1) {
                temp += tp[i];
                num_of_result = stoi(temp);
            }
            else{
                temp += tp[i];
            }
        }
        newfile.close(); //close the file object
        recipe.set_result(result);
        recipe.set_num_of_result(num_of_result);
        this->list[nEff] = recipe;
        nEff++;
    }
}

ListRecipe::ListRecipe(const ListRecipe& lr){
    this->size = lr.size;
    this->list = new Recipe[this->size];
    nEff = lr.nEff;
    for (int i = 0; i < lr.nEff; i++) {
        this->list[i] = lr.list[i];
    }
}

ListRecipe::~ListRecipe(){
    delete[] list;
}

void ListRecipe::add_recipe(Recipe r) {
    this->list[nEff] = r;
    nEff++;
}

int ListRecipe::get_neff() const {
    return nEff;
}

Recipe ListRecipe::get_recipe(int idx) const{
    return this->list[idx];
}

ListRecipe& ListRecipe::operator=(const ListRecipe& lr) {
    this->size = lr.size;
    nEff = lr.nEff;
    delete[] list;
    this->list = new Recipe[this->size];
    for (int i = 0; i < lr.nEff; i++) {
        this->list[i] = lr.list[i];
    }
    return *this;
}
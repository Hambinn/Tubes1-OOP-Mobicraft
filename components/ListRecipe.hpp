#ifndef _LISTRECIPE_HPP_
#define _LISTRECIPE_HPP_
#include "Recipe.hpp"

class ListRecipe {
private:
    Recipe* list;
    int size;
    static int nEff;

public:
    ListRecipe();
    ListRecipe(int size);
    ListRecipe(const ListRecipe& lr);
    ~ListRecipe();

    void add_recipe(Recipe r);
    int get_neff() const;
    Recipe get_recipe(int idx) const;
    ListRecipe& operator=(const ListRecipe& lr);
};

#endif
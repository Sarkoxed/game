// sarkoxed //
#pragma once

#include <map>

#include "../items/item.hpp"
#include "../items/weapon.hpp"
#include "../items/medkit.hpp"
#include "../items/bandolier.hpp"

class Inventory{
    private:
        unsigned int a_curweight;
        unsigned int a_maxweight;
        unsigned int a_itcount;
        std::map<unsigned int, Item*> a_table;
    public:
        Inventory(unsigned int size = 0, unsigned int max = 0, unsigned int el = 0):a_curweight(size),a_maxweight(max), a_itcount(el){}
        const unsigned int getCurWeight()const { return a_curweight; }

        const unsigned int getMaxWeight()const{return a_maxweight;}
        const unsigned int getCurCount()const{return a_itcount;}
        void add(unsigned int inv, Item* it);
        Item* extract(unsigned int inv);
        std::map<unsigned int, Item*>* getTable() {return &a_table;}

        std::vector<std::string> toString() const;

        Item* operator[](unsigned int inv);
        ~Inventory();
};

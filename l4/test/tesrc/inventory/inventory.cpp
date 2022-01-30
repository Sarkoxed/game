#include "inventory.hpp"

void Inventory::add(unsigned int inv, Item* it){
    auto tmp = a_table.find(inv);
    if(tmp != a_table.end() && a_table[inv] != nullptr){
        throw std::invalid_argument("this cell if full");
    }
    if(it == nullptr){
        a_table[inv] = nullptr;
        return;
    }
    if(a_curweight + it->getWeight() > a_maxweight){
        throw std::out_of_range("not enough stamina");
    }

    a_table[inv] = it;
    a_curweight += it->getWeight();
    a_itcount++;
}


Item* Inventory::extract(unsigned int inv){
    auto tmp = a_table.find(inv);
    if(tmp != a_table.end() && a_table[inv] != nullptr){
       Item* tmp1 = a_table[inv];
       a_table[inv] = nullptr;
       a_curweight -= tmp1->getWeight();
       a_itcount--;
       return tmp1;
    }
    throw std::invalid_argument("this cell is empty");
}


Item* Inventory::operator[](unsigned int inv){
    auto tmp = a_table.find(inv);
    if(tmp != a_table.end() && a_table[inv] != nullptr){
        return a_table[inv];
    }
    throw std::out_of_range("no such an element");
}

std::vector<std::string> Inventory::toString()const{
    std::vector<std::string> ans;
    for(auto i: a_table){
        if(i.second != nullptr){
        ans.push_back(std::to_string(i.first) + " " + std::string(*i.second));
        }
    }
    return ans;
}

Inventory::~Inventory(){
    for(auto i: a_table){
        delete i.second;
    }
}

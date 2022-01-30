#pragma once

#include "character.hpp"
#include <random>

class OpAgent: public Character{
    private:
        std::string a_name;
        unsigned int a_reloadtime; // may be changed via weight
        unsigned int a_strength;
        unsigned int a_curweight;
        Inventory a_inventory;
        Weapon* a_hands;
    public:
        explicit OpAgent(nlohmann::json& js);

        std::string getName() const { return a_name; };
        unsigned int getRelTime() const { return a_reloadtime;};
        unsigned int getStrength() const { return a_strength;};
        unsigned int getCurWeight() const { return a_curweight;};
        Weapon* getHand() const { return a_hands;}

        Inventory& getInventory() {return a_inventory;}

        void setReload(unsigned int rel);
        void changeWeight(unsigned int weigh);      
        void chooseItemToHold(unsigned int num);
        Item* pickItemToHold(Item* item);

        void pickItem(Item* item, unsigned int num);
        Item* throwItem(unsigned int num = 0);
        Item* throwHand();

        void reload(Bandolier& ammo);
        void heal(MedKit& med);
        unsigned int shoot(unsigned int dist);
        
        const bool isTrooper() const override { return true; }
        const bool isBeast() const override { return false; }
        const bool isWild() const override{ return false; };
        const bool isSmart() const override{ return false;};
        const bool isForager() const override{ return false;};

        ~OpAgent(){
            delete a_hands;
        }
};

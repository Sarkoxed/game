#pragma once
#include "character.hpp"

typedef std::vector<std::vector<unsigned int>> bconfig;

class WildBeast: public Character{
    private:
        unsigned int a_damage;
    public:
        explicit WildBeast(nlohmann::json& config);
        unsigned int getDamage() const { return a_damage; };

        const bool isTrooper() const override{ return false; }
        const bool isBeast() const override{ return true; }
        const bool isWild() const override{ return true; };
        const bool isSmart() const override{ return false;};
        const bool isForager() const override{ return false;};

        ~WildBeast() = default;
};

class SmartBeast: public Character{
    private:
        Weapon* a_hands;
    public: 
        explicit SmartBeast(nlohmann::json& config);
        void takeItem(Weapon* item);
        Weapon* throwItem();

        unsigned int shoot(unsigned int dist);
        Weapon* getHand() const{ return a_hands;}

        const bool isTrooper() const override{ return false; }
        const bool isBeast() const override { return true; }
        const bool isWild() const override{ return false; };
        const bool isSmart() const override{ return true;};
        const bool isForager() const override{ return false;};
        ~SmartBeast(){
            delete a_hands;
        };
};

class ForagerBeast: public Character{
    private:
        unsigned int a_strength;
        Inventory a_inventory;
    public:
        explicit ForagerBeast(nlohmann::json& config);
        void pickItem(Item* item, unsigned int num = 0);
        Item* throwItem(unsigned int num);
        Inventory& getInventory(){ return a_inventory;}
        unsigned int getStrenght() const{return a_strength;}

        const bool isTrooper() const override{ return false; }
        const bool isBeast() const override { return true; }
        const bool isWild() const override{ return false; };
        const bool isSmart() const override{ return false;};
        const bool isForager() const override{ return true;};

        ~ForagerBeast() = default;
};

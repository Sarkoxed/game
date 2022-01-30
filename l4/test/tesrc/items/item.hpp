#pragma once

#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <string>
#include <map>

#include "../../../json/single_include/nlohmann/json.hpp"
#include "../../tools/toolib.hpp"

enum class WeaponType: short{
    pistol = 0, 
    rifle = 1, 
    shotgun = 2, 
    canon = 3,
    grenade = 4
};

enum ItemType: short{
    weapon = 0,
    medkit = 1,
    bandolier = 2
};

class Item{
    protected:
        ItemType a_type;
        unsigned int a_weight;
    public:
        unsigned int getWeight() const { return a_weight; };
        virtual const bool isWeapon() const{ return false; }
        virtual const bool isMedkit() const{ return false; }
        virtual const bool isAmmo() const{ return false; }
        virtual ~Item() = default;
        virtual explicit operator std::string()const = 0;

};

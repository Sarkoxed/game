#pragma once

#include "item.hpp"

typedef std::map<WeaponType, std::vector<unsigned int>> wconfig; 

class Weapon: public Item{
    private:
        WeaponType a_name;
        unsigned int a_damage;
        unsigned int a_tshoot;
        unsigned int a_treload;
        unsigned int a_mag;
        unsigned int a_fullmag;
    public:
        explicit Weapon(nlohmann::json& js, WeaponType x = WeaponType::pistol, unsigned int curmag = 0);
        explicit Weapon(const Weapon& vx) = default;
        explicit Weapon(Weapon&& x) = default;

        Weapon& operator=(const Weapon& right) = default;
        Weapon& operator=(Weapon&& right) = default;

        
        unsigned int getCurrentAmmo() const {return a_mag;}
        unsigned int getFullAmmo() const { return a_fullmag;}
        unsigned int getRelTime() const {return a_treload;}
        unsigned int getShootTime() const {return a_tshoot;}
        WeaponType getName() const { return a_name;}


        unsigned int getDamage() const{ return a_damage; };
        void makeShot(unsigned int& time);
        const bool getShotResult(unsigned int dist, unsigned int accuracy, unsigned int radius);
        void reload(unsigned int& ammo, unsigned int& time);

        const bool isWeapon() const override{ return true; }
        const bool isMedkit() const override{ return false; }
        const bool isAmmo() const override{ return false; }

        explicit operator std::string() const override{
            std::string ans;
            switch(a_name){
                case WeaponType::pistol:
                    ans += "pistol ";
                    break;
                case WeaponType::grenade:
                    ans += "grenade ";
                    break;
                case WeaponType::canon:
                    ans+= "canon";
                    break;
                case WeaponType::rifle:
                    ans+="rifle ";
                    break;
                case WeaponType::shotgun:
                    ans+="shotgun ";
                    break;
            }

            ans+= "Weight: " + std::to_string(a_weight);
            ans+= " Damage: " + std::to_string(a_damage);
            ans+= " Time: " + std::to_string(a_tshoot);
            ans+= " Treload: " + std::to_string(a_treload);
            ans+= " Ammo: " + std::to_string(a_mag) + " // " + std::to_string(a_fullmag);
            return ans;
        }

        ~Weapon() = default;
};

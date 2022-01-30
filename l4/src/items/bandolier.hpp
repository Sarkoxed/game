#pragma once

#include "item.hpp"

class Bandolier:public Item{
    private:
        WeaponType a_bullets;
        unsigned int a_maxsize;
        unsigned int a_cursize;
    public:
        explicit Bandolier(WeaponType x = WeaponType::pistol, unsigned int s = 0, unsigned int max = 0, unsigned int w = 0):a_bullets(x),a_maxsize(max),a_cursize(s){
        a_weight = w;
        a_type = bandolier;
        };
        
        explicit Bandolier(const Bandolier& copy) = default;
        explicit Bandolier(Bandolier&& move) = default;
        Bandolier& operator=(const Bandolier& right) = default;
        Bandolier& operator=(Bandolier&& right) = default;

        const bool operator==(Bandolier& right) const {return this ==&right;};
        const bool operator!=(Bandolier& right) const {return this != &right;};

        unsigned int getCurSize() const { return a_cursize;};
        unsigned int getMaxSize() const { return a_maxsize;};
         
        //Bandolier operator+(const Bandolier& right);
        //Bandolier operator+(const unsigned int right);
        void operator-(const unsigned int right);
        void operator-=(unsigned int);
        void operator+=(Bandolier& right);
        void operator+=(const unsigned int);
       
        WeaponType getType() const { return a_bullets; };
        void setType(WeaponType type, unsigned int amo = 0);

        const bool isWeapon() const override{ return false; }
        const bool isMedkit() const override{ return false; }
        const bool isAmmo() const override{ return true; }

        explicit operator std::string() const override{
            std::string ans("Bandolier ");
            switch(a_bullets){
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
            ans += "Weight = "  + std::to_string(a_weight);
            ans += "Bullets: " + std::to_string(a_cursize) + " \\ " + std::to_string(a_maxsize);
            return ans;

        }
        ~Bandolier() = default;
};

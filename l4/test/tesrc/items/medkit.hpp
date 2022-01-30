#pragma once

#include "item.hpp"

class MedKit: public Item{
    private:
        unsigned int a_inchealth;
        unsigned int a_healthtime;
    public:
        explicit MedKit(unsigned int inc = 0,unsigned int ht = 0, unsigned int w = 0):a_inchealth(inc), a_healthtime(ht){
        a_type = medkit;
        a_weight = w; 
        }

        explicit MedKit(const MedKit& mx) = default; 
        explicit MedKit(MedKit&& mx) = default;
MedKit& operator=(const MedKit& rx) = default;
        MedKit& operator=(MedKit&& rx) = default;


        unsigned int getIncHealth() const { return a_inchealth;};
        unsigned int getHealTime() const { return a_healthtime; };
        
        void decHeal(unsigned int& curHeal, unsigned int maxHealth);

        const bool isWeapon() const override{ return false; }
        const bool isMedkit() const override{  return true; }
        const bool isAmmo() const override{ return false; }

        explicit operator std::string() const override{
            std::string ans;
            ans += "MedKit";
            ans += " Weight: " + std::to_string(a_weight);
            ans += " Inc: " + std::to_string(a_inchealth);
            ans += " Time: " + std::to_string(a_healthtime);
            return ans;
        }
        ~MedKit() = default;

};

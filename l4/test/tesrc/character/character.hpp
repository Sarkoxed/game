#pragma once

#include "../inventory/inventory.hpp"
#include "../../tools/toolib.hpp"
#include "../../../json/single_include/nlohmann/json.hpp"

#include <string>

class Character{
    protected:
        unsigned int a_curhealth;
        unsigned int a_maxhealth;
        unsigned int a_curtime;
        unsigned int a_maxtime; 
        unsigned int a_steptime; // may be changed via weight ---!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        unsigned int a_radius;
        unsigned int a_accuracy; // too
    public:
        unsigned int getCurHealth() const { return a_curhealth; };
        unsigned int getMaxHealth() const { return a_maxhealth; };
        unsigned int getCurTime() const { return a_curtime; };
        unsigned int getMaxTime() const { return a_maxtime; };
        unsigned int getStepTime() const { return a_steptime; };
        unsigned int getRadius() const { return a_radius;};
        unsigned int getAccuracy() const { return a_accuracy;};
        
        void recieveDamage(unsigned int dam);
        void resetTime();
        void setStepTime(unsigned int t);        
        void makeStep();
        void decTime(unsigned int t);

        virtual const bool isTrooper() const{ return false; }
        virtual const bool isBeast() const { return false; }
        virtual const bool isWild() const { return false; };
        virtual const bool isSmart() const { return false;};
        virtual const bool isForager() const { return false;};

        virtual ~Character() = default;
        friend std::ostream& operator<<(std::ostream& out, Character& x);
};



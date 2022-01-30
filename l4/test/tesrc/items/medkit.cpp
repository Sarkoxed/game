// sarkoxed //
#include "medkit.hpp"

void MedKit::decHeal(unsigned int& curHeal, unsigned int maxHealth){
    unsigned int ned = maxHealth - curHeal;
    curHeal = curHeal + a_inchealth;
    curHeal = (curHeal >= maxHealth) ? maxHealth : curHeal;
    a_inchealth = (ned > a_inchealth) ? 0 : a_inchealth - ned;
}

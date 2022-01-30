// sarkoxed //
#include <gtest/gtest.h>
#include <cassert>
#include <ostream>
#include <map>

#include "../tesrc/level/level.hpp"

TEST(item, weapon){
    nlohmann::json x = getconf("../config/weapons.json");
    Weapon pist(x, WeaponType::pistol);
    
    // ned
    ASSERT_TRUE(pist.getDamage() == 233); ASSERT_TRUE(pist.getCurrentAmmo() == 0);
    ASSERT_TRUE(pist.getFullAmmo() == 13);
    ASSERT_TRUE(pist.getRelTime() == 230);
    ASSERT_TRUE(pist.getShootTime() == 31);
    ASSERT_TRUE(pist.getWeight() == 15);
    
    unsigned int band = 26, time = 1000;
    pist.reload(band, time); ASSERT_TRUE(band == 13); ASSERT_TRUE(pist.getCurrentAmmo() == 13);

    ASSERT_TRUE(pist.getShotResult(4, 2, 10));

    pist.makeShot(time);
    ASSERT_TRUE(pist.getCurrentAmmo() == 12);
    pist.reload(band, time);
    ASSERT_TRUE(band == 12);
    
    // my
    Weapon y(pist);
    ASSERT_TRUE(y.getCurrentAmmo() == 13);
    time = 0;
    EXPECT_ANY_THROW(pist.makeShot(time));
    ASSERT_FALSE(pist.isMedkit());
}


TEST(item, medkit){
    MedKit x(100, 14, 10);
    ASSERT_TRUE(x.isMedkit());
    ASSERT_TRUE(x.getHealTime() == 14);
    unsigned int ch = 17, mh = 100;
    x.decHeal(ch, mh);
    ASSERT_TRUE(x.getIncHealth() == 17);
    ASSERT_TRUE(ch == 100);
}

TEST(item, bandolier){
    Bandolier x(WeaponType::canon, 3, 5, 100);

    ASSERT_TRUE(x.getCurSize() == 3);
    ASSERT_TRUE(x.getMaxSize() == 5);

    x += 6;
    ASSERT_TRUE(x.getCurSize() == 5);
    ASSERT_TRUE(x.isAmmo());
    x-=1;
    ASSERT_TRUE(x.getCurSize() == 4);
    Bandolier y(WeaponType::canon, 2, 5, 75);
    Bandolier z(WeaponType::pistol, 10, 10, 10);
    
    EXPECT_ANY_THROW(x+=z);
    x+=y;
    ASSERT_TRUE(x.getCurSize() == 5);
    x-=5;
    EXPECT_ANY_THROW(x-=1);

}

TEST(inventory, all){
    auto x = getconf("../config/weapons.json");
    Weapon pist(x, WeaponType::pistol);
    Weapon rifle(x, WeaponType::rifle);
    Bandolier b(WeaponType::canon, 3, 5, 100);
    MedKit m(100, 14, 10);
    
    Inventory ma(0, 200);

    EXPECT_ANY_THROW(ma[3]);
    
    ASSERT_TRUE(ma.getCurWeight() == 0);
    ASSERT_TRUE(ma.getMaxWeight() == 200);

    ma.add(5, &pist);
    ASSERT_TRUE(ma.getCurCount() == 1);
    ASSERT_TRUE(ma.getCurWeight() == 15);

    EXPECT_ANY_THROW(ma.add(5, &rifle));

    ma.add(1, &rifle);
    ma.add(3, &b);
    ma.add(7, &m);

    ASSERT_TRUE(ma[1]->isWeapon());
    ASSERT_TRUE(ma[7]->isMedkit());
    ASSERT_TRUE(ma[3]->isAmmo());

    MedKit* l = dynamic_cast<MedKit*>(ma.extract(7));

    ASSERT_TRUE(l->isMedkit());
    EXPECT_ANY_THROW(ma[7]);
    ASSERT_TRUE(ma.getCurWeight() == pist.getWeight() + rifle.getWeight() + b.getWeight());
    EXPECT_ANY_THROW(ma.extract(10));
    EXPECT_ANY_THROW(ma.add(20, &b));
}

TEST(oper, gg){
    auto x = getconf("../config/weapons.json");
    auto y = getconf("../config/oper.json");

    OpAgent a(y);
    

// --------------- setters + getters 
    std::vector<unsigned int> vals{a.getCurHealth(), a.getMaxHealth(), a.getCurTime(), a.getMaxTime(), a.getStepTime(), a.getRadius(), a.getAccuracy(), a.getRelTime(), a.getStrength(), a.getCurWeight()};
    
    ASSERT_NO_THROW(a.getName());

    a.setStepTime(5);
    ASSERT_TRUE(a.getStepTime() == 5);

    unsigned int l = a.getCurHealth();
    a.recieveDamage(l-3);
    ASSERT_TRUE(a.getCurHealth() == 3);
    EXPECT_ANY_THROW(a.recieveDamage(100));
    ASSERT_TRUE(a.isTrooper());
    ASSERT_FALSE(a.isBeast());

    unsigned int m = a.getRelTime() - 2;
    a.setReload(a.getRelTime() - 2);
    ASSERT_TRUE(a.getRelTime() == m);
    

// -------------- step
    ASSERT_TRUE(a.getCurTime() == a.getMaxTime());
    a.makeStep();
    ASSERT_TRUE(a.getCurTime() == a.getMaxTime() - a.getStepTime());

    a.setStepTime(a.getCurTime() - 2);
    a.makeStep();
    EXPECT_ANY_THROW(a.makeStep());

    a.resetTime();
    ASSERT_TRUE(a.getCurTime() == a.getMaxTime());

// -------------- items
    Weapon pi(x,WeaponType::pistol, 10);
    Weapon g(x,WeaponType::grenade, 2);
    if(a.getStrength() > pi.getWeight() + g.getWeight()){
        std::cout << "im here" << std::endl;
        a.pickItem(&pi, 4);
        a.pickItem(&g, 7);

        EXPECT_ANY_THROW(a.pickItem(&pi, 4));
        ASSERT_TRUE(a.getHand() == nullptr);

        ASSERT_TRUE(a.getCurWeight() == pi.getWeight() + g.getWeight());
        
        a.chooseItemToHold(4);
        
        ASSERT_TRUE(a.getCurWeight() == pi.getWeight() + g.getWeight());
        
        EXPECT_ANY_THROW(a.chooseItemToHold(5)); 
        
        ASSERT_TRUE(a.getHand() == &pi);
        
        
        ASSERT_FALSE(a.getInventory()[7] == nullptr);
        a.throwItem(7);
        EXPECT_ANY_THROW(a.getInventory()[7]);
        
        ASSERT_TRUE(a.getCurWeight() == pi.getWeight());
        a.throwHand();
        ASSERT_TRUE(a.getCurWeight() == 0);
        ASSERT_TRUE(a.getHand()==nullptr);
        
        a.pickItem(&g, 4);
        a.chooseItemToHold(4);
        a.shoot(10);
        ASSERT_TRUE(a.getCurTime() == a.getMaxTime() - a.getHand()->getShootTime());

        EXPECT_ANY_THROW(a.decTime(10000));

        // items
        a.resetTime();
        MedKit apt(a.getMaxHealth(), 100, 2);
        Bandolier bb(WeaponType::grenade, 10, 100, 1);
        a.reload(bb);
        ASSERT_TRUE(bb.getCurSize() == 6);
        a.resetTime();
        a.heal(apt);
        ASSERT_TRUE(apt.getIncHealth() == 0);
        ASSERT_TRUE(a.getCurHealth() == a.getMaxHealth());
    }
    // overweight
    Weapon dd1(x, WeaponType::canon);
    Weapon dd2(x, WeaponType::canon);
    Weapon dd3(x, WeaponType::canon);
    Weapon dd4(x, WeaponType::canon);

    EXPECT_ANY_THROW(a.pickItem(&dd1, 10));
    EXPECT_ANY_THROW(a.pickItem(&dd2, 11));
    EXPECT_ANY_THROW(a.pickItem(&dd3, 12));
    EXPECT_ANY_THROW(a.pickItem(&dd4, 13));

}

TEST(wildbeast, main){
    auto x = getconf("../config/weapons.json");
    auto y = getconf("../config/beasts.json");
    
    WildBeast a(y);
    
    std::vector<unsigned int> vals{a.getCurHealth(), a.getMaxHealth(), a.getCurTime(), a.getMaxTime(), a.getStepTime(), a.getRadius(), a.getAccuracy(), a.getDamage()};

// setters getters
    a.setStepTime(5);
    ASSERT_TRUE(a.getStepTime() == 5);

    unsigned int l = a.getCurHealth();
    a.recieveDamage(l-3);
    ASSERT_TRUE(a.getCurHealth() == 3);
    EXPECT_ANY_THROW(a.recieveDamage(100));
    ASSERT_FALSE(a.isTrooper());
    ASSERT_TRUE(a.isBeast());

// -------------- step
    ASSERT_TRUE(a.getCurTime() == a.getMaxTime());
    a.makeStep();
    ASSERT_TRUE(a.getCurTime() == a.getMaxTime() - a.getStepTime());

    a.setStepTime(a.getCurTime() - 2);
    a.makeStep();
    EXPECT_ANY_THROW(a.makeStep());

    a.resetTime();
    ASSERT_TRUE(a.getCurTime() == a.getMaxTime());
}

TEST(smartbeast, all){
    auto x = getconf("../config/weapons.json");
    auto y = getconf("../config/beasts.json");
 
    SmartBeast b(y);

// --------------- setters + getters 
    std::vector<unsigned int> vals{b.getCurHealth(), b.getMaxHealth(), b.getCurTime(), b.getMaxTime(), b.getStepTime(), b.getRadius(), b.getAccuracy()}; 
    
    b.setStepTime(5);
    ASSERT_TRUE(b.getStepTime() == 5);

    unsigned int l = b.getCurHealth();
    b.recieveDamage(l-3);
    ASSERT_TRUE(b.getCurHealth() == 3);
    EXPECT_ANY_THROW(b.recieveDamage(100));
    ASSERT_FALSE(b.isTrooper());
    ASSERT_TRUE(b.isBeast());


// -------------- step
    ASSERT_TRUE(b.getCurTime() == b.getMaxTime());
    b.makeStep();
    ASSERT_TRUE(b.getCurTime() == b.getMaxTime() - b.getStepTime());

    b.setStepTime(b.getCurTime() - 2);
    b.makeStep();
    EXPECT_ANY_THROW(b.makeStep());

    b.resetTime();
    ASSERT_TRUE(b.getCurTime() == b.getMaxTime());


// items
    Weapon pistol(x,WeaponType::pistol,  10);
    ASSERT_TRUE(b.getHand() == nullptr);
    b.takeItem(&pistol);
    ASSERT_FALSE(b.getHand() == nullptr);

    unsigned int d = b.shoot(10);
    ASSERT_TRUE(b.getHand()->getCurrentAmmo() == 9);
    ASSERT_TRUE(b.getCurTime() == b.getMaxTime() - b.getHand()->getShootTime());    
    
    b.resetTime();
    ASSERT_TRUE(b.getCurTime() == b.getMaxTime());
    Weapon* tmp = b.throwItem();
    ASSERT_TRUE(tmp == &pistol);
    ASSERT_TRUE(b.getHand() == nullptr);
}

TEST(foragerbeast, all){
    auto x = getconf("../config/weapons.json");
    auto y = getconf("../config/beasts.json");
 
    ForagerBeast b(y);

// --------------- setters + getters 
    std::vector<unsigned int> vals{b.getCurHealth(), b.getMaxHealth(), b.getCurTime(), b.getMaxTime(), b.getStepTime(), b.getRadius(), b.getAccuracy()}; 
    
    b.setStepTime(5);
    ASSERT_TRUE(b.getStepTime() == 5);

    unsigned int l = b.getCurHealth();
    std::cout << l << std::endl;
    b.recieveDamage(l-3);
    ASSERT_TRUE(b.getCurHealth() == 3);
    EXPECT_ANY_THROW(b.recieveDamage(100));
    ASSERT_FALSE(b.isTrooper());
    ASSERT_TRUE(b.isBeast());


// -------------- step
    ASSERT_TRUE(b.getCurTime() == b.getMaxTime());
    b.makeStep();
    ASSERT_TRUE(b.getCurTime() == b.getMaxTime() - b.getStepTime());

    b.setStepTime(b.getCurTime() - 2);
    b.makeStep();
    EXPECT_ANY_THROW(b.makeStep());

    b.resetTime();
    ASSERT_TRUE(b.getCurTime() == b.getMaxTime());

// items
    Weapon pistol(x,WeaponType::pistol,  10);
    ASSERT_TRUE(b.getInventory().getCurCount() == 0);
    b.pickItem(&pistol, 3);
    ASSERT_FALSE(b.getInventory()[3] == nullptr);

    b.resetTime();
    ASSERT_TRUE(b.getCurTime() == b.getMaxTime());
    ASSERT_TRUE(b.getInventory().getCurCount() ==1 );
    Weapon* tmp = dynamic_cast<Weapon*>(b.throwItem(3));
    EXPECT_ANY_THROW(b.getInventory()[34]);
    ASSERT_TRUE(tmp == &pistol);
}

TEST(level, fucc){
    auto wep = getconf("../config/weapons.json");
    auto op = getconf("../config/oper.json");
    auto be = getconf("../config/beasts.json");
    auto ma = getconf("../config/map.json");
    Level lvl(ma, wep, op, be, 3);   

    // check for collisions
    unsigned int all = lvl.getOpCount() + lvl.getBeCount();
    unsigned int count = 0;
    SUCCEED();
}

int main(){
    srand(time(0));
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

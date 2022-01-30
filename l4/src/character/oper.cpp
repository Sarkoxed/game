// sarkoxed //
#include "oper.hpp"

OpAgent::OpAgent(nlohmann::json& js){
    unsigned int num = js["a_name"].size();
    num = randint(num-1);
    a_name = std::string(js["a_name"][num]); 
    a_strength = js["a_strength"][num];
    a_maxhealth = js["a_maxhealth"][num];
    try{
        a_curhealth = js["a_curhealth"][num];
    }
    catch(const std::exception& e){
        a_curhealth = a_maxhealth;
    }
    a_maxtime = js["a_maxtime"][num]; 
    try{
        a_curtime = js["a_curtime"][num];
    }
    catch(const std::exception& e){
        a_curtime = a_maxtime;
    } 
    a_steptime = js["a_steptime"][num]; 
    a_radius = js["a_radius"][num];
    a_accuracy = js["a_accuracy"][num]; 
    try{    
        a_reloadtime = js["a_reloadtime"][num];
    }
    catch(const std::exception& e){
        a_reloadtime = 0;
    } 
    a_curweight = 0;
    //try{
    //    a_curweight  = js["a_curweight"][num];
    //}
    //catch(const std::exception& e){
    //    a_curweight = 0;
    //}
    a_hands = nullptr;
    a_inventory = Inventory(0, a_strength, 0);
    if(js.contains("items")){
        auto jj = js["items"];
        if(jj.contains("inventory")){
            for(auto it: jj["inventory"]){
                ItemType type = static_cast<ItemType>(it["type"]);
                Item* tmp;
                if(type == ItemType::weapon){
                    tmp = new Weapon(it, static_cast<WeaponType>(it["a_name"]));
                }
                else if(type == ItemType::medkit){
                    tmp = new MedKit(it["increasing"], it["heltime"], it["a_weight"]);
                }
                else{
                    auto type1 = static_cast<WeaponType>(it["a_name"]);
                    unsigned int sss = it["a_cursize"];
                    unsigned int aaa = it["a_maxsize"];
                    unsigned int bbb = it["a_weight"];
                    tmp = new Bandolier(type1, sss, aaa, bbb);
                }
                pickItem(tmp, it["num"]);
            }
        }

        if(jj.contains("hands")){
            auto it = jj["hands"];
            ItemType type = static_cast<ItemType>(it["type"]);
            Item* tmp;
            if(type == ItemType::weapon){
                tmp = new Weapon(it, static_cast<WeaponType>(it["a_name"]));
            }
            else if(type == ItemType::medkit){
                tmp = new MedKit(it["increasing"], it["heltime"], it["a_weight"]);
            }
            else{
                auto tp = static_cast<WeaponType>(it["a_name"]);
                tmp = new Bandolier(tp, it["a_curs      ize"], it["a_maxsize"], it["a_weight"]);
            }
            pickItemToHold(tmp);
        }
    }
}

void OpAgent::setReload(unsigned int rel){
    a_reloadtime = rel;
}

void OpAgent::changeWeight(unsigned int weigh){
    a_curweight = weigh;
}

void OpAgent::chooseItemToHold(unsigned int num){
    if(a_inventory[num]->isWeapon()){
        Weapon* w = dynamic_cast<Weapon*>(a_inventory.extract(num));
        a_inventory.add(num, a_hands);
        a_hands = w;
        a_reloadtime = w->getRelTime();
        return;
    }
    throw std::invalid_argument("not a weapon");
}

void OpAgent::pickItem(Item* item, unsigned int num){
    if(a_hands != nullptr){
        if(a_hands->getWeight() + a_curweight + item->getWeight() > a_strength){
            throw std::out_of_range("not enough stamina");
        }
    }
    else if(a_curweight + item->getWeight() > a_strength){
        throw std::out_of_range("not enough stamina");
    }
    if(num == 0){
        auto tmp = pickItemToHold(item);
        return;
    }
    a_inventory.add(num, item);
    a_curweight += item->getWeight(); 
}

Item* OpAgent::pickItemToHold(Item *item){
    if(a_hands){
        throw std::invalid_argument("already a hand");
    }
    if(item->isWeapon()){
        Weapon* w = dynamic_cast<Weapon*>(item);
        Item* tmp = a_hands;
        a_hands = w;
        a_curweight += w->getWeight();
        a_reloadtime = w->getRelTime();
        return tmp;
    }
    throw std::invalid_argument("not a weapon");
}

Item* OpAgent::throwItem(unsigned int num){
    if(num == 0){
        Item* tmp = a_hands;
        a_hands = nullptr;
        a_curweight -= tmp->getWeight();
        return tmp;
    }
    Item* tmp = a_inventory.extract(num);
    a_curweight -= tmp->getWeight();
    std::cout << a_curweight << std::endl;
    std::cout << tmp->getWeight() << std::endl; 
    return tmp;
}

Item* OpAgent::throwHand(){
    if(a_hands == nullptr){
        throw std::out_of_range("nothing to throw");
    }
    Item* tmp = a_hands;
    a_hands = nullptr;
    a_curweight -= tmp->getWeight();
    return tmp;
}


void OpAgent::reload(Bandolier& ammo){
    unsigned int a = ammo.getCurSize();
    a_hands->reload(a, a_curtime);
    ammo -= (ammo.getCurSize() - a);
}

void OpAgent::heal(MedKit& med){
    med.decHeal(a_curhealth, a_maxhealth);
}

unsigned int OpAgent::shoot(unsigned int dist){
    a_hands->makeShot(a_curtime);
    if(a_hands->getShotResult(dist, a_accuracy, a_radius)){
        return a_hands->getDamage();
    }
    return 0;
}


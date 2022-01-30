// sarkoxed //
#include "beasts.hpp"


WildBeast::WildBeast(nlohmann::json& js){
    unsigned int num = randint(js["a_maxhealth"].size()-1);
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
        a_damage = js["a_damage"][num];
    }
    catch(const std::exception& e){
        a_damage = randint(200);
    }
}


SmartBeast::SmartBeast(nlohmann::json& js){
    unsigned int num = randint(js["a_maxhealth"].size()-1);
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
    a_hands = nullptr;
    if(js.contains("items")){
        auto jj = js["items"];
        if(jj.contains("hands")){ 
            auto it = jj["hands"];
            Weapon* tmp = new Weapon(it, static_cast<WeaponType>(it["a_name"]));
            takeItem(tmp);
        }
    }
}


ForagerBeast::ForagerBeast(nlohmann::json& js){
    unsigned int num = randint(js["a_maxhealth"].size()-1);
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
        a_strength = js["a_strength"][num];
    }
    catch(const std::exception& e){
        a_strength = 100 + randint(400);
    }
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
                    auto type = static_cast<WeaponType>(it["a_name"]);
                    tmp = new Bandolier(type, it["a_curs      ize"], it["a_maxsize"], it["a_weight"]);
                }
                pickItem(tmp, it["num"]);
            }
        }

     }
}


void SmartBeast::takeItem(Weapon* wep){
    if(a_hands){
        throw std::out_of_range("full hands");
    }
    a_hands = wep;
}

Weapon* SmartBeast::throwItem(){
    Weapon* tmp = a_hands;
    a_hands = nullptr;
    return tmp;
}

unsigned int SmartBeast::shoot(unsigned int dist){
    a_hands->makeShot(a_curtime);
    if(a_hands->getShotResult(dist, a_accuracy, a_radius)){
        return a_hands->getDamage();
    }
    return 0;
}

void ForagerBeast::pickItem(Item* item, unsigned int num){
    if(num == 0){
        num = a_inventory.getCurCount() + 1;
    }
    a_inventory.add(num, item);
}

Item* ForagerBeast::throwItem(unsigned int num){
    return  a_inventory.extract(num);

}

//bconfig readbea(const std::string& filename){
//    std::ifstream fin;
//    fin.open(filename);
//    if(!fin.is_open()){
//        throw std::invalid_argument("no such a file");
//    }
//    
//    bconfig cha;
//    int count;
//    fin >> count;
//    std::string name;
//    while(!fin.eof()){
//        try{
//            unsigned int val;
//            fin >> name;
//            std::vector<unsigned int> vals;
//            for(int i = 0; i < count; i++){
//                fin >> val;
//                vals.push_back(val);
//            }
//            cha.push_back(vals);
//        }
//        catch(const std::exception& e){
//            std::cout << e.what() << std::endl;
//        }
//    }
//    return cha;
//}

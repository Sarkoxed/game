// sarkoxed //

#include "src/character/beasts.hpp"
#include "src/game/game.hpp"
#include "src/items/weapon.hpp"
#include <iostream>


int main(){
    srand(time(0));
   // auto wep = getconf("config/weapons.json");
   // auto op = getconf("config/oper.json");
   // auto be = getconf("config/beasts.json");
   // auto ma = getconf("config/map1.json");

   // Level lvl(ma, wep, op, be, 3);
 
    std::cout << sizeof(MedKit) << std::endl;
    std::cout << sizeof(Weapon) << std::endl;
    std::cout << sizeof(Bandolier) << std::endl;
    std::cout << sizeof(Character) << std::endl;
    std::cout << sizeof(OpAgent) << std::endl;
    std::cout << sizeof(WildBeast) << std::endl;
    std::cout << sizeof(ForagerBeast) << std::endl;
    std::cout << sizeof(SmartBeast) << std::endl;
    std::cout << sizeof(Inventory) << std::endl;
    std::cout << sizeof(Item) << std::endl;
    
   std::string ccccc;
   std::cin >> ccccc;
   nlohmann::json cc = getconf(ccccc);
   Level lvl(cc);
    std::cout << lvl;
    lvl.save("kuka");

    Game g(lvl);
    while(true){
        int choice;
        std::cin >> choice;
        std::vector<Actions> a = {Actions::skip,Actions::mup, Actions::mdown, Actions::mright, Actions::mleft, Actions::picki, Actions::heal, Actions::reload, Actions::shootxy, Actions::throwi};
        if(choice == 20){
            break;
        }
        if(!g.getEnd()){
            unsigned int x = 0, y = 0;
            if(choice == 8){
                std::cin >> x >> y;
            }
            else if(choice == 5 || choice == 6 || choice == 7 || choice == 9){
                std::cin >> x;
            }
            
            g.action(a[choice], x, y);
            std::cout << lvl << std::endl;
            lvl.save("rara");
        }
        else{
            g.newRound();
        }
    }
}

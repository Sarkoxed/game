#pragma once
#include <vector>
#include <list>
#include <cmath>
#include <stdlib.h>

#include "../character/oper.hpp"
#include "../character/beasts.hpp"
#include "../template/vector.hpp"

enum cellType: short{
    floo = 0,
    wall = 1,
    glass = 2,
    baffle = 3,
    storage = 4
};

struct Cell{
    cellType a_type;
    std::list<Item*> l_items;
    Character* p_player;
};

struct Field{
    std::vector<Vec<Cell>> a_field;
    unsigned int width;
    unsigned int height;
};

class Level{
    private:
        Field a_field;
        std::list<std::pair<OpAgent*, std::pair<unsigned int, unsigned int>>> l_players;
        std::list<std::pair<Character*, std::pair<unsigned int, unsigned int>>> l_enemies;
    public:
        explicit Level(const nlohmann::json& js);
        explicit Level(nlohmann::json& mconf, nlohmann::json& wconf, nlohmann::json& opconf, nlohmann::json& bconf, unsigned int playernum);


        std::pair<unsigned int, unsigned int> getSize() const { return std::pair<unsigned int, unsigned int>(a_field.width, a_field.height);}

        void setSize(std::pair<unsigned int, unsigned int>);
        
        cellType getCellType(std::pair<unsigned int, unsigned int>) const;
        void setCellType(unsigned int x, unsigned int y, cellType t);

        void addItemToCell(unsigned int x, unsigned int y, Item* item);
        Item* getItemFromCell(unsigned int x, unsigned int y);
        std::list<std::pair<OpAgent*, std::pair<unsigned int, unsigned int>>>& getPlayers(){return l_players;}
        std::list<std::pair<Character*, std::pair<unsigned int, unsigned int>>>& getEnemies(){return l_enemies;}

        Field& getField(){return a_field;}
 
        unsigned int getOpCount(){return l_players.size();};
        unsigned int getBeCount(){return l_enemies.size();};
        
        void destroy(unsigned int x, unsigned int y);
        void attack(unsigned int x, unsigned int y, unsigned int x1, unsigned int y1);
        void changeCell(unsigned int x, unsigned int y, unsigned int x1, unsigned int y1);
        void pickItem(unsigned int x, unsigned int y, unsigned int num, Item* it);
        void pickHand(unsigned int x, unsigned int y, unsigned int num);
        void throwItem(unsigned int x, unsigned int y, unsigned int num);
        void throwItem(unsigned int x, unsigned int y, Item* it);
        void throwHand(unsigned int x, unsigned int y);
        void handToInv(unsigned int x, unsigned int y, unsigned int num);

        std::vector<std::string> getInv(unsigned int, unsigned int) const;
        std::vector<std::string> getIt(unsigned int, unsigned int) const;

        void save(const std::string& filename);
        
        friend class Game;
        ~Level();  

        friend std::ostream& operator<<(std::ostream& out, const Level& x);
};

std::list<Item*> genRandomThings(nlohmann::json& wconf);
nlohmann::json mapmap(const nlohmann::json& js);
nlohmann::json getJsonOfItems(OpAgent* agent);

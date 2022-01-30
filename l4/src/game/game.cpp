// sarkoxed //
#include "game.hpp"

// move up - 1
// move down - 2
// move right - 3
// move left - 4
// pick and object
Character* Game::getCurPlayer(){
    if(a_team){
        return l_curplayer->first; 
    }
    return l_curenemy->first;
}

std::pair<unsigned int, unsigned int> Game::getCurPos(){
    if(a_team){
        return l_curplayer->second;
    }
    return l_curenemy->second;
}


void Game::newRound(){
    std::list<std::pair<OpAgent*, std::pair<unsigned int, unsigned int>>> dead;
    for(auto i: l_lvl.getPlayers()){
        if(i.first->getCurHealth() != 0){
            i.first->resetTime();
        }
        else{
            dead.push_back(i);
        }
    }
    l_lvl.getPlayers().remove_if([](std::pair<OpAgent*, std::pair<unsigned int, unsigned int>> x){return x.first->getCurHealth() == 0;});
    
    Field& fi = l_lvl.getField();
    for(auto i: dead){
        unsigned int x, y;
        x = i.second.first;
        y = i.second.second;
        for(auto it: *(i.first->getInventory()).getTable()){
            l_lvl.throwItem(x, y, it.second);
        }
        if(i.first->getHand()){
            l_lvl.throwItem(x,y, i.first->getHand());
        }
        auto tmp = fi.a_field[x][y].p_player;
        l_lvl.a_field.a_field[x][y].p_player = nullptr;
        delete tmp;
    }


    std::list<std::pair<Character*, std::pair<unsigned int, unsigned int>>> dead1;
    for(auto i: l_lvl.getEnemies()){
        if(i.first->getCurHealth() != 0){
            i.first->resetTime();
        }
        else{
            dead1.push_back(i);
        }
    }
    l_lvl.getEnemies().remove_if([](std::pair<Character*, std::pair<unsigned int, unsigned int>> x){return x.first->getCurHealth() == 0;});
    
    for(auto i: dead1){
        unsigned int x, y;
        x = i.second.first;
        y = i.second.second;
        
        if(i.first->isForager()){
            for(auto it: *(dynamic_cast<ForagerBeast*>(i.first)->getInventory()).getTable()){
                l_lvl.throwItem(x, y, it.second);
            }
        }
        if(i.first->isSmart() && dynamic_cast<SmartBeast*>(i.first)->getHand()){
            l_lvl.throwItem(x,y, dynamic_cast<SmartBeast*>(i.first)->getHand());
        }
        auto tmp = fi.a_field[x][y].p_player;
        fi.a_field[x][y].p_player = nullptr;
        delete tmp;
    }
    l_curplayer = l_lvl.l_players.begin();
    l_curenemy = l_lvl.l_enemies.begin();
    a_team = true;
    a_endr = false;
}

void Game::action(Actions act, unsigned int x1, unsigned int y1){
    bool sk = false;
    unsigned int a_x, a_y;
    if(a_team){
        a_x = l_curplayer->second.first; 
        a_y = l_curplayer->second.second;
        std::cout << *l_curplayer->first << std::endl;
        std::cout << dynamic_cast<OpAgent*>(l_curplayer->first)->getCurWeight() << " werignhf" << std::endl;
        if(l_curplayer->first->getCurHealth() == 0){
            act = Actions::skip;
        }
    }
    else{
        a_x = l_curenemy->second.first; 
        a_y = l_curenemy->second.second;
        std::cout << *l_curenemy->first << std::endl;
        if(l_curenemy->first->getCurHealth() == 0){
            act = Actions::skip;
        }
    }
    std::cout << a_x << " " << a_y << "current" << std::endl;

    switch(act){
        case Actions::mup:
            {
                try{
                    l_lvl.changeCell(a_x, a_y, a_x -1, a_y);
                }
                catch(const std::exception&  e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
        case Actions::mdown:
            {
                try{
                    l_lvl.changeCell(a_x, a_y, a_x+1, a_y);
                } catch(const std::exception&  e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
        case Actions::mleft:
            {
                try{
                    l_lvl.changeCell(a_x, a_y, a_x, a_y-1);
                }
                catch(const std::exception&  e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
        case Actions::mright:
            {
                try{
                    l_lvl.changeCell(a_x, a_y, a_x, a_y+1);
                }
                catch(const std::exception&  e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
        case Actions::shootxy:
            {
                try{
                    l_lvl.attack(a_x, a_y, x1, y1);
                }
                catch(const std::exception&  e){
                    std::cout << e.what() << std::endl;
                }
                break;

            }
        case Actions::picki:
            {
                try{
                    l_lvl.pickItem(a_x, a_y, x1, l_lvl.getField().a_field[a_x][a_y].l_items.front());
                    l_lvl.getField().a_field[a_x][a_y].l_items.pop_front();
                }
                catch(const std::exception&  e){
                    std::cout << e.what() << std::endl;
                }
                break;
            }
        case Actions::reload:
            {
                try{
                    auto op = dynamic_cast<OpAgent*>(l_lvl.getField().a_field[a_x][a_y].p_player);
                    op->reload(*dynamic_cast<Bandolier*>(op->getInventory()[x1]));
                }
                catch(const std::exception&  e){
                    std::cout << e.what() << std::endl;
                }
                break;
 
            }
        case Actions::heal:
            {
                try{
                    auto op = dynamic_cast<OpAgent*>(l_lvl.getField().a_field[a_x][a_y].p_player);
                    op->heal(*dynamic_cast<MedKit*>(op->getInventory()[x1]));
                }
                catch(const std::exception&  e){
                    std::cout << e.what() << std::endl;
                }
                break;
 
            }
        case Actions::skip:
            {
                sk = true;
                break;
            }
        case Actions::throwi:
            {
                try{
                    auto r = l_lvl.getField().a_field[a_x][a_y].p_player;
                    if(r->isTrooper()){
                        auto ka = dynamic_cast<OpAgent*>(r);
                        if(x1 != 0){
                            auto tm = ka->throwItem(x1);
                            l_lvl.getField().a_field[a_x][a_y].l_items.push_back(tm);
                        }
                        else{
                            l_lvl.getField().a_field[a_x][a_y].l_items.push_back(ka->throwHand());
                        }
                    }
                    else if(r->isForager()){
                        auto ka = dynamic_cast<ForagerBeast*>(r);
                        l_lvl.getField().a_field[a_x][a_y].l_items.push_back(ka->throwItem(x1));
                    }
                    else if(r->isSmart()){
                        auto ka = dynamic_cast<SmartBeast*>(r);
                        l_lvl.getField().a_field[a_x][a_y].l_items.push_back(ka->throwItem());
                    }
                }
                catch(const std::exception&  e){
                    std::cout << e.what() << std::endl;
                }
                break;          
            }
        default:
            break;
    }
    checkRound(sk);
    if(!a_endr){
        if(a_team){
            a_x = l_curplayer->second.first; 
            a_y = l_curplayer->second.second;
            std::cout << *l_curplayer->first << std::endl;
        }
        else{
            a_x = l_curenemy->second.first; 
            a_y = l_curenemy->second.second;
            std::cout << *l_curenemy->first << std::endl;
        }
        std::cout << a_x << " " << a_y << "step_done" << std::endl;
    }
    else{
        std::cout << "end  of round " << std::endl;
    }
    
}

void Game::checkRound(bool skip){
    if(!a_team && (l_curenemy->first->getCurTime() == 0 || skip)){
        ++l_curenemy;
    }
    if(!a_team && l_curenemy == l_lvl.l_enemies.end()){
        a_endr = true;
    }
    if(a_team && (l_curplayer->first->getCurTime() == 0 || skip)){
       ++l_curplayer; 
    }
    if(a_team && l_curplayer == l_lvl.l_players.end()){
        a_team = false;
    }
}

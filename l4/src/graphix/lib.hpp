#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../game/game.hpp"

const int st = 6, it = 5, inv = 10;
const int size = 128;
const int chsize = 25;

struct ims{
    sf::Image troop_im;
    sf::Image wall_im;
    sf::Image wild_im;
    sf::Image forager_im;
    sf::Image smart_im;
    sf::Image floor_im;
    sf::Image glass_im;
    sf::Image baffle_im;
    sf::Image john_im;
    sf::Image khan_im;
    sf::Image anzan_im;
    sf::Image slava_im;
    sf::Image mark_im;
    sf::Image gun_im;
    sf::Image white_im;
    sf::Image grey_im;
    sf::Image deadbe_im;
    sf::Image deadp_im;
    sf::Image pad_im;
    sf::Image win_im;
    sf::Image lose_im;
};    

struct texs{

    sf::Texture grey_tex;

    sf::Texture troop_tex;
    sf::Texture wall_tex;
    sf::Texture wild_tex;
    sf::Texture smart_tex;
    sf::Texture forager_tex;
    sf::Texture floor_tex;
    sf::Texture glass_tex;
    sf::Texture baffle_tex;
    sf::Texture john_tex;
    sf::Texture khan_tex;
    sf::Texture anzan_tex;
    sf::Texture slava_tex;
    sf::Texture mark_tex;
    sf::Texture gun_tex;
    sf::Texture white_tex;
    sf::Texture deadbe_tex;
    sf::Texture deadp_tex;
    sf::Texture pad_tex; 
    sf::Texture win_tex;
    sf::Texture lose_tex;
};

texs getTex(ims& im);
ims getIms();

void redrawPlane(Game& game, sf::RenderWindow& window, texs& tex, sf::Sprite& sprite);
sf::Texture getName(const std::string& name, texs& tex);
void drawstats(Game& game, sf::RenderWindow& window);



std::vector<std::string> getStats(Character* cha);
void handleEvents(Game& game, sf::RenderWindow& window, sf::Event& event, texs& tex);
void drawInv(Game& game, sf::RenderWindow& window, texs& tex);
void drawItems(Game& game, sf::RenderWindow& window, texs& tex);
void drawPad(Game&, sf::RenderWindow& window, texs& tex);
void drawWin(sf::RenderWindow&, texs& tex);
void drawLose(sf::RenderWindow&, texs& tex);

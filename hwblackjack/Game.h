#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "House.h"
#include "Player.h"

class Game {
private:
    Deck deck;
    House house;
    Player player;

public:
    Game(const std::string& playerName);
    ~Game();
    void play();
};

#endif
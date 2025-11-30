#include "Game.h"
#include <iostream>

Game::Game(const std::string& playerName) : player(playerName) {
    deck.populate();
    deck.shuffle();
}

Game::~Game() {}

void Game::play() {
    // Deal initial 2 cards to everyone
    for (int i = 0; i < 2; ++i) {
        deck.deal(player);
        deck.deal(house);
    }
    
    // Hide dealer's first card
    house.flipFirstCard();
    
    // Display everyone's hands
    std::cout << player << std::endl;
    std::cout << house << std::endl;
    
    // Deal additional cards to player
    deck.additionalCards(player);
    
    // Reveal dealer's first card
    house.flipFirstCard();
    std::cout << std::endl << house << std::endl;
    
    // Deal additional cards to dealer
    deck.additionalCards(house);
    
    if (house.isBusted()) {
        if (!player.isBusted()) {
            player.win();
        }
    } else {
        if (!player.isBusted()) {
            if (player.getTotal() > house.getTotal()) {
                player.win();
            } else if (player.getTotal() < house.getTotal()) {
                player.lose();
            } else {
                player.push();
            }
        } else {
            player.lose();
        }
    }
    
    // Clear hands for next round
    player.clearHand();
    house.clearHand();
}
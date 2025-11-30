#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <vector>

class Card {
public:
    enum RANK { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
    enum SUIT { CLUBS, DIAMONDS, HEARTS, SPADES };
    
private:
    RANK rank;
    SUIT suit;
    bool isFaceUp;

public:
    Card(RANK rank = ACE, SUIT suit = SPADES, bool isUp = true);
    int getValue() const;
    void flip();
    
    // Friend function for overloaded << operator
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
};

#endif
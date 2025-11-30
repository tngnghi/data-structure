#ifndef DECK_H
#define DECK_H

#include "Hand.h"
#include "GenericPlayer.h"

class Deck : public Hand {
public:
    Deck();
    virtual ~Deck();
    void populate();
    void shuffle();
    void deal(Hand& aHand);
    void additionalCards(GenericPlayer& aGenericPlayer);
};

#endif
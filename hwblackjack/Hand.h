#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include <vector>

class Hand {
protected:
    std::vector<Card*> cardVector;

public:
    Hand();
    virtual ~Hand();
    void add(Card* cardPtr);
    void clearHand();
    int getTotal() const;
};

#endif
#include "Hand.h"
#include <vector>

Hand::Hand() {
    cardVector.reserve(7);
}

Hand::~Hand() {
    clearHand();
}

void Hand::add(Card* cardPtr) {
    cardVector.push_back(cardPtr);
}

void Hand::clearHand() {
    for (std::vector<Card*>::iterator iter = cardVector.begin(); iter != cardVector.end(); ++iter) {
        delete *iter;
        *iter = NULL;
    }
    cardVector.clear();
}

int Hand::getTotal() const {
    if (cardVector.empty()) return 0;
    
    if (cardVector[0]->getValue() == 0) return 0;
    
    int total = 0;
    bool hasAce = false;
    
    for (std::vector<Card*>::const_iterator iter = cardVector.begin(); iter != cardVector.end(); ++iter) {
        total += (*iter)->getValue();
        if ((*iter)->getValue() == Card::ACE) {
            hasAce = true;
        }
    }
    
    if (hasAce && total <= 11) {
        total += 10;
    }
    
    return total;
}
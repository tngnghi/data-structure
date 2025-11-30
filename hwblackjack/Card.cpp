#include "Card.h"

Card::Card(RANK r, SUIT s, bool isUp) : rank(r), suit(s), isFaceUp(isUp) {}

int Card::getValue() const {
    if (!isFaceUp) return 0;
    
    if (rank >= TEN) return 10;
    return rank;
}

void Card::flip() {
    isFaceUp = !isFaceUp;
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    const std::string RANKS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
    const std::string SUITS[] = { "C", "D", "H", "S" };
    
    if (card.isFaceUp) {
        os << RANKS[card.rank] << SUITS[card.suit];
    } else {
        os << "XX";
    }
    
    return os;
}
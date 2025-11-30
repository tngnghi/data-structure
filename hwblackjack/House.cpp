#include "House.h"
#include <iostream>

House::House(const std::string& name) : GenericPlayer(name) {}

House::~House() {}

bool House::isHitting() const {
    return getTotal() <= 16;
}

void House::flipFirstCard() {
    if (!cardVector.empty()) {
        cardVector[0]->flip();
    } else {
        std::cout << "No card to flip!" << std::endl;
    }
}
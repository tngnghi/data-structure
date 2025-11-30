#include "GenericPlayer.h"
#include <iostream>

GenericPlayer::GenericPlayer(const std::string& n) : name(n) {}

GenericPlayer::~GenericPlayer() {}

bool GenericPlayer::isBusted() const {
    return getTotal() > 21;
}

void GenericPlayer::bust() const {
    std::cout << name << " busts!" << std::endl;
}

std::string GenericPlayer::getName() const {
    return name;
}

void GenericPlayer::setName(const std::string& n) {
    name = n;
}

std::ostream& operator<<(std::ostream& os, const GenericPlayer& genericPlayer) {
    os << genericPlayer.name << ":\t";
    
    if (!genericPlayer.cardVector.empty()) {
        for (std::vector<Card*>::const_iterator iter = genericPlayer.cardVector.begin(); 
             iter != genericPlayer.cardVector.end(); ++iter) {
            os << *(*iter) << "\t";
        }
        
        if (genericPlayer.getTotal() != 0) {
            os << "(" << genericPlayer.getTotal() << ")";
        }
    } else {
        os << "<empty>";
    }
    
    return os;
}
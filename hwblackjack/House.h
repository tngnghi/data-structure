#ifndef HOUSE_H
#define HOUSE_H

#include "GenericPlayer.h"

class House : public GenericPlayer {
public:
    House(const std::string& name = "Dealer");
    virtual ~House();
    virtual bool isHitting() const;
    void flipFirstCard();
};

#endif
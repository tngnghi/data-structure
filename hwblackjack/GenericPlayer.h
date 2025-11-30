#ifndef GENERICPLAYER_H
#define GENERICPLAYER_H

#include "Hand.h"
#include <string>

class GenericPlayer : public Hand {
private:
    std::string name;

public:
    GenericPlayer(const std::string& name = "");
    virtual ~GenericPlayer();
    virtual bool isHitting() const = 0; // Pure virtual function
    bool isBusted() const;
    void bust() const;
    std::string getName() const;
    void setName(const std::string& name);
    
    // Friend function for overloaded << operator
    friend std::ostream& operator<<(std::ostream& os, const GenericPlayer& genericPlayer);
};

#endif
#ifndef BELISKNER_PLAYER_HPP
#define BELISKNER_PLAYER_HPP

#include "OGRE/Ogre.h"

namespace Beliskner
{

class Player
{
public:
    Player();
    ~Player();

    std::string name;
    int         playerLife;
    int         playerMana;
    int         playerSpeed;
    int         playerStrength;

private:
};

}

#endif

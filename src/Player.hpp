#ifndef BELISKNER_PLAYER_HPP
#define BELISKNER_PLAYER_HPP

#include "OGRE/Ogre.h"

#include "BaseRoot.hpp"

namespace Beliskner
{

class Player
{
public:
    Player();
    ~Player();

    BaseRoot *base;

    Ogre::Entity            *playerEnt;
    Ogre::SceneNode         *playerNode;
    Ogre::AnimationState    *aniState;
    Ogre::AnimationState    *aniStateTop;
    Ogre::AnimationState    *hitAni;

    bool attackPlayer;
    bool hitMonster;
    bool invertPlayerDir;
    bool magicPlayer;
    int  playerTurns;
    bool playerActionInProgress;

    std::string name;
    int         playerLife;
    int         playerMana;
    int         playerSpeed;
    int         playerStrength;

    void setUpScene();
    void leaveScene();
    void makeAnimations();

private:
};

}

#endif

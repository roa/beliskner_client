#ifndef BELISKNER_MONSTER_HPP
#define BELISKNER_MONSTER_HPP

#include "OGRE/Ogre.h"
#include <lua.hpp>

#include "BaseScene.hpp"
#include "BaseRoot.hpp"

namespace Beliskner
{

class Monster
{
public:
    Monster( std::string _name, BaseScene *_currentScene );
    ~Monster();

    BaseRoot* base;

    std::string name;
    int         monsterLife;
    int         monsterMana;
    int         monsterSpeed;
    int         monsterStrength;

    bool attackMonster;
    bool hitPlayer;
    bool invertMonsterDir;
    bool magicMonster;
    int  monsterTurns;

    bool playerAction;
    bool playerActionInProgress;
    bool monsterActionInProgress;

    Ogre::Entity            *monsterEnt;
    Ogre::SceneNode         *monsterNode;
    Ogre::AnimationState    *monsterState;
    Ogre::AnimationState    *monsterAttack;

    BaseScene *currentScene;

    bool initFailure;
    std::vector<std::string> monsterAttacks;

    void setUpScene();
    void makeAnimations();

private:
    lua_State *L;

    void load( lua_State *L, const char* fname );

};

}

#endif

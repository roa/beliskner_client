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
    Monster( std::string _name, BaseScene *_currentScene, int _xCoord );
    ~Monster();

    BaseRoot* base;

    std::string name;
    std::string sname;
    std::string aname;
    int monsterLife;
    int currentMonsterLife;
    int monsterMana;
    int currentMonsterMana;
    int monsterSpeed;
    int monsterStrength;

    bool attackMonster;
    bool hitPlayer;
    bool invertMonsterDir;
    bool magicMonster;
    int  monsterTurns;

    bool playerAction;
    bool playerActionInProgress;
    bool monsterActionInProgress;

    int xCoord;
    int damage;

    Ogre::Entity            *monsterEnt;
    Ogre::SceneNode         *monsterNode;
    Ogre::AnimationState    *monsterState;
    std::vector<Ogre::AnimationState*> monsterAttackAnis;
    int aniNum;
    BaseScene *currentScene;

    bool initFailure;
    std::vector<std::string> monsterAttacks;
    int monsterAttackCount;

    void setUpScene();
    void makeAnimations();

    void calcAttack();
private:
    lua_State *L;

    void load( lua_State *L, const char* fname );
    void initAnimations();


};

}

#endif

#ifndef BELISKNER_MONSTER_HPP
#define BELISKNER_MONSTER_HPP

#include "OGRE/Ogre.h"
#include <lua.hpp>

namespace Beliskner
{

class Monster
{
public:
    Monster( std::string _name );
    ~Monster();

    std::string name;
    int         monsterLife;
    int         monsterMana;
    int         monsterSpeed;
    int         monsterStrength;

    bool initFailure;

private:
    lua_State *L;

    void init( lua_State *L, const char* fname );

};

}

#endif

#include "Monster.hpp"

namespace Beliskner
{

Monster::Monster( std::string _name )
{
    name = _name;
    L = luaL_newstate();
    std::stringstream scriptCaller;
    scriptCaller << "scripts/" << name.c_str() << ".lua";
    init( L, scriptCaller.str().c_str() );
}

Monster::~Monster()
{

}

void Monster::init( lua_State *L, const char* fname )
{
    if( luaL_loadfile( L, fname ) || lua_pcall( L, 0, 0, 0 ) )
    {
        std::cout << "cannot run config file: " << lua_tostring( L, -1 ) << std::endl;
    }

    lua_getglobal( L, "monsterLife" );
    lua_getglobal( L, "monsterMana" );
    lua_getglobal( L, "monsterSpeed");
    lua_getglobal( L, "monsterStrength");

    if( !lua_isnumber( L, 1 ) )
    {
        std::cerr << "monsterLife is not a number" << std::endl;
        initFailure = true;
    }
    if( !lua_isnumber( L, 2 ) )
    {
        std::cerr << "monsterMana is not a number" << std::endl;
        initFailure = true;
    }
    if( !lua_isnumber( L, 2 ) )
    {
        std::cerr << "monsterSpeed is not a number" << std::endl;
        initFailure = true;
    }
    if( !lua_isnumber( L, 3 ) )
    {
        std::cerr << "monsterStrength is not a number" << std::endl;
        initFailure = true;
    }

    monsterLife     = lua_tointeger( L, 1 );
    monsterMana     = lua_tointeger( L, 2 );
    monsterSpeed    = lua_tointeger( L, 3 );
    monsterStrength = lua_tointeger( L, 4 );
}

}

#include "Monster.hpp"

namespace Beliskner
{

Monster::Monster( std::string _name, BaseScene *_currentScene, int _xCoord )
{
    base = BaseRoot::getSingletonPtr();
    attackMonster      = false;
    hitPlayer          = false;
    invertMonsterDir   = false;
    magicMonster       = false;
    monsterTurns       = 0;
    monsterAttackCount = 0;
    aniNum             = 0;
    currentMonsterLife = 0;
    currentMonsterMana = 0;
    monsterActionInProgress = false;
    currentScene = _currentScene;
    xCoord       = _xCoord;

    name         = _name;
    L            = luaL_newstate();

    std::stringstream scriptCaller;
    scriptCaller << "scripts/" << name.c_str() << ".lua";
    sname = scriptCaller.str();
    std::stringstream scriptCaller2;
    scriptCaller2 << "scripts/" << name.c_str() << "Attack.lua";
    aname = scriptCaller2.str();
    load( L, sname.c_str() );
}

Monster::~Monster()
{

}

void Monster::setUpScene()
{
    monsterEnt  = currentScene->sceneManager->createEntity( "ninja.mesh" );
    monsterNode = currentScene->sceneManager->getRootSceneNode()->createChildSceneNode();
    monsterNode->setPosition( 5 * xCoord, -5, 25 );
    monsterNode->attachObject( monsterEnt );
    monsterNode->scale( 0.04f, 0.04f, 0.04f );

    monsterState = monsterEnt->getAnimationState( "Walk" );
    monsterState->setLoop( false );

    initAnimations();
}

void Monster::makeAnimations()
{
    if( monsterNode->getPosition().z == -23 )
    {
        if( hitPlayer )
        {
            monsterAttackAnis.at( aniNum )->setEnabled( true );
            monsterAttackAnis.at( aniNum )->addTime( base->timer->getMilliseconds() * 0.001f );
            if( monsterAttackAnis.at( aniNum )->hasEnded() )
            {
                monsterAttackAnis.at( aniNum )->setEnabled( false );
                monsterAttackAnis.at( aniNum )->setTimePosition( 0.0f );
                hitPlayer = false;
                base->player->playerLife -= damage;
            }
            return;
        }
        else
        {
            invertMonsterDir = true;
            monsterNode->yaw( Ogre::Degree( 180 ) );
        }
    }

    Ogre::Vector3 transDir( 0, 0, 0 );
    if( invertMonsterDir )
    {
        transDir.z = 1;
    }
    else
    {
        transDir.z = -1;
    }
    if( attackMonster )
    {
        monsterNode->translate( transDir * 0.5f );
        monsterState->setEnabled( true );

        if( monsterState->hasEnded() )
        {
            monsterState->setTimePosition( 0.0f );
        }
    }
    else
    {
        monsterState->setTimePosition( 0.0f );
        monsterState->setEnabled( false );
    }
    monsterState->addTime( base->timer->getMilliseconds() * 0.001f );

    if( attackMonster && monsterNode->getPosition().z == 25 )
    {
        attackMonster = false;
        monsterActionInProgress = false;
        invertMonsterDir = false;
        monsterNode->yaw( Ogre::Degree( 180 ) );
        monsterState->setTimePosition( 0.0f );
        monsterState->setEnabled( false );
        return;
    }
}

void Monster::load( lua_State *L, const char* fname )
{
    if( luaL_loadfile( L, fname ) || lua_pcall( L, 0, 0, 0 ) )
    {
        std::cout << "cannot run config file: " << lua_tostring( L, -1 ) << std::endl;
    }

    lua_getglobal( L, "monsterLife" );
    if( !lua_isnumber( L, 1 ) )
    {
        std::cerr << "monsterLife is not a number" << std::endl;
        initFailure = true;
    }
    monsterLife     = lua_tointeger( L, 1 );
    currentMonsterLife = monsterLife;
    lua_pop( L, 1 );

    lua_getglobal( L, "monsterMana" );
    if( !lua_isnumber( L, 1 ) )
    {
        std::cerr << "monsterMana is not a number" << std::endl;
        initFailure = true;
    }
    monsterMana     = lua_tointeger( L, 1 );
    currentMonsterMana = monsterMana;
    lua_pop( L, 1 );

    lua_getglobal( L, "monsterSpeed");
    if( !lua_isnumber( L, 1 ) )
    {
        std::cerr << "monsterSpeed is not a number" << std::endl;
        initFailure = true;
    }
    monsterSpeed    = lua_tointeger( L, 1 );
    lua_pop( L, 1 );

    lua_getglobal( L, "monsterStrength");
    if( !lua_isnumber( L, 1 ) )
    {
        std::cerr << "monsterStrength is not a number" << std::endl;
        initFailure = true;
    }
    monsterStrength = lua_tointeger( L, 1 );
    lua_pop( L, 1 );

    lua_getglobal( L, "monsterAttacks" );
    if ( !lua_istable( L, 1 ) )
    {
        std::cerr << "monsterAttacks is not a table" << std::endl;
        initFailure = true;
    }

    lua_pushnil( L );

    while( lua_next( L, 1 ) != 0 )
    {
        monsterAttacks.push_back( lua_tostring( L, -1 ));
        lua_pop( L, 1 );
        ++monsterAttackCount;
    }
    lua_close( L );
}

void Monster::initAnimations()
{
    int i = 0;
    for( std::vector<std::string>::iterator it = monsterAttacks.begin(); it != monsterAttacks.end(); ++it)
    {
        std::string aniName = *it;
        monsterAttackAnis.push_back( monsterEnt->getAnimationState( aniName ) );
        monsterAttackAnis.at( i++ )->setLoop( false );
    }
}

void Monster::calcAttack()
{
    L = luaL_newstate();
    luaopen_math(L);
    luaopen_os(L);
    if( luaL_loadfile( L, aname.c_str() ) )
    {
        std::cerr << "Could not load " << aname << " : " << lua_tostring( L, -1 ) << std::endl;
    }
    luaL_openlibs( L );

    lua_pushnumber( L, monsterLife );
    lua_setglobal( L, "monsterLife" );
    lua_pushnumber( L, currentMonsterLife );
    lua_setglobal( L, "currentMonsterLife" );
    lua_pushnumber( L, monsterStrength );
    lua_setglobal( L, "monsterStrength" );
    lua_pushnumber( L, currentMonsterMana );
    lua_setglobal( L, "currentMonsterMana" );


   /***************************************************
    *   pcall: luaState, parameters, results, errfunc *
    ***************************************************/
    lua_pcall(L, 0, 3, 0);

    aniNum = lua_tonumber( L, -3 );
    damage = lua_tonumber( L, -2 );
    currentMonsterMana = lua_tonumber( L, -1 );
    std::cout << " ani: " << aniNum << " dam: " << lua_tonumber( L, -2) << " mana: " << currentMonsterMana << " monsternum: "<< xCoord <<std::endl;
    lua_close( L );
}

}

#include "Monster.hpp"

namespace Beliskner
{

Monster::Monster( std::string _name, BaseScene *_currentScene )
{
    base = BaseRoot::getSingletonPtr();
    attackMonster    = false;
    hitPlayer        = false;
    invertMonsterDir = false;
    magicMonster     = false;
    monsterTurns     = 0;

    monsterActionInProgress = false;
    currentScene = _currentScene;

    name         = _name;
    L            = luaL_newstate();

    std::stringstream scriptCaller;
    scriptCaller << "scripts/" << name.c_str() << ".lua";
    load( L, scriptCaller.str().c_str() );
}

Monster::~Monster()
{

}

void Monster::setUpScene()
{
    monsterEnt = currentScene->sceneManager->createEntity( "ninja.mesh" );
    monsterNode = currentScene->sceneManager->getRootSceneNode()->createChildSceneNode();
    monsterNode->setPosition( 0, -5, 25 );
    monsterNode->attachObject( monsterEnt );
    monsterNode->scale( 0.04f, 0.04f, 0.04f );

    monsterState = monsterEnt->getAnimationState( "Walk" );
    monsterState->setLoop( false );

    monsterAttack = monsterEnt->getAnimationState( "Attack1" );
    monsterAttack->setLoop( false );
}

void Monster::makeAnimations()
{
    if( monsterNode->getPosition().z == -23 )
    {
        if( hitPlayer )
        {
            monsterAttack->setEnabled( true );
            monsterAttack->addTime( base->timer->getMilliseconds() * 0.001f );
            if( monsterAttack->hasEnded() )
            {
                monsterAttack->setEnabled( false );
                monsterAttack->setTimePosition( 0.0f );
                hitPlayer = false;
                base->player->playerLife -= monsterStrength;
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
    lua_pop( L, 1 );

    lua_getglobal( L, "monsterMana" );
    if( !lua_isnumber( L, 1 ) )
    {
        std::cerr << "monsterMana is not a number" << std::endl;
        initFailure = true;
    }
    monsterMana     = lua_tointeger( L, 1 );
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
    }
}

}

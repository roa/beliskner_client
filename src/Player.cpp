#include "Player.hpp"

namespace Beliskner
{

Player::Player()
{
    name            = "Roa";
    playerLife      = 500;
    playerMana      = 500;
    playerSpeed     = 10;
    playerStrength  = 10;

    playerEnt   = NULL;
    playerNode  = NULL;
    aniState    = NULL;
    aniStateTop = NULL;
    hitAni      = NULL;

    attackPlayer = false;
    hitMonster = false;
    invertPlayerDir = false;
    magicPlayer = false;
    playerTurns = 0;
    playerActionInProgress = false;

    base = BaseRoot::getSingletonPtr();
}

Player::~Player()
{

}

void Player::setUpScene()
{
    playerEnt = base->sceneManager->currentScene->sceneManager->createEntity( "Sinbad.mesh" );
    playerNode = base->sceneManager->currentScene->sceneManager->getRootSceneNode()->createChildSceneNode();
    playerNode->setPosition( 0, 0, -25 );
    playerNode->attachObject( playerEnt );

    aniState    = playerEnt->getAnimationState( "RunBase" );
    aniState->setLoop( false );

    aniStateTop = playerEnt->getAnimationState( "RunTop" );
    aniStateTop->setLoop( false );

    hitAni = playerEnt->getAnimationState( "DrawSwords" );
    hitAni->setLoop( false );
}

void Player::leaveScene()
{
    playerEnt   = NULL;
    playerNode  = NULL;
    aniState    = NULL;
    aniStateTop = NULL;
    hitAni      = NULL;

    attackPlayer = false;
    hitMonster = false;
    invertPlayerDir = false;
    magicPlayer = false;
    playerTurns = 0;
}

void Player::makeAnimations()
{
    if( playerNode->getPosition().z == 23 )
    {
        if( hitMonster )
        {
            hitAni->setEnabled(true);
            hitAni->addTime( base->timer->getMilliseconds() * 0.001f );
            if( hitAni->hasEnded() )
            {
                hitAni->setEnabled(false);
                hitAni->setTimePosition( 0.0f );
                hitMonster = false;
            }
            return;
        }
        else
        {
            invertPlayerDir = true;
            playerNode->yaw( Ogre::Degree( 180 ) );
        }
    }

    Ogre::Vector3 transDir(0, 0, 0);
    if( invertPlayerDir )
    {
        transDir.z = -1;
    }
    else
    {
        transDir.z = 1;
    }
    if( attackPlayer )
    {
        playerNode->translate( transDir * 0.5f );
        aniState->setEnabled( true );
        aniStateTop->setEnabled( true );

        if( aniState->hasEnded() )
        {
            aniState->setTimePosition( 0.0f );
        }
        if( aniStateTop->hasEnded() )
        {
            aniStateTop->setTimePosition( 0.0f );
        }
    }
    else
    {
        aniState->setTimePosition( 0.0f );
        aniState->setEnabled( false );
        aniStateTop->setTimePosition( 0.0f );
        aniStateTop->setEnabled( false );
    }
    aniState->addTime( base->timer->getMilliseconds() * 0.001f );
    aniStateTop->addTime( base->timer->getMilliseconds() * 0.001f );
    if( attackPlayer && playerNode->getPosition().z == -25 )
    {
        attackPlayer = false;
        playerActionInProgress = false;
        invertPlayerDir = false;
        playerNode->yaw( Ogre::Degree( 180 ) );
        aniState->setTimePosition( 0.0f );
        aniStateTop->setTimePosition( 0.0f );
    }
}

}

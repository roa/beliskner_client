#include "BaseScene.hpp"

namespace Beliskner
{

BaseScene::BaseScene()
{
    base         = NULL;
    sceneManager = NULL;
    camera       = NULL;
    initBaseRoot();
}

BaseScene::~BaseScene()
{

}

void BaseScene::enterScene()
{
    initSceneManager();
    initCamera();
    initViewport();
}

void BaseScene::createScene()
{
    Ogre::Entity *ent = sceneManager->createEntity( "Sinbad.mesh" );
    sceneManager->getRootSceneNode()->attachObject( ent );
}

void BaseScene::initBaseRoot()
{
    base = BaseRoot::getSingletonPtr();
}

void BaseScene::initSceneManager()
{
    base->logger->logMessage( "initiating scenemanager in BaseScene..." );
    sceneManager = base->root->createSceneManager( Ogre::ST_GENERIC );
}

void BaseScene::initCamera()
{
    base->logger->logMessage( "initiating camera..." );
    camera = sceneManager->createCamera( "Camera" );
    camera->setPosition( Ogre::Vector3( 0, 0, 50 ) );
    camera->lookAt( Ogre::Vector3( 0, 0, 0 ) );
    camera->setNearClipDistance( 5 );
}

void BaseScene::initViewport()
{
    base->logger->logMessage( "initiating viewport" );
    viewport = base->window->addViewport( camera );
    viewport->setBackgroundColour( Ogre::ColourValue( 0.5, 0.5, 0.5 ) );
    camera->setAspectRatio( Ogre::Real( viewport->getActualWidth() ) / Ogre::Real( viewport->getActualHeight() ) );
}
}

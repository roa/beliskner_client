#include "DemoScene.hpp"

namespace Beliskner
{

DemoScene::DemoScene()
{
    base         = NULL;
    sceneManager = NULL;
    camera       = NULL;
    initScene();
}

DemoScene::~DemoScene()
{

}

void DemoScene::initScene()
{
    initBaseRoot();
    initSceneManager();
    initCamera();
    initViewport();
}

void DemoScene::createScene()
{
    Ogre::Entity *ent = sceneManager->createEntity( "Sinbad.mesh" );
    sceneManager->getRootSceneNode()->attachObject( ent );
}

void DemoScene::initBaseRoot()
{
    base = BaseRoot::getSingletonPtr();
}

void DemoScene::initSceneManager()
{
    base->logger->logMessage( "initiating scenemanager in demoscene..." );
    sceneManager = base->root->createSceneManager( Ogre::ST_GENERIC );
}

void DemoScene::initCamera()
{
    base->logger->logMessage( "initiating camera..." );
    camera = sceneManager->createCamera( "Camera" );
    camera->setPosition( Ogre::Vector3( 0, 0, 50 ) );
    camera->lookAt( Ogre::Vector3( 0, 0, 0 ) );
    camera->setNearClipDistance( 5 );
}

void DemoScene::initViewport()
{
    base->logger->logMessage( "initiating viewport" );
    viewport = base->window->addViewport( camera );
    viewport->setBackgroundColour( Ogre::ColourValue( 0.5, 0.5, 0.5 ) );
    camera->setAspectRatio( Ogre::Real( viewport->getActualWidth() ) / Ogre::Real( viewport->getActualHeight() ) );
}
}

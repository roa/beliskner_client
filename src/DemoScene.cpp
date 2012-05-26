#include "DemoScene.hpp"

namespace Beliskner
{

DemoScene::DemoScene()
{
    base         = NULL;
    sceneManager = NULL;
    camera       = NULL;
    initBaseRoot();
    initSceneManager();
    initCamera();
    initViewport();

}

DemoScene::~DemoScene()
{

}

void DemoScene::run()
{
    Ogre::Entity *ent = sceneManager->createEntity( "Sinbad.mesh" );
    sceneManager->getRootSceneNode()->attachObject( ent );
    while( base->running() )
    {
        base->renderOneFrame();
    }
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

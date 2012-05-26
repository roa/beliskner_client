#include "DemoScene2.hpp"

namespace Beliskner
{

DemoScene2::DemoScene2( std::string _sceneName )
{
    sceneName = _sceneName;
    sceneManager = NULL;
    camera       = NULL;
    initBaseRoot();
}

DemoScene2::~DemoScene2()
{

}

void DemoScene2::createScene()
{
    Ogre::Entity *ent = sceneManager->createEntity( "ninja.mesh" );
    sceneManager->getRootSceneNode()->attachObject( ent );
}

void DemoScene2::enterScene()
{
    initSceneManager();
    initCamera();
}

void DemoScene2::exitScene()
{
    destroyCamera();
    destroySceneManager();
}

void DemoScene2::initBaseRoot()
{
    base = BaseRoot::getSingletonPtr();
}

void DemoScene2::initSceneManager()
{
    base->logger->logMessage( "initiating scenemanager in DemoScene2..." );
    sceneManager = base->root->createSceneManager( Ogre::ST_GENERIC );
}

void DemoScene2::initCamera()
{
    base->logger->logMessage( "initiating camera..." );
    camera = sceneManager->createCamera( "Camera" );
    camera->setPosition( Ogre::Vector3( 0, 0, 50 ) );
    camera->lookAt( Ogre::Vector3( 0, 0, 0 ) );
    camera->setNearClipDistance( 5 );
    camera->setAspectRatio( Ogre::Real( base->viewport->getActualWidth() ) / Ogre::Real( base->viewport->getActualHeight() ) );
    base->viewport->setCamera( camera );
}

void DemoScene2::destroySceneManager()
{
    base->root->destroySceneManager( sceneManager );
}

void DemoScene2::destroyCamera()
{
    sceneManager->destroyCamera( camera );
}


}

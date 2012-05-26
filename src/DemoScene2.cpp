#include "DemoScene2.hpp"

namespace Beliskner
{

DemoScene2::DemoScene2( std::string _sceneName )
{
    base = BaseRoot::getSingletonPtr();
    sceneName = _sceneName;
    sceneManager = NULL;
    camera       = NULL;
    sceneSwitch  = false;
}

DemoScene2::~DemoScene2()
{

}

void DemoScene2::createScene()
{
    sceneSwitch = false;
    Ogre::Entity *ent = sceneManager->createEntity( "ninja.mesh" );
    sceneManager->getRootSceneNode()->attachObject( ent );
}

void DemoScene2::prepareScene()
{
    initSceneManager();
    initCamera();
}

void DemoScene2::exitScene()
{
    destroyCamera();
    destroySceneManager();
}

void DemoScene2::switchScene()
{
    if( sceneSwitch )
        base->sceneManager->switchToScene( "mainScene" );
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

void DemoScene2::updateScene()
{
    updateKeyboard();
    updateMouse();
    switchScene();
}

void DemoScene2::updateKeyboard()
{
    base->frameListener->keyboard->capture();
    if( base->frameListener->keyboard->isKeyDown( OIS::KC_ESCAPE ) )
    {
        base->frameListener->leaveApp = true;
    }
    if( base->frameListener->keyboard->isKeyDown( OIS::KC_S) )
    {
        sceneSwitch = true;
    }
}

void DemoScene2::updateMouse()
{

}

}

#include "NextScene.hpp"

namespace Beliskner
{

NextScene::NextScene( std::string _sceneName )
{
    base = BaseRoot::getSingletonPtr();
    sceneName = _sceneName;
    sceneManager = NULL;
    camera       = NULL;
    sceneSwitch  = false;
}

NextScene::~NextScene()
{

}

void NextScene::createScene()
{
    sceneSwitch = false;
    Ogre::Entity *ent = sceneManager->createEntity( "ninja.mesh" );
    sceneManager->getRootSceneNode()->attachObject( ent );
}

void NextScene::prepareScene()
{
    initSceneManager();
    initCamera();
}

void NextScene::exitScene()
{
    destroyCamera();
    destroySceneManager();
}

void NextScene::switchScene()
{
    if( sceneSwitch )
        base->sceneManager->switchToScene( "mainScene" );
}

void NextScene::initSceneManager()
{
    base->logger->logMessage( "initiating scenemanager in NextScene..." );
    sceneManager = base->root->createSceneManager( Ogre::ST_GENERIC );
}

void NextScene::initCamera()
{
    base->logger->logMessage( "initiating camera..." );
    camera = sceneManager->createCamera( "Camera" );
    camera->setPosition( Ogre::Vector3( 0, 0, 50 ) );
    camera->lookAt( Ogre::Vector3( 0, 0, 0 ) );
    camera->setNearClipDistance( 5 );
    camera->setAspectRatio( Ogre::Real( base->viewport->getActualWidth() ) / Ogre::Real( base->viewport->getActualHeight() ) );
    base->viewport->setCamera( camera );
}

void NextScene::destroySceneManager()
{
    base->root->destroySceneManager( sceneManager );
}

void NextScene::destroyCamera()
{
    sceneManager->destroyCamera( camera );
}

void NextScene::updateScene()
{
    updateKeyboard();
    updateMouse();
    switchScene();
}

void NextScene::updateKeyboard()
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

void NextScene::updateMouse()
{

}

}

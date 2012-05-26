#include "DemoScene.hpp"

namespace Beliskner
{

DemoScene::DemoScene( std::string _sceneName )
{
    sceneName = _sceneName;
    sceneManager = NULL;
    camera       = NULL;
    initBaseRoot();

}

DemoScene::~DemoScene()
{

}

void DemoScene::createScene()
{
    Ogre::Entity *ent = sceneManager->createEntity( "Sinbad.mesh" );
    sceneManager->getRootSceneNode()->attachObject( ent );
}

void DemoScene::enterScene()
{
    initSceneManager();
    initCamera();
}

void DemoScene::exitScene()
{
    destroyCamera();
    destroySceneManager();
}

void DemoScene::initBaseRoot()
{
    base = BaseRoot::getSingletonPtr();
}

void DemoScene::initSceneManager()
{
    base->logger->logMessage( "initiating scenemanager in DemoScene..." );
    sceneManager = base->root->createSceneManager( Ogre::ST_GENERIC );
}

void DemoScene::initCamera()
{
    base->logger->logMessage( "initiating camera..." );
    camera = sceneManager->createCamera( "Camera" );
    camera->setPosition( Ogre::Vector3( 0, 0, 50 ) );
    camera->lookAt( Ogre::Vector3( 0, 0, 0 ) );
    camera->setNearClipDistance( 5 );
    camera->setAspectRatio( Ogre::Real( base->viewport->getActualWidth() ) / Ogre::Real( base->viewport->getActualHeight() ) );
    base->viewport->setCamera( camera );
}

void DemoScene::destroySceneManager()
{
    base->root->destroySceneManager( sceneManager );
}

void DemoScene::destroyCamera()
{
    sceneManager->destroyCamera( camera );
}

void DemoScene::handleInput()
{
    base->frameListener->keyboard->capture();
    if( base->frameListener->keyboard->isKeyDown( OIS::KC_ESCAPE ) )
    {
        base->frameListener->leaveApp = true;
    }
    if( base->frameListener->keyboard->isKeyDown( OIS::KC_S) )
    {
        base->sceneManager->switchToScene( "nextScene" );
    }
}

}

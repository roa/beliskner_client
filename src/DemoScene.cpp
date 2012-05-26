#include "DemoScene.hpp"

namespace Beliskner
{

DemoScene::DemoScene( std::string _sceneName )
{
    sceneName = _sceneName;
}

DemoScene::~DemoScene()
{

}

void DemoScene::createScene()
{
    Ogre::Entity *ent = sceneManager->createEntity( "Sinbad.mesh" );
    sceneManager->getRootSceneNode()->attachObject( ent );
}

void DemoScene::createScene2()
{
    Ogre::Entity *ent = sceneManager->createEntity( "ninja.mesh" );
    sceneManager->getRootSceneNode()->attachObject( ent );
}

}

#include "SceneManager.hpp"
#include "DemoScene.hpp"

namespace Beliskner
{

SceneManager::SceneManager()
{
    sceneManagerState = NULL;
    base              = NULL;
    initSceneManager();
}

SceneManager::~SceneManager()
{

}

void SceneManager::initSceneManager()
{
    base = BaseRoot::getSingletonPtr();
    sceneManagerState = new std::vector<BaseScene*>;
    createMainScene();
    createNextScene();
}

void SceneManager::createMainScene()
{
    DemoScene *mainScene = new DemoScene( "mainScene" );
    sceneManagerState->push_back( mainScene );
}

void SceneManager::createNextScene()
{
    DemoScene *nextScene = new DemoScene( "nextScene" );
    sceneManagerState->push_back( nextScene );
}

void SceneManager::startMainScene()
{
    sceneManagerState->front()->enterScene();
    sceneManagerState->front()->createScene2();
}

void SceneManager::switchToScene( std::string _sceneName )
{
    for(std::vector<BaseScene*>::iterator it = sceneManagerState->begin(); it != sceneManagerState->end(); ++it)
    {
        BaseScene* baseScene = *it;
        std::cout << baseScene->sceneName << std::endl;
    }
}

}

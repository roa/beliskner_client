#include "SceneManager.hpp"

namespace Beliskner
{

SceneManager::SceneManager()
{
    sceneManagerState = NULL;
    base              = NULL;
    initSceneManager();
    switchScene = false;
}

SceneManager::~SceneManager()
{

}

void SceneManager::initSceneManager()
{
    base = BaseRoot::getSingletonPtr();
    sceneManagerState = new std::vector<BaseScene*>;
}

void SceneManager::createNewScene( BaseScene* _newScene )
{
    sceneManagerState->push_back( _newScene );
}

void SceneManager::startMainScene()
{
    sceneManagerState->front()->enterScene();
    sceneManagerState->front()->createScene();
    currentScene = sceneManagerState->front();
}

void SceneManager::switchToScene( std::string _sceneName )
{
    if( switchScene )
    {
        for(std::vector<BaseScene*>::iterator it = sceneManagerState->begin(); it != sceneManagerState->end(); ++it)
        {
            BaseScene* baseScene = *it;
            if( baseScene->sceneName.compare( _sceneName ) == 0 )
            {
                currentScene->exitScene();
                currentScene = baseScene;
                currentScene->enterScene();
                currentScene->createScene();
            }
            else
            {
                std::cout << "no" << std::endl;
            }
        }
        switchScene = false;
    }
}

}

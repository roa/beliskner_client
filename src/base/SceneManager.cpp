#include "SceneManager.hpp"

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
    delete sceneManagerState;
}

void SceneManager::initSceneManager()
{
    base = BaseRoot::getSingletonPtr();
    sceneManagerState = new std::vector<BaseScene*>;
    WorldScene *worldScene = new WorldScene( "WorldScene" );
    addNewScene( worldScene );
    FightScene *fightScene = new FightScene( "FightScene" );
    addNewScene( fightScene );
}

void SceneManager::addNewScene( BaseScene* _newScene )
{
    sceneManagerState->push_back( _newScene );
}

void SceneManager::startWorldScene()
{
    currentScene = sceneManagerState->front();
    sceneManagerState->front()->prepareScene();
    sceneManagerState->front()->createScene();
}

void SceneManager::switchToScene( std::string _sceneName )
{
    if( currentScene->sceneName.compare( _sceneName ) != 0 )
    {
        for(std::vector<BaseScene*>::iterator it = sceneManagerState->begin(); it != sceneManagerState->end(); ++it)
        {
            BaseScene* baseScene = *it;
            if( baseScene->sceneName.compare( _sceneName ) == 0 )
            {
                currentScene->exitScene();
                currentScene = baseScene;
                currentScene->prepareScene();
                currentScene->createScene();
                break;
            }
        }
    }
}

}

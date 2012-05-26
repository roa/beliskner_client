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

}

void SceneManager::initSceneManager()
{
    new BaseRoot();
    base = BaseRoot::getSingletonPtr();
    sceneManagerState = new std::vector<BaseScene*>;
    createMainScene();
    createNextScene();
}

void SceneManager::createMainScene()
{
    BaseScene *mainScene = new BaseScene();
    sceneManagerState->push_back( mainScene );
}

void SceneManager::createNextScene()
{
    BaseScene *nextScene = new BaseScene();
    sceneManagerState->push_back( nextScene );
}

void SceneManager::startMainScene()
{
    sceneManagerState->front()->enterScene();
    sceneManagerState->front()->createScene();
}

}

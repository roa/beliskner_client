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
    sceneManagerState = new std::vector<DemoScene*>;
    createMainScene();
}

void SceneManager::createMainScene()
{
    new BaseRoot();
    base = BaseRoot::getSingletonPtr();
    DemoScene *mainScene = new DemoScene();
    sceneManagerState->push_back( mainScene );
}

void SceneManager::startMainScene()
{
    sceneManagerState->front()->createScene();
}

}

#ifndef BELISKNER_SCENEMANAGER_HPP
#define BELISKNER_SCENEMANAGER_HPP

#include "OGRE/Ogre.h"
#include "OIS/OIS.h"
#include <vector>

#include "BaseScene.hpp"
#include "BaseRoot.hpp"

namespace Beliskner
{

class BaseRoot;

class SceneManager
{
public:
    std::vector<BaseScene*>* sceneManagerState;
    BaseRoot *base;
    BaseScene* currentScene;

    void initSceneManager();
    void createNewScene( BaseScene* _newScene );

public:
    SceneManager();
    ~SceneManager();

    bool switchScene;

    void startMainScene();
    void switchToScene( std::string _sceneName );
};

}

#endif

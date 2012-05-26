#ifndef BELISKNER_SCENEMANAGER_HPP
#define BELISKNER_SCENEMANAGER_HPP

#include "OGRE/Ogre.h"
#include "OIS/OIS.h"
#include <vector>

#include "BaseRoot.hpp"
#include "BaseScene.hpp"

namespace Beliskner
{

class SceneManager
{
private:
    std::vector<BaseScene*>* sceneManagerState;
    BaseRoot *base;

    void initSceneManager();
    void createMainScene();
    void createNextScene();

public:
    SceneManager();
    ~SceneManager();

    void startMainScene();
};

}

#endif

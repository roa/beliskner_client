#ifndef BELISKNER_SCENEMANAGER_HPP
#define BELISKNER_SCENEMANAGER_HPP

#include "OGRE/Ogre.h"
#include "OIS/OIS.h"
#include <vector>

#include "BaseRoot.hpp"
#include "DemoScene.hpp"

namespace Beliskner
{

class SceneManager
{
private:
    std::vector<DemoScene*>* sceneManagerState;
    BaseRoot *base;

    void initSceneManager();
    void createMainScene();

public:
    SceneManager();
    ~SceneManager();

    void startMainScene();
};

}

#endif

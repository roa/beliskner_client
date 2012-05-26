#ifndef BELISKNER_SCENEMANAGER_HPP
#define BELISKNER_SCENEMANAGER_HPP

#include "OGRE/Ogre.h"
#include "OIS/OIS.h"
#include <vector>

namespace Beliskner
{

class BaseRoot;
class BaseScene;

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
    void switchToScene( std::string _sceneName );
};

}

#endif

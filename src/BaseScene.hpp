#ifndef BELISKNER_BASESCENE_HPP
#define BELISKNER_BASESCENE_HPP

#include "OGRE/Ogre.h"
#include "OIS/OIS.h"

#include "BaseRoot.hpp"

namespace Beliskner
{

class BaseRoot;
class SceneManager;

class BaseScene
{
public:
    BaseRoot* base;
    Ogre::SceneManager  *sceneManager;
    Ogre::Camera        *camera;
    Ogre::Viewport      *viewport;

    std::string sceneName;

    void initBaseRoot();

    void initSceneManager();
    void initCamera();
    void initViewport();

    void destroySceneManager();
    void destroyCamera();

    BaseScene();
    ~BaseScene();

    void enterScene();
    void exitScene();

    virtual void createScene() = 0;
    virtual void createScene2() = 0;
};

}

#endif

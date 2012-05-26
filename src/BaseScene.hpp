#ifndef BELISKNER_BaseScene_HPP
#define BELISKNER_BaseScene_HPP

#include "OGRE/Ogre.h"
#include "OIS/OIS.h"

#include "BaseRoot.hpp"

namespace Beliskner
{

class BaseScene
{
private:
    BaseRoot* base;
    Ogre::SceneManager  *sceneManager;
    Ogre::Camera        *camera;
    Ogre::Viewport      *viewport;

    void initBaseRoot();
    void initSceneManager();
    void initCamera();
    void initViewport();

public:
    BaseScene();
    ~BaseScene();
    void enterScene();
    void createScene();
};

}

#endif

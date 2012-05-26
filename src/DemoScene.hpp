#ifndef BELISKNER_DEMOSCENE_HPP
#define BELISKNER_DEMOSCENE_HPP

#include "OGRE/Ogre.h"
#include "OIS/OIS.h"

#include "BaseRoot.hpp"

namespace Beliskner
{

class DemoScene
{
private:
    BaseRoot* base;
    Ogre::SceneManager  *sceneManager;
    Ogre::Camera        *camera;
    Ogre::Viewport      *viewport;

    void initScene();

    void initBaseRoot();
    void initSceneManager();
    void initCamera();
    void initViewport();

public:
    DemoScene();
    ~DemoScene();

    void createScene();
};

}

#endif

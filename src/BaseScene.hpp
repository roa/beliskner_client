#ifndef BELISKNER_BASESCENE_HPP
#define BELISKNER_BASESCENE_HPP

#include "OGRE/Ogre.h"
#include "OIS/OIS.h"

namespace Beliskner
{

class SceneManager;

class BaseScene
{
public:
    Ogre::SceneManager  *sceneManager;
    Ogre::Camera        *camera;

    std::string sceneName;

    virtual void initSceneManager()     = 0;
    virtual void initCamera()           = 0;

    virtual void destroySceneManager()  = 0;
    virtual void destroyCamera()        = 0;

    virtual void enterScene()           = 0;
    virtual void exitScene()            = 0;

    virtual void createScene()          = 0;
};

}

#endif

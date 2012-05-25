#ifndef BELISKNER_BASEROOT_HPP
#define BELISKNER_BASEROOT_HPP

#include "OGRE/Ogre.h"

namespace Beliskner
{

class BaseRoot : public Ogre::Singleton<BaseRoot>
{

private:
    Ogre::Root          *root;
    Ogre::RenderWindow  *window;
    Ogre::SceneManager  *sceneManager;
    Ogre::Camera        *camera;
    Ogre::Viewport      *viewport;


public:
    BaseRoot();
    ~BaseRoot();

    bool initOgre();
    void run();
};

}

#endif

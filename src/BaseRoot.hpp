#ifndef BELISKNER_BASEROOT_HPP
#define BELISKNER_BASEROOT_HPP

#include "OGRE/Ogre.h"

#include "FrameListener.hpp"

namespace Beliskner
{

class BaseRoot : public Ogre::Singleton<BaseRoot>
{

private:
    Ogre::Log           *logger;
    Ogre::Root          *root;
    Ogre::RenderWindow  *window;
    Ogre::SceneManager  *sceneManager;
    Ogre::Camera        *camera;
    Ogre::Viewport      *viewport;
    FrameListener       *frameListener;

    void initLogManager();
    void initOgre();
    void initRoot();
    void initWindow();
    void initSceneManager();
    void initCamera();
    void initViewport();
    void initResourceManager();
    void initFrameListener();

public:
    BaseRoot();
    ~BaseRoot();

    void run();
};

}

#endif

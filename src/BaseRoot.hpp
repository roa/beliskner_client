#ifndef BELISKNER_BASEROOT_HPP
#define BELISKNER_BASEROOT_HPP

#include "OGRE/Ogre.h"

#include "FrameListener.hpp"
#include "SceneManager.hpp"
#include "BaseScene.hpp"
#include "DemoScene.hpp"
#include "DemoScene2.hpp"

namespace Beliskner
{

class FrameListener;
class SceneManager;

class BaseRoot : public Ogre::Singleton<BaseRoot>
{

public:
    Ogre::Log           *logger;
    Ogre::Root          *root;
    Ogre::RenderWindow  *window;
    Ogre::Viewport      *viewport;
    Ogre::Timer         *timer;

    FrameListener       *frameListener;
    SceneManager        *sceneManager;

    bool keepRunning;

    void initLogManager();
    void initOgre();
    void initRoot();
    void initWindow();
    void initViewport();
    void initTimer();

    void initResourceManager();
    void initFrameListener();
    void initSceneManager();

    void renderOneFrame();
    bool running();

    BaseRoot();
    ~BaseRoot();

private:

};

}

#endif

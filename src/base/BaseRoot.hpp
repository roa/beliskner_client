#ifndef BELISKNER_BASEROOT_HPP
#define BELISKNER_BASEROOT_HPP

#include "OGRE/Ogre.h"

#include "FrameListener.hpp"
#include "SceneManager.hpp"
#include "BaseScene.hpp"
#include "MainScene.hpp"
#include "NextScene.hpp"
#include "NoLogger.hpp"
#include "Player.hpp"

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>

namespace Beliskner
{

class FrameListener;
class SceneManager;
class Player;

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
    Player              *player;

    CEGUI::OgreRenderer *ceguiRenderer;

    bool keepRunning;

    void initLogManager();
    void initOgre();
    void initRoot();
    void initWindow();
    void initViewport();
    void initTimer();
    void initGui();
    void initPlayer();

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

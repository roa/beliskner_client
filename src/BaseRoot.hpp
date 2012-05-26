#ifndef BELISKNER_BASEROOT_HPP
#define BELISKNER_BASEROOT_HPP

#include "OGRE/Ogre.h"

#include "FrameListener.hpp"

namespace Beliskner
{

class BaseRoot : public Ogre::Singleton<BaseRoot>
{

public:
    Ogre::Log           *logger;
    Ogre::Root          *root;
    Ogre::RenderWindow  *window;
    FrameListener       *frameListener;

    bool keepRunning;

    void initLogManager();
    void initOgre();
    void initRoot();
    void initWindow();

    void initResourceManager();
    void initFrameListener();

    void renderOneFrame();
    bool running();

    BaseRoot();
    ~BaseRoot();

private:

};

}

#endif

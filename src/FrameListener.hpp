#ifndef BELISKNER_FRAMELISTENER_HPP
#define BELISKNER_FRAMELISTENER_HPP

#include "OGRE/Ogre.h"
#include "OIS/OIS.h"

#include "BaseRoot.hpp"

namespace Beliskner
{

class InputHandler;
class BaseRoot;

class FrameListener : public Ogre::FrameListener
{

public:
    OIS::InputManager   *inputManager;
    OIS::Keyboard       *keyboard;
    OIS::Mouse          *mouse;
    BaseRoot* base;

    bool leaveApp;

    FrameListener( Ogre::RenderWindow *_window );
    ~FrameListener();

    bool frameStarted( const Ogre::FrameEvent &evt );
    bool frameEnded( const Ogre::FrameEvent &evt );
    bool frameRenderingQueued( const Ogre::FrameEvent &evt );
};

}

#endif

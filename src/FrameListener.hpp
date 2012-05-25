#ifndef BELISKNER_FRAMELISTENER_HPP
#define BELISKNER_FRAMELISTENER_HPP

#include "OGRE/Ogre.h"
#include "OIS/OIS.h"

#include "InputHandler.hpp"

namespace Beliskner
{

class FrameListener : public Ogre::FrameListener
{

private:
    OIS::InputManager*  inputManager;
    OIS::Keyboard*      keyboard;

    InputHandler*       inputHandler;

public:
    FrameListener( Ogre::RenderWindow *_window );
    ~FrameListener();

    bool frameStarted( const Ogre::FrameEvent &evt );
    bool frameEnded( const Ogre::FrameEvent &evt );
    bool frameRenderingQueued( const Ogre::FrameEvent &evt );
};

}

#endif

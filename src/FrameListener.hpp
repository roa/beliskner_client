#ifndef BELISKNER_FRAMELISTENER_HPP
#define BELISKNER_FRAMELISTENER_HPP

#include "OGRE/Ogre.h"

namespace Beliskner
{

class FrameListener : public Ogre::FrameListener
{

private:

public:
    FrameListener();
    ~FrameListener();

    bool frameStarted( const Ogre::FrameEvent &evt );
    bool frameEnded( const Ogre::FrameEvent &evt );
    bool frameRenderingQueued( const Ogre::FrameEvent &evt );
};

}

#endif

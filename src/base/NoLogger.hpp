#ifndef BELISKNER_NO_LOGGER_HPP
#define BELISKNER_NO_LOGGER_HPP

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>

namespace Beliskner
{

class NoLogger : public CEGUI::Logger
{
    void logEvent ( const CEGUI::String&, CEGUI::LoggingLevel )
    {}
    void setLogFilename( const CEGUI::String&, bool )
    {}
};

}

#endif

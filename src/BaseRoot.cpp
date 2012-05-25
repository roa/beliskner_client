#include "BaseRoot.hpp"

namespace Beliskner
{

template<> BaseRoot* Ogre::Singleton<BaseRoot>::msSingleton = 0;

BaseRoot::BaseRoot()
{
    std::cout << "hucherlo" << std::endl;
    root            = NULL;
    window          = NULL;
    sceneManager    = NULL;
    camera          = NULL;
    viewport        = NULL;
}

BaseRoot::~BaseRoot()
{

}

bool BaseRoot::initOgre()
{
    root = new Ogre::Root( "/home/roa/programming/beliskner/beliskner_client/config/plugins.cfg");//, "config/Ogre.cfg" );

    if( !root->showConfigDialog() )
    {
        return false;
    }

    window = root->initialise( true, "Beliskner" );

    sceneManager = root->createSceneManager( Ogre::ST_GENERIC );

    camera = sceneManager->createCamera( "Camera" );
    camera->setPosition( Ogre::Vector3( 0, 0, 50 ) );
    camera->lookAt( Ogre::Vector3( 0, 0, 0 ) );
    camera->setNearClipDistance( 5 );

    viewport = window->addViewport( camera );
    viewport->setBackgroundColour( Ogre::ColourValue( 0.5, 0.5, 0.5 ) );

    camera->setAspectRatio( Ogre::Real( viewport->getActualWidth() ) / Ogre::Real( viewport->getActualHeight() ) );

    return true;
}

void BaseRoot::run()
{
    root->startRendering();
}

}

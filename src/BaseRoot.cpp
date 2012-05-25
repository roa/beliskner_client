#include "BaseRoot.hpp"

namespace Beliskner
{

template<> BaseRoot* Ogre::Singleton<BaseRoot>::msSingleton = 0;

BaseRoot::BaseRoot()
{
    logger          = NULL;
    root            = NULL;
    window          = NULL;
    sceneManager    = NULL;
    camera          = NULL;
    viewport        = NULL;
    frameListener   = NULL;
    keepRunning     = true;
    initLogManager();
    initOgre();
}

BaseRoot::~BaseRoot()
{
    delete root;
}

void BaseRoot::initLogManager()
{
    Ogre::LogManager *logMgr = new Ogre::LogManager();
    logger = logMgr->getSingleton().createLog( "log/Beliskner.log", true, true, false );
    logger->setDebugOutputEnabled( true );
    logger->logMessage( "initiated logmanager..." );
}

void BaseRoot::initOgre()
{
    initRoot();
    initWindow();
    initSceneManager();
    initCamera();
    initViewport();
    initResourceManager();
    initFrameListener();
}

void BaseRoot::initRoot()
{
    logger->logMessage( "initiating root..." );
    root = new Ogre::Root( "config/plugins.cfg", "config/Ogre.cfg" );

    if( !root->showConfigDialog() )
    {
        return;
    }
}

void BaseRoot::initWindow()
{
    logger->logMessage( "initiating window..." );
    window = root->initialise( true, "Beliskner" );
}

void BaseRoot::initSceneManager()
{
    logger->logMessage( "initiating scenemanager..." );
    sceneManager = root->createSceneManager( Ogre::ST_GENERIC );
}

void BaseRoot::initCamera()
{
    logger->logMessage( "initiating camera..." );
    camera = sceneManager->createCamera( "Camera" );
    camera->setPosition( Ogre::Vector3( 0, 0, 50 ) );
    camera->lookAt( Ogre::Vector3( 0, 0, 0 ) );
    camera->setNearClipDistance( 5 );
}

void BaseRoot::initViewport()
{
    logger->logMessage( "initiating viewport" );
    viewport = window->addViewport( camera );
    viewport->setBackgroundColour( Ogre::ColourValue( 0.5, 0.5, 0.5 ) );
    camera->setAspectRatio( Ogre::Real( viewport->getActualWidth() ) / Ogre::Real( viewport->getActualHeight() ) );
}

void BaseRoot::initResourceManager()
{
    logger->logMessage( "initiating resourcemanager...");
    Ogre::ConfigFile configFile;
    configFile.load( "config/resources.cfg" );
    Ogre::ConfigFile::SectionIterator sectioniter = configFile.getSectionIterator();
    Ogre::String sectionName, typeName, dataName;
    while( sectioniter.hasMoreElements() )
    {
        sectionName = sectioniter.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = sectioniter.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for( i = settings->begin(); i!= settings->end(); ++i )
        {
            typeName = i->first;
            dataName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation( dataName, typeName, sectionName );
        }
    }
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void BaseRoot::initFrameListener()
{
    logger->logMessage( "initiating framelistener..." );
    frameListener = new FrameListener( window );
    root->addFrameListener( frameListener );
}

void BaseRoot::renderOneFrame()
{
    Ogre::WindowEventUtilities::messagePump();
    keepRunning = root->renderOneFrame();
}

bool BaseRoot::running()
{
    return keepRunning;
}

void BaseRoot::runTest()
{
    Ogre::Entity *ent = sceneManager->createEntity( "Sinbad.mesh" );
    sceneManager->getRootSceneNode()->attachObject( ent );
    while( running() )
    {
        renderOneFrame();
    }
}

}

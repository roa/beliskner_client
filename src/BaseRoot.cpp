#include "BaseRoot.hpp"

namespace Beliskner
{

template<> BaseRoot* Ogre::Singleton<BaseRoot>::msSingleton = 0;

BaseRoot::BaseRoot()
{
    logger          = NULL;
    root            = NULL;
    window          = NULL;
    frameListener   = NULL;
    viewport        = NULL;
    timer           = NULL;

    keepRunning     = true;
    initLogManager();
    initOgre();
    initSceneManager();
}

BaseRoot::~BaseRoot()
{
    delete frameListener;
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
    initViewport();
    initTimer();
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

void BaseRoot::initViewport()
{
    logger->logMessage( "initiating viewport..." );
    viewport = window->addViewport( 0 );
    viewport->setBackgroundColour( Ogre::ColourValue( 0.5, 0.5, 0.5 ) );
    viewport->setCamera( 0 );
}

void BaseRoot::initTimer()
{
    logger->logMessage( "initiating timer..." );
    timer = new Ogre::Timer();
    timer->reset();
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

void BaseRoot::initSceneManager()
{
    sceneManager = new SceneManager();
    DemoScene *demoscene = new DemoScene( "mainScene" );
    sceneManager->addNewScene( demoscene );
    DemoScene2 *demoscene2 = new DemoScene2( "nextScene" );
    sceneManager->addNewScene( demoscene2 );
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

}

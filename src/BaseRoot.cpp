#include "BaseRoot.hpp"

namespace Beliskner
{

template<> BaseRoot* Ogre::Singleton<BaseRoot>::msSingleton = 0;

BaseRoot::BaseRoot()
{
    root            = NULL;
    window          = NULL;
    sceneManager    = NULL;
    camera          = NULL;
    viewport        = NULL;
    initOgre();
}

BaseRoot::~BaseRoot()
{

}

void BaseRoot::initOgre()
{
    initRoot();
    initWindow();
    initSceneManager();
    initCamera();
    initViewport();
    initResourceManager();
}

void BaseRoot::initRoot()
{
    root = new Ogre::Root( "config/plugins.cfg", "config/Ogre.cfg" );

    if( !root->showConfigDialog() )
    {
        return;
    }
}

void BaseRoot::initWindow()
{
    window = root->initialise( true, "Beliskner" );
}

void BaseRoot::initSceneManager()
{
    sceneManager = root->createSceneManager( Ogre::ST_GENERIC );
}

void BaseRoot::initCamera()
{
    camera = sceneManager->createCamera( "Camera" );
    camera->setPosition( Ogre::Vector3( 0, 0, 50 ) );
    camera->lookAt( Ogre::Vector3( 0, 0, 0 ) );
    camera->setNearClipDistance( 5 );
}

void BaseRoot::initViewport()
{
    viewport = window->addViewport( camera );
    viewport->setBackgroundColour( Ogre::ColourValue( 0.5, 0.5, 0.5 ) );
    camera->setAspectRatio( Ogre::Real( viewport->getActualWidth() ) / Ogre::Real( viewport->getActualHeight() ) );
}

void BaseRoot::initResourceManager()
{
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

void BaseRoot::run()
{
    Ogre::Entity *ent = sceneManager->createEntity( "Sinbad.mesh" );
    sceneManager->getRootSceneNode()->attachObject( ent );
    root->startRendering();
}

}

#include "NextScene.hpp"

namespace Beliskner
{

NextScene::NextScene( std::string _sceneName )
{
    base = BaseRoot::getSingletonPtr();
    ceguiRenderer = base->ceguiRenderer;
    sceneName = _sceneName;
    sceneManager = NULL;
    camera       = NULL;
    sceneSwitch  = false;
}

NextScene::~NextScene()
{

}

void NextScene::createScene()
{
    sceneSwitch = false;
    Ogre::Entity *ent = sceneManager->createEntity( "penguin.mesh" );
    //sceneManager->getRootSceneNode()->attachObject( ent );
        ceguiRenderer= &CEGUI::OgreRenderer::bootstrapSystem();
        CEGUI::SchemeManager::getSingleton().create( "TaharezLook.scheme" );
        CEGUI::System::getSingleton().setDefaultFont( "DejaVuSans-10" );
        CEGUI::System::getSingleton().setDefaultMouseCursor( "TaharezLook", "MouseArrow" );
        CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::Informative); // this is recommended to help with debugging, but not neccessary

        myRoot = CEGUI::WindowManager::getSingleton().createWindow( "DefaultWindow", "RootWindow" );
        CEGUI::System::getSingleton().setGUISheet( myRoot );
        CEGUI::FrameWindow* fWnd = static_cast<CEGUI::FrameWindow*>(
    CEGUI::WindowManager::getSingleton().createWindow( "TaharezLook/FrameWindow", "testWindow" ));
    myRoot->addChildWindow( fWnd );

}

void NextScene::prepareScene()
{
    initSceneManager();
    initCamera();
}

void NextScene::exitScene()
{
    ceguiRenderer->destroySystem();
    destroyCamera();
    destroySceneManager();
}

void NextScene::switchScene()
{
    if( sceneSwitch )
        base->sceneManager->switchToScene( "mainScene" );
}

void NextScene::initSceneManager()
{
    base->logger->logMessage( "initiating scenemanager in NextScene..." );
    sceneManager = base->root->createSceneManager( Ogre::ST_GENERIC );
}

void NextScene::initCamera()
{
    base->logger->logMessage( "initiating camera..." );
    camera = sceneManager->createCamera( "Camera" );
    camera->setPosition( Ogre::Vector3( 0, 0, 50 ) );
    camera->lookAt( Ogre::Vector3( 0, 0, 0 ) );
    camera->setNearClipDistance( 5 );
    camera->setAspectRatio( Ogre::Real( base->viewport->getActualWidth() ) / Ogre::Real( base->viewport->getActualHeight() ) );
    base->viewport->setCamera( camera );
}

void NextScene::destroySceneManager()
{
    base->root->destroySceneManager( sceneManager );
}

void NextScene::destroyCamera()
{
    sceneManager->destroyCamera( camera );
}

void NextScene::updateScene()
{
    updateKeyboard();
    updateMouse();
    switchScene();
}

void NextScene::updateKeyboard()
{
    base->frameListener->keyboard->capture();
    if( base->frameListener->keyboard->isKeyDown( OIS::KC_ESCAPE ) )
    {
        base->frameListener->leaveApp = true;
    }
    if( base->frameListener->keyboard->isKeyDown( OIS::KC_S) )
    {
        sceneSwitch = true;
    }
}

void NextScene::updateMouse()
{
    base->frameListener->mouse->capture();
    CEGUI::System::getSingleton().injectTimePulse( base->timer->getMilliseconds() * 0.001f );
}

bool NextScene::keyPressed( const OIS::KeyEvent& evt )
{
    return true;
}

bool NextScene::keyReleased( const OIS::KeyEvent& evt )
{
    return true;
}

bool NextScene::mouseMoved( const OIS::MouseEvent& evt )
{
    CEGUI::System &sys = CEGUI::System::getSingleton();
    sys.injectMouseMove(evt.state.X.rel, evt.state.Y.rel);
    // Scroll wheel.
    if (evt.state.Z.rel)
        sys.injectMouseWheelChange(evt.state.Z.rel / 120.0f);
    return true;
}

bool NextScene::mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
    CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));
    return true;
}

bool NextScene::mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
    CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));
    return true;
}

CEGUI::MouseButton NextScene::convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;

    case OIS::MB_Right:
        return CEGUI::RightButton;

    case OIS::MB_Middle:
        return CEGUI::MiddleButton;

    default:
        return CEGUI::LeftButton;
    }
}

}

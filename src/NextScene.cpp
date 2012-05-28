#include "NextScene.hpp"

namespace Beliskner
{

NextScene::NextScene( std::string _sceneName )
{
    playerName = "playername";
    std::stringstream tempstream;
    playerLife = 500;
    playerMana = 500;
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
    sceneManager->getRootSceneNode()->attachObject( ent );



}

bool NextScene::attackButtonClicked( const CEGUI::EventArgs& )
{
    std::cout << "attack" << std::endl;
    return true;
}

bool NextScene::magicButtonClicked( const CEGUI::EventArgs& )
{
    std::cout << "magic" << std::endl;
    return true;
}

std::string NextScene::playerStatusString()
{
    std::stringstream playerStatus;
    playerStatus << "HP " << playerLife << " MP " << playerMana;
    return playerStatus.str();
}

void NextScene::prepareScene()
{
    initSceneManager();
    initCamera();
    initGui();
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

void NextScene::initGui()
{
    ceguiRenderer= &CEGUI::OgreRenderer::bootstrapSystem();
    CEGUI::SchemeManager::getSingleton().create( "TaharezLook.scheme" );
    CEGUI::System::getSingleton().setDefaultFont( "DejaVuSans-10" );
    CEGUI::System::getSingleton().setDefaultMouseCursor( "TaharezLook", "MouseArrow" );

    myRoot = CEGUI::WindowManager::getSingleton().createWindow( "DefaultWindow", "RootWindow" );
    CEGUI::System::getSingleton().setGUISheet( myRoot );

    CEGUI::Window* MenuBackground = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage", "Background");
    MenuBackground->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.004f, 0.0f ), CEGUI::UDim( 0.85f, 0.0f) ) );
    MenuBackground->setSize( CEGUI::UVector2( CEGUI::UDim( 0.14f, 0.0f ), CEGUI::UDim( 0.14f, 0.0f ) ) );  // full screen
    MenuBackground->setProperty( "Alpha", "0.50" );
    myRoot->addChildWindow( MenuBackground );

    CEGUI::Window* StatsBackground = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage", "StatsBackground");
    StatsBackground->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.70f, 0.0f ), CEGUI::UDim( 0.92f, 0.0f) ) );
    StatsBackground->setSize( CEGUI::UVector2( CEGUI::UDim( 0.295f, 0.0f ), CEGUI::UDim( 0.07f, 0.0f ) ) );  // full screen
    StatsBackground->setProperty( "Alpha", "0.50" );
    myRoot->addChildWindow( StatsBackground );

    CEGUI::PushButton* attackLabel = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button", "attackLabel"));
    attackLabel->setSize(CEGUI::UVector2( CEGUI::UDim( 0.12f, 0.0f ), CEGUI::UDim( 0.05f, 0.0f ) ));
    attackLabel->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.012f, 0.0f ), CEGUI::UDim( 0.86f, 0.0f) ));
    attackLabel->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&NextScene::attackButtonClicked,this));
    attackLabel->setText( "Attack" );
    myRoot->addChildWindow(attackLabel);

    CEGUI::PushButton* magicLabel = static_cast<CEGUI::PushButton*>(CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button", "magicLabel"));
    magicLabel->setText( "Magic" );
    magicLabel->setSize(CEGUI::UVector2( CEGUI::UDim( 0.12f, 0.0f ), CEGUI::UDim( 0.05f, 0.0f ) ));
    magicLabel->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.012f, 0.0f ), CEGUI::UDim( 0.92f, 0.0f) ));
    magicLabel->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&NextScene::magicButtonClicked,this));
    myRoot->addChildWindow(magicLabel);

    CEGUI::DefaultWindow* displayedPlayerName = static_cast<CEGUI::DefaultWindow*>(CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticText", "playerName"));
    displayedPlayerName->setText( playerName );
    displayedPlayerName->setProperty("TextColours", "tl:FFFFFFFF tr:FFFFFFFF bl:FFFFFFFF br:FFFF0000");
    displayedPlayerName->setProperty("VertFormatting", "VertCentred");
    displayedPlayerName->setProperty("HorzFormatting", "HorzCentred");
    displayedPlayerName->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.705f, 0.0f ), CEGUI::UDim( 0.93f, 0.0f) ) );
    displayedPlayerName->setSize( CEGUI::UVector2( CEGUI::UDim( 0.10f, 0.0f ), CEGUI::UDim( 0.05f, 0.0f) ) );
    displayedPlayerName->setProperty("BackgroundEnabled", "false");
    displayedPlayerName->setProperty("FrameEnabled", "false");
    myRoot->addChildWindow(displayedPlayerName);

    CEGUI::DefaultWindow* displayedPlayerLife = static_cast<CEGUI::DefaultWindow*>(CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticText", "playerLife"));
    displayedPlayerLife->setText( playerStatusString() );
    displayedPlayerLife->setProperty("TextColours", "tl:FFFFFFFF tr:FFFFFFFF bl:FFFFFFFF br:FFFF0000");
    displayedPlayerLife->setProperty("VertFormatting", "VertCentred");
    displayedPlayerLife->setProperty("HorzFormatting", "HorzCentred");
    displayedPlayerLife->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.775f, 0.0f ), CEGUI::UDim( 0.93f, 0.0f) ) );
    displayedPlayerLife->setSize( CEGUI::UVector2( CEGUI::UDim( 0.24f, 0.0f ), CEGUI::UDim( 0.05f, 0.0f) ) );
    displayedPlayerLife->setProperty("BackgroundEnabled", "false");
    displayedPlayerLife->setProperty("FrameEnabled", "false");
    myRoot->addChildWindow(displayedPlayerLife);
/*
    CEGUI::DefaultWindow* displayedPlayerMana = static_cast<CEGUI::DefaultWindow*>(CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticText", "playerMana"));
    displayedPlayerMana->setText( playerMP );
    displayedPlayerMana->setProperty("TextColours", "tl:FFFFFFFF tr:FFFFFFFF bl:FFFFFFFF br:FFFF0000");
    displayedPlayerMana->setProperty("VertFormatting", "VertCentred");
    displayedPlayerMana->setProperty("HorzFormatting", "HorzCentred");
    displayedPlayerMana->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.955f, 0.0f ), CEGUI::UDim( 0.93f, 0.0f) ) );
    displayedPlayerMana->setSize( CEGUI::UVector2( CEGUI::UDim( 0.12f, 0.0f ), CEGUI::UDim( 0.05f, 0.0f) ) );
    displayedPlayerMana->setProperty("BackgroundEnabled", "false");
    displayedPlayerMana->setProperty("FrameEnabled", "false");
    myRoot->addChildWindow(displayedPlayerMana);
*/
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

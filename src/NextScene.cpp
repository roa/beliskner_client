#include "NextScene.hpp"

namespace Beliskner
{

NextScene::NextScene( std::string _sceneName )
{
    base = BaseRoot::getSingletonPtr();
    ceguiRenderer    = base->ceguiRenderer;
    sceneName        = _sceneName;
    sceneManager     = NULL;
    camera           = NULL;
    sceneSwitch      = false;
    playerAction     = false;
}

NextScene::~NextScene()
{

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
    camera->setPosition( Ogre::Vector3( -50, 20, 0 ) );
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

    CEGUI::Window* MenuBackground = CEGUI::WindowManager::getSingleton().createWindow( "TaharezLook/StaticImage", "Background" );
    MenuBackground->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.004f, 0.0f ), CEGUI::UDim( 0.85f, 0.0f ) ) );
    MenuBackground->setSize( CEGUI::UVector2( CEGUI::UDim( 0.14f, 0.0f ), CEGUI::UDim( 0.14f, 0.0f ) ) );
    MenuBackground->setProperty( "Alpha", "0.50" );
    myRoot->addChildWindow( MenuBackground );

    CEGUI::Window* StatsBackground = CEGUI::WindowManager::getSingleton().createWindow( "TaharezLook/StaticImage", "StatsBackground" );
    StatsBackground->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.70f, 0.0f ), CEGUI::UDim( 0.92f, 0.0f ) ) );
    StatsBackground->setSize( CEGUI::UVector2( CEGUI::UDim( 0.295f, 0.0f ), CEGUI::UDim( 0.07f, 0.0f ) ) );
    StatsBackground->setProperty( "Alpha", "0.50" );
    myRoot->addChildWindow( StatsBackground );

    CEGUI::PushButton* attackLabel = static_cast<CEGUI::PushButton*>( CEGUI::WindowManager::getSingleton().createWindow( "TaharezLook/Button", "attackLabel") );
    attackLabel->setSize( CEGUI::UVector2( CEGUI::UDim( 0.12f, 0.0f ), CEGUI::UDim( 0.05f, 0.0f ) ) );
    attackLabel->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.012f, 0.0f ), CEGUI::UDim( 0.86f, 0.0f ) ) );
    attackLabel->subscribeEvent( CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber( &NextScene::attackButtonClicked,this ) );
    attackLabel->setText( "Attack" );
    myRoot->addChildWindow( attackLabel );

    CEGUI::PushButton* magicLabel = static_cast<CEGUI::PushButton*>( CEGUI::WindowManager::getSingleton().createWindow( "TaharezLook/Button", "magicLabel" ) );
    magicLabel->setText( "Magic" );
    magicLabel->setSize( CEGUI::UVector2( CEGUI::UDim( 0.12f, 0.0f ), CEGUI::UDim( 0.05f, 0.0f ) ) );
    magicLabel->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.012f, 0.0f ), CEGUI::UDim( 0.92f, 0.0f ) ) );
    magicLabel->subscribeEvent( CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber( &NextScene::magicButtonClicked,this ) );
    myRoot->addChildWindow( magicLabel );

    CEGUI::DefaultWindow* displayedPlayerName = static_cast<CEGUI::DefaultWindow*>( CEGUI::WindowManager::getSingleton().createWindow( "TaharezLook/StaticText", "playerName" ) );
    displayedPlayerName->setText( base->player->name );
    displayedPlayerName->setProperty( "TextColours", "tl:FFFFFFFF tr:FFFFFFFF bl:FFFFFFFF br:FFFF0000" );
    displayedPlayerName->setProperty( "VertFormatting", "VertCentred" );
    displayedPlayerName->setProperty( "HorzFormatting", "HorzCentred" );
    displayedPlayerName->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.705f, 0.0f ), CEGUI::UDim( 0.93f, 0.0f ) ) );
    displayedPlayerName->setSize( CEGUI::UVector2( CEGUI::UDim( 0.10f, 0.0f ), CEGUI::UDim( 0.05f, 0.0f ) ) );
    displayedPlayerName->setProperty( "BackgroundEnabled", "false" );
    displayedPlayerName->setProperty( "FrameEnabled", "false" );
    myRoot->addChildWindow( displayedPlayerName );

    displayedPlayerStatus = static_cast<CEGUI::DefaultWindow*>( CEGUI::WindowManager::getSingleton().createWindow( "TaharezLook/StaticText", "playerLife" ) );
    displayedPlayerStatus->setText( playerStatusString() );
    displayedPlayerStatus->setProperty( "TextColours", "tl:FFFFFFFF tr:FFFFFFFF bl:FFFFFFFF br:FFFF0000" );
    displayedPlayerStatus->setProperty( "VertFormatting", "VertCentred" );
    displayedPlayerStatus->setProperty( "HorzFormatting", "HorzCentred" );
    displayedPlayerStatus->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.775f, 0.0f ), CEGUI::UDim( 0.93f, 0.0f ) ) );
    displayedPlayerStatus->setSize( CEGUI::UVector2( CEGUI::UDim( 0.24f, 0.0f ), CEGUI::UDim( 0.05f, 0.0f ) ) );
    displayedPlayerStatus->setProperty( "BackgroundEnabled", "false" );
    displayedPlayerStatus->setProperty( "FrameEnabled", "false" );
    myRoot->addChildWindow( displayedPlayerStatus );
}

void NextScene::initMonster()
{
    monster = new Monster( "ninja", this );
}

void NextScene::destroySceneManager()
{
    base->root->destroySceneManager( sceneManager );
}

void NextScene::destroyCamera()
{
    sceneManager->destroyCamera( camera );
}

void NextScene::updateKeyboard()
{
    base->frameListener->keyboard->capture();
    if( base->frameListener->keyboard->isKeyDown( OIS::KC_ESCAPE ) )
    {
        base->frameListener->leaveApp = true;
    }
    if( base->frameListener->keyboard->isKeyDown( OIS::KC_S ) )
    {
        sceneSwitch = true;
    }
}

void NextScene::updateMouse()
{
    base->frameListener->mouse->capture();
    CEGUI::System::getSingleton().injectTimePulse( base->timer->getMilliseconds() * 0.001f );
}

void NextScene::updateAnimations()
{
    if( base->player->playerActionInProgress )
    {
        base->player->makeAnimations();
        return;
    }

    if( monster->monsterActionInProgress )
    {
        monster->makeAnimations();
        return;
    }
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
    sys.injectMouseMove( evt.state.X.rel, evt.state.Y.rel );
    // Scroll wheel.
    if( evt.state.Z.rel )
        sys.injectMouseWheelChange( evt.state.Z.rel / 120.0f );
    return true;
}

bool NextScene::mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
    CEGUI::System::getSingleton().injectMouseButtonDown( convertButton( id ) );
    return true;
}

bool NextScene::mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
    CEGUI::System::getSingleton().injectMouseButtonUp( convertButton( id ) );
    return true;
}

CEGUI::MouseButton NextScene::convertButton( OIS::MouseButtonID buttonID )
{
    switch ( buttonID )
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

bool NextScene::attackButtonClicked( const CEGUI::EventArgs& )
{
    base->player->attackPlayer = true;
    base->player->hitMonster = true;
    ++base->player->playerTurns;
    base->player->playerActionInProgress = true;
    return true;
}

bool NextScene::magicButtonClicked( const CEGUI::EventArgs& )
{
    base->player->playerMana -= 10;
    displayedPlayerStatus->setText( playerStatusString() );
    return true;
}

std::string NextScene::playerStatusString()
{
    std::stringstream playerStatus;
    playerStatus << "HP " << base->player->playerLife << " MP " << base->player->playerMana;
    return playerStatus.str();
}
void NextScene::createScene()
{
    sceneSwitch = false;

    Ogre::Plane plane( Ogre::Vector3::UNIT_Y, -5 );
    Ogre::MeshManager::getSingleton().createPlane( "plane",
                                                    Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                    plane,
                                                    1500, 1500, 200, 200, true, 1, 5, 5, Ogre::Vector3::UNIT_Z
                                                 );
    Ogre::Entity *ground = sceneManager->createEntity( "LightPlane", "plane" );
    sceneManager->getRootSceneNode()->attachObject( ground );
    ground->setMaterialName( "Examples/BeachStones" );

    Ogre::Light *light = sceneManager->createLight( "Light1" );
    light->setType( Ogre::Light::LT_DIRECTIONAL );
    light->setDirection( Ogre::Vector3( 1, -1, 0 ) );

    base->player->setUpScene();
    monster->setUpScene();

}

void NextScene::prepareScene()
{
    initSceneManager();
    initCamera();
    initGui();
    initMonster();
}

void NextScene::exitScene()
{
    ceguiRenderer->destroySystem();
    destroyCamera();
    destroySceneManager();
    delete monster;
    base->player->leaveScene();
    base->player->playerTurns  = 0;
}

void NextScene::switchScene()
{
    if( sceneSwitch )
        base->sceneManager->switchToScene( "mainScene" );
}

void NextScene::updateScene()
{
    if( !monster->monsterActionInProgress && !base->player->playerActionInProgress )
        updateTurn();
    updateGui();
    updateKeyboard();
    updateMouse();
    updateAnimations();
    switchScene();
}

void NextScene::updateTurn()
{
    float turnRatioShould = monster->monsterSpeed / base->player->playerSpeed;
    float turnRatioIs = ( monster->monsterTurns + 1 ) / ( base->player->playerTurns + 1 );
    if( base->player->playerTurns == 0 && monster->monsterTurns == 0 )
    {
        srand( time( NULL ) );
        if( rand() % 2 )
        {
            playerAction = true;
        }
    }
    else
    {
        if( turnRatioIs >= turnRatioShould )
        {
            playerAction = true;
        }
        else
        {
            playerAction = false;
        }
    }
    if( !playerAction )
    {
        std::cout << "monsterTrn" << std::endl;
        ++monster->monsterTurns;
        monster->monsterActionInProgress = true;
        monster->hitPlayer = true;
        monster->attackMonster = true;
    }
}

void NextScene::updateGui()
{
    displayedPlayerStatus->setText( playerStatusString() );
    if( playerAction )
    {
    }
    else
    {
    }
}
}

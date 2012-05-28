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
    attackPlayer     = false;
    invertPlayerDir  = false;
    magicPlayer      = false;
    sceneSwitch      = false;
    hitMonster       = false;
    hitAni           = false;
    playerTurns      = 0;

    playerAction     = false;
    playerActionInProgress = false;
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
    displayedPlayerName->setText( base->player->name );
    displayedPlayerName->setProperty("TextColours", "tl:FFFFFFFF tr:FFFFFFFF bl:FFFFFFFF br:FFFF0000");
    displayedPlayerName->setProperty("VertFormatting", "VertCentred");
    displayedPlayerName->setProperty("HorzFormatting", "HorzCentred");
    displayedPlayerName->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.705f, 0.0f ), CEGUI::UDim( 0.93f, 0.0f) ) );
    displayedPlayerName->setSize( CEGUI::UVector2( CEGUI::UDim( 0.10f, 0.0f ), CEGUI::UDim( 0.05f, 0.0f) ) );
    displayedPlayerName->setProperty("BackgroundEnabled", "false");
    displayedPlayerName->setProperty("FrameEnabled", "false");
    myRoot->addChildWindow(displayedPlayerName);

    displayedPlayerStatus = static_cast<CEGUI::DefaultWindow*>(CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticText", "playerLife"));
    displayedPlayerStatus->setText( playerStatusString() );
    displayedPlayerStatus->setProperty("TextColours", "tl:FFFFFFFF tr:FFFFFFFF bl:FFFFFFFF br:FFFF0000");
    displayedPlayerStatus->setProperty("VertFormatting", "VertCentred");
    displayedPlayerStatus->setProperty("HorzFormatting", "HorzCentred");
    displayedPlayerStatus->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.775f, 0.0f ), CEGUI::UDim( 0.93f, 0.0f) ) );
    displayedPlayerStatus->setSize( CEGUI::UVector2( CEGUI::UDim( 0.24f, 0.0f ), CEGUI::UDim( 0.05f, 0.0f) ) );
    displayedPlayerStatus->setProperty("BackgroundEnabled", "false");
    displayedPlayerStatus->setProperty("FrameEnabled", "false");
    myRoot->addChildWindow(displayedPlayerStatus);
}

void NextScene::initMonster()
{
    monster = new Monster( "ninja", monsterEnt, monsterNode, this );
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

void NextScene::updateAnimations()
{
    if( playerActionInProgress )
    {
        if( playerNode->getPosition().z == 23 )
        {
            if( hitMonster )
            {
                hitAni->setEnabled(true);
                hitAni->addTime( base->timer->getMilliseconds() * 0.001f );
                if( hitAni->hasEnded() )
                {
                    hitAni->setEnabled(false);
                    hitAni->setTimePosition( 0.0f );
                    hitMonster = false;
                }
                return;
            }
            else
            {
                invertPlayerDir = true;
                playerNode->yaw( Ogre::Degree( 180 ) );
            }
        }

        Ogre::Vector3 transDir(0, 0, 0);
        if( invertPlayerDir )
        {
            transDir.z = -1;
        }
        else
        {
            transDir.z = 1;
        }
        if( attackPlayer )
        {
            playerNode->translate( transDir * 0.5f );
            aniState->setEnabled( true );
            aniStateTop->setEnabled( true );

            if( aniState->hasEnded() )
            {
                aniState->setTimePosition( 0.0f );
            }
            if( aniStateTop->hasEnded() )
            {
                aniStateTop->setTimePosition( 0.0f );
            }
        }
        else
        {
            aniState->setTimePosition( 0.0f );
            aniState->setEnabled( false );
            aniStateTop->setTimePosition( 0.0f );
            aniStateTop->setEnabled( false );
        }
        aniState->addTime( base->timer->getMilliseconds() * 0.001f );
        aniStateTop->addTime( base->timer->getMilliseconds() * 0.001f );
        if( attackPlayer && playerNode->getPosition().z == -25 )
        {
            attackPlayer = false;
            playerActionInProgress = false;
            invertPlayerDir = false;
            playerNode->yaw( Ogre::Degree( 180 ) );
            aniState->setTimePosition( 0.0f );
            aniStateTop->setTimePosition( 0.0f );
        }
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

bool NextScene::attackButtonClicked( const CEGUI::EventArgs& )
{
    attackPlayer = true;
    hitMonster = true;
    ++playerTurns;
    playerActionInProgress = true;
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

    playerEnt = sceneManager->createEntity( "Sinbad.mesh" );
    playerNode = sceneManager->getRootSceneNode()->createChildSceneNode();
    playerNode->setPosition( 0, 0, -25 );
    playerNode->attachObject( playerEnt );

    aniState    = playerEnt->getAnimationState( "RunBase" );
    aniState->setLoop( false );

    aniStateTop = playerEnt->getAnimationState( "RunTop" );
    aniStateTop->setLoop( false );

    hitAni = playerEnt->getAnimationState( "DrawSwords" );
    hitAni->setLoop( false );

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
    playerTurns  = 0;
}

void NextScene::switchScene()
{
    if( sceneSwitch )
        base->sceneManager->switchToScene( "mainScene" );
}

void NextScene::updateScene()
{
    if( !monster->monsterActionInProgress && !playerActionInProgress )
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
    float turnRatioIs = ( monster->monsterTurns + 1 ) / ( playerTurns + 1 );
    if( playerTurns == 0 && monster->monsterTurns == 0 )
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

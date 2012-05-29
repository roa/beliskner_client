#include "MainScene.hpp"

namespace Beliskner
{

MainScene::MainScene( std::string _sceneName )
{
    sceneName = _sceneName;
    base = BaseRoot::getSingletonPtr();
    sceneManager = NULL;
    camera       = NULL;

    cameraPosition = ( 0, 0, 50 );
    sceneSwitch  = false;
}

MainScene::~MainScene()
{

}

void MainScene::createScene()
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
    sceneManager->setShadowTechnique( Ogre::SHADOWTYPE_STENCIL_ADDITIVE );
}

void MainScene::prepareScene()
{
    initSceneManager();
    initCamera();
}

void MainScene::exitScene()
{
    cameraPosition = camera->getPosition();
    destroyCamera();
    destroySceneManager();
}

void MainScene::switchScene()
{
    if( sceneSwitch )
        base->sceneManager->switchToScene( "nextScene" );
}

void MainScene::initSceneManager()
{
    base->logger->logMessage( "initiating scenemanager in MainScene..." );
    sceneManager = base->root->createSceneManager( Ogre::ST_GENERIC );
}

void MainScene::initCamera()
{
    base->logger->logMessage( "initiating camera..." );
    camera = sceneManager->createCamera( "Camera" );
    camera->setPosition( Ogre::Vector3( cameraPosition ) );
    camera->lookAt( Ogre::Vector3( 0, 0, 0 ) );
    camera->setNearClipDistance( 5 );
    camera->setAspectRatio( Ogre::Real( base->viewport->getActualWidth() ) / Ogre::Real( base->viewport->getActualHeight() ) );
    base->viewport->setCamera( camera );
}

void MainScene::destroySceneManager()
{
    base->root->destroySceneManager( sceneManager );
}

void MainScene::destroyCamera()
{
    sceneManager->destroyCamera( camera );
}

void MainScene::updateScene()
{
    updateMouse();
    updateKeyboard();
    //updateAnimations();
    base->player->makeWalkAnimations();
    switchScene();
}

void MainScene::updateKeyboard()
{
    base->frameListener->keyboard->capture();

    if( base->frameListener->keyboard->isKeyDown( OIS::KC_ESCAPE ) )
    {
        base->frameListener->leaveApp = true;
    }

    if( base->frameListener->keyboard->isKeyDown( OIS::KC_X ) )
    {
        sceneSwitch = true;

        return;
    }

    Ogre::Vector3 camTranslate( 0, 0, 0 );
    if( base->frameListener->keyboard->isKeyDown( OIS::KC_W ) )
    {
        camTranslate += Ogre::Vector3( 0, 0, -1 );
    }
    if( base->frameListener->keyboard->isKeyDown( OIS::KC_S ) )
    {
        camTranslate += Ogre::Vector3( 0, 0, 1 );
    }
    if( base->frameListener->keyboard->isKeyDown( OIS::KC_A ) )
    {
        camTranslate += Ogre::Vector3( -1, 0, 0 );
    }
    if( base->frameListener->keyboard->isKeyDown( OIS::KC_D ) )
    {
        camTranslate += Ogre::Vector3( 1, 0, 0 );
    }
    camera->moveRelative( camTranslate * base->timer->getMilliseconds() * 0.01f );

    Ogre::Vector3 playerTranslate( 0, 0, 0 );
    float playerRotation = 0;
    bool up    = false;
    bool down  = false;
    bool right = false;
    bool left  = false;
    if( base->frameListener->keyboard->isKeyDown( OIS::KC_UP ) )
    {
        playerTranslate += Ogre::Vector3( 0, 0, -1 );
        playerRotation   = 180;
        base->player->playerWalked     = true;
        up               = true;
    }
    if( base->frameListener->keyboard->isKeyDown( OIS::KC_DOWN ) )
    {
        playerTranslate += Ogre::Vector3( 0, 0, 1 );
        playerRotation   = 0;
        base->player->playerWalked     = true;
        down             = true;
    }
    if( base->frameListener->keyboard->isKeyDown( OIS::KC_LEFT ) )
    {
        playerTranslate += Ogre::Vector3( -1, 0, 0 );
        playerRotation   = 270;
        base->player->playerWalked     = true;
        left             = true;
    }
    if( base->frameListener->keyboard->isKeyDown( OIS::KC_RIGHT ) )
    {
        playerTranslate += Ogre::Vector3( 1, 0, 0 );
        playerRotation   = 90;
        base->player->playerWalked     = true;
        right            = true;
    }
    if( up && left )
        playerRotation = 225;
    if( up && right )
        playerRotation = 135;
    if( down && left )
        playerRotation = 305;
    if( down && right )
        playerRotation = 45;
    base->player->playerNode->translate( playerTranslate * 0.5f );
    base->player->playerNode->resetOrientation();
    base->player->playerNode->yaw( Ogre::Degree( playerRotation ) );
}

void MainScene::updateMouse()
{
    base->frameListener->mouse->capture();

    float rotX = base->frameListener->mouse->getMouseState().X.rel * -0.01f;
    float rotY = base->frameListener->mouse->getMouseState().Y.rel * -0.01f;

    camera->yaw( Ogre::Radian( rotX ) );
    camera->pitch( Ogre::Radian( rotY ) );
}

bool MainScene::keyPressed( const OIS::KeyEvent& evt )
{
    return true;
}

bool MainScene::keyReleased( const OIS::KeyEvent& evt )
{
    return true;
}

bool MainScene::mouseMoved( const OIS::MouseEvent& evt )
{
    return true;
}

bool MainScene::mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
    return true;
}

bool MainScene::mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
    return true;
}

}

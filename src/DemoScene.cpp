#include "DemoScene.hpp"

namespace Beliskner
{

DemoScene::DemoScene( std::string _sceneName )
{
    sceneName = _sceneName;
    sceneManager = NULL;
    camera       = NULL;
    playerWalked = false;
    initBaseRoot();
    std::cout << "const" << std::endl;
}

DemoScene::~DemoScene()
{

}

void DemoScene::initBaseRoot()
{
    base = BaseRoot::getSingletonPtr();
}

void DemoScene::createScene()
{
    std::cout << "create" << std::endl;

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

    playerEnt   = sceneManager->createEntity( "Sinbad.mesh" );
    aniState    = playerEnt->getAnimationState( "RunBase" );
    aniState->setLoop( false );

    aniStateTop = playerEnt->getAnimationState( "RunTop" );
    aniStateTop->setLoop( false );

    playerNode = sceneManager->getRootSceneNode()->createChildSceneNode();
    playerNode->attachObject( playerEnt );

    sceneManager->setShadowTechnique( Ogre::SHADOWTYPE_STENCIL_ADDITIVE );
}

void DemoScene::enterScene()
{
    initSceneManager();
    initCamera();
}

void DemoScene::exitScene()
{
    destroyCamera();
    destroySceneManager();
}

void DemoScene::initSceneManager()
{
    base->logger->logMessage( "initiating scenemanager in DemoScene..." );
    sceneManager = base->root->createSceneManager( Ogre::ST_GENERIC );
}

void DemoScene::initCamera()
{
    base->logger->logMessage( "initiating camera..." );
    camera = sceneManager->createCamera( "Camera" );
    camera->setPosition( Ogre::Vector3( 0, 0, 50 ) );
    camera->lookAt( Ogre::Vector3( 0, 0, 0 ) );
    camera->setNearClipDistance( 5 );
    camera->setAspectRatio( Ogre::Real( base->viewport->getActualWidth() ) / Ogre::Real( base->viewport->getActualHeight() ) );
    base->viewport->setCamera( camera );
}

void DemoScene::destroySceneManager()
{
    base->root->destroySceneManager( sceneManager );
}

void DemoScene::destroyCamera()
{
    sceneManager->destroyCamera( camera );
}

void DemoScene::updateScene()
{
    updateMouse();
    updateKeyboard();
    updateAnimations();
}

void DemoScene::updateKeyboard()
{
    base->frameListener->keyboard->capture();

    if( base->frameListener->keyboard->isKeyDown( OIS::KC_ESCAPE ) )
    {
        base->frameListener->leaveApp = true;
    }

    if( base->frameListener->keyboard->isKeyDown( OIS::KC_X ) )
    {
        base->sceneManager->switchToScene( "nextScene" );
        return;
    }

    Ogre::Vector3 camTranslate( 0, 0, 0 );
    if( base->frameListener->keyboard->isKeyDown( OIS::KC_W ) )
    {
        camTranslate += Ogre::Vector3( 0, 0, -1 );
    }
    if( base->frameListener->keyboard->isKeyDown( OIS::KC_S ) )
    {
        camTranslate += Ogre::Vector3( 0, 0, 1);
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
    float playerRotation = 0.0f;
    if( base->frameListener->keyboard->isKeyDown( OIS::KC_UP ) )
    {
        playerTranslate += Ogre::Vector3( 0, 0, -1 );
        playerRotation   = 3.14f;
        playerWalked     = true;
    }
    if( base->frameListener->keyboard->isKeyDown( OIS::KC_DOWN ) )
    {
        playerTranslate += Ogre::Vector3( 0, 0, 1);
        playerRotation = 0.0f;
        playerWalked     = true;
    }
    if( base->frameListener->keyboard->isKeyDown( OIS::KC_LEFT ) )
    {
        playerTranslate += Ogre::Vector3( -1, 0, 0 );
        playerRotation = -1.57f;
        playerWalked     = true;
    }
    if( base->frameListener->keyboard->isKeyDown( OIS::KC_RIGHT ) )
    {
        playerTranslate += Ogre::Vector3( 1, 0, 0 );
        playerRotation = 1.57f;
        playerWalked     = true;
    }
    playerNode->translate( playerTranslate * 0.5f );
    playerNode->resetOrientation();
    playerNode->yaw( Ogre::Radian( playerRotation ) );
}

void DemoScene::updateMouse()
{
    base->frameListener->mouse->capture();

    float rotX = base->frameListener->mouse->getMouseState().X.rel * -0.01f;
    float rotY = base->frameListener->mouse->getMouseState().Y.rel * -0.01f;

    camera->yaw( Ogre::Radian( rotX ) );
    camera->pitch( Ogre::Radian( rotY ) );
}

void DemoScene::updateAnimations()
{
    if( playerWalked )
    {
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
    playerWalked = false;
}

}

#include "HelloWorldScene.h"
#include "GameMap.h"
#include "Tank.h"
#include "World.h"

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename)
{
    printf("Error while loading: %s\n", filename);
    printf(
        "Depending on how you compiled you might have to add 'Content/' in front of filenames in "
        "HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    // super init first
    if (!Scene::initWithPhysics())
    {
        return false;
    }

    // setup
    setupGame();

    // physics
    setupPhysics();

    // background
    setupBackground();

    // game layer
    gameLayer = Layer::create();
    addChild(gameLayer);

    // player
    setupPlayer();

    // ui
    // setupUI();
    // setupLevelUI();

    // touch
    setupControls();

    // foreground
    // setupForeground();

    // map
    setupMap();

    // camera
    setupCamera();

    // schedule update
    scheduleUpdate();

    return true;

    // map
    std::vector<std::vector<int>> mapData = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    };

    // create the map
    //    auto gameMap = GameMap::create("spritesheets/map.png", mapData);
    //    addChild(gameMap);

    // update
    // scheduleUpdate();

    /*
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", AX_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr || closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = safeOrigin.x + safeArea.size.width - closeItem->getContentSize().width / 2;
        float y = safeOrigin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // Some templates (uncomment what you  need)
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesBegan = AX_CALLBACK_2(HelloWorld::onTouchesBegan, this);
    touchListener->onTouchesMoved = AX_CALLBACK_2(HelloWorld::onTouchesMoved, this);
    touchListener->onTouchesEnded = AX_CALLBACK_2(HelloWorld::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    // auto mouseListener           = EventListenerMouse::create();
    // mouseListener->onMouseMove   = AX_CALLBACK_1(HelloWorld::onMouseMove, this);
    // mouseListener->onMouseUp     = AX_CALLBACK_1(HelloWorld::onMouseUp, this);
    // mouseListener->onMouseDown   = AX_CALLBACK_1(HelloWorld::onMouseDown, this);
    // mouseListener->onMouseScroll = AX_CALLBACK_1(HelloWorld::onMouseScroll, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    // auto keyboardListener           = EventListenerKeyboard::create();
    // keyboardListener->onKeyPressed  = AX_CALLBACK_2(HelloWorld::onKeyPressed, this);
    // keyboardListener->onKeyReleased = AX_CALLBACK_2(HelloWorld::onKeyReleased, this);
    //_eventDispatcher->addEventListenerWithFixedPriority(keyboardListener, 11);

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(
            Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png"sv);
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
        auto drawNode = DrawNode::create();
        drawNode->setPosition(Vec2(0, 0));
        addChild(drawNode);

        drawNode->drawRect(safeArea.origin + Vec2(1, 1), safeArea.origin + safeArea.size, Color4F::BLUE);
    }

    // scheduleUpdate() is required to ensure update(float) is called on every loop
    scheduleUpdate();
    */

    return true;
}

void HelloWorld::setupGame()
{
    // size and origin
    winSize = _director->getWinSize();
    visibleSize = _director->getVisibleSize();
    origin = _director->getVisibleOrigin();
    safeArea = _director->getSafeAreaRect();
    safeOrigin = safeArea.origin;

#if !defined(AX_TARGET_OS_TVOS)
    // visibleSize = safeArea.size;
    // origin = safeOrigin;
#endif

    // init random
    srand(static_cast<unsigned int>(time(nullptr)));
}

void HelloWorld::setupPhysics()
{
    // world
    getPhysicsWorld()->setGravity(Vec2(0, 0));
    // getPhysicsWorld()->setAutoStep(true);
    // getPhysicsWorld()->setUpdateRate(1.0f / 60);
    // getPhysicsWorld()->setFixedUpdateRate(60);

#if _AX_DEBUG
    getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif

    // contact
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = AX_CALLBACK_1(HelloWorld::onPhysicsContact, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool HelloWorld::onPhysicsContact(PhysicsContact &contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    if (nodeA && nodeB)
    {
        if (nodeA == player || nodeB == player)
        {
            player->getPhysicsBody()->setVelocity(Vec2::ZERO);
        }
    }

    return true;
};

void HelloWorld::setupBackground()
{
    // background
    // auto background = Sprite::create("Background.png");
    auto background = LayerColor::create(Color4B(64, 31, 7, 255));
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    float scale = std::max(visibleSize.width, visibleSize.height);
    background->setScale(scale);

    addChild(background);
}

void HelloWorld::setupPlayer()
{
    player = Tank::createTank("tanks");
    gameLayer->addChild(player, 100);
    player->setPosition(150, 150);
    player->setVelocity(400.0f);
}

void HelloWorld::setupCamera()
{
    gameCamera = Camera::create();
    gameCamera->setPosition3D(Vec3(0, 0, 900));
    gameCamera->lookAt(Vec3(0, 0, 0), Vec3(0, 1, 0));

#if defined(AX_TARGET_OS_TVOS)
    gameCamera->setZoom(1);
#else
    gameCamera->setZoom(2);
#endif

    gameLayer->addChild(gameCamera, 1000);
}

void HelloWorld::setupControls()
{
    Controller::startDiscoveryController();

    // add touch listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = AX_CALLBACK_2(HelloWorld::onKeyPressed, this);
    keyboardListener->onKeyReleased = AX_CALLBACK_2(HelloWorld::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // add controller listener
    auto controllerListener = EventListenerController::create();
    controllerListener->onKeyDown = AX_CALLBACK_3(HelloWorld::onControllerButtonDown, this);
    controllerListener->onKeyUp = AX_CALLBACK_3(HelloWorld::onControllerButtonUp, this);
    controllerListener->onAxisEvent = AX_CALLBACK_3(HelloWorld::onControllerAxis, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(controllerListener, this);
}

void HelloWorld::setupMap()
{
    // map
    // auto map = FastTMXTiledMap::create("maps/orthogonal-test1.tmx");
    auto map = FastTMXTiledMap::create("maps/map1/map.tmx");
    gameLayer->addChild(map, 0, 0);
    map->setScale(1.00f);

    // collision layer
    auto collisionLayer = map->getLayer("Collision Layer");

    if (collisionLayer)
    {
        collisionLayer->setVisible(false);

        for (int y = 0; y < collisionLayer->getLayerSize().height; y++)
        {
            for (int x = 0; x < collisionLayer->getLayerSize().width; x++)
            {
                auto tileSprite = collisionLayer->getTileAt(Vec2(x, y));

                if (tileSprite)
                {
                    auto physicsBody = PhysicsBody::createBox(tileSprite->getContentSize(), PhysicsMaterial(1.0f, 0.1f, 0.0f));
                    physicsBody->setDynamic(false);
                    physicsBody->setCategoryBitmask(0x02);
                    physicsBody->setCollisionBitmask(0x01);
                    physicsBody->setGravityEnable(false);
                    physicsBody->setRotationEnable(false);
                    tileSprite->setPhysicsBody(physicsBody);
                }
            }
        }
    }
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_W)
    {
        player->setMoveDirection(1);
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_S)
    {
        player->setMoveDirection(2);
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_A)
    {
        player->setRotateSide(1);
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_D)
    {
        player->setRotateSide(2);
    }
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_W)
    {
        player->stopMoving();
        player->stopRotatingSide();
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_S)
    {
        player->stopMoving();
        player->stopRotatingSide();
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_A)
    {
        player->stopMoving();
        player->stopRotatingSide();
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_D)
    {
        player->stopMoving();
        player->stopRotatingSide();
    }
}

void HelloWorld::onControllerButtonDown(Controller *controller, int keyCode, Event *event)
{
    if (keyCode == Controller::Key::BUTTON_DPAD_UP)
    {
        player->setMoveDirection(1);
    }
    else if (keyCode == Controller::Key::BUTTON_DPAD_DOWN)
    {
        player->setMoveDirection(2);
    }
    else if (keyCode == Controller::Key::BUTTON_DPAD_LEFT)
    {
        player->setRotateSide(1);
    }
    else if (keyCode == Controller::Key::BUTTON_DPAD_RIGHT)
    {
        player->setRotateSide(2);
    }
}

void HelloWorld::onControllerButtonUp(Controller *controller, int keyCode, Event *event)
{
    if (keyCode == Controller::Key::BUTTON_DPAD_UP)
    {
        player->stopMoving();
        player->stopRotatingSide();
    }
    else if (keyCode == Controller::Key::BUTTON_DPAD_DOWN)
    {
        player->stopMoving();
        player->stopRotatingSide();
    }
    else if (keyCode == Controller::Key::BUTTON_DPAD_LEFT)
    {
        player->stopMoving();
        player->stopRotatingSide();
    }
    else if (keyCode == Controller::Key::BUTTON_DPAD_RIGHT)
    {
        player->stopMoving();
        player->stopRotatingSide();
    }
}

void HelloWorld::onControllerAxis(Controller *controller, int keyCode, Event *event)
{
    if (keyCode == Controller::Key::JOYSTICK_LEFT_X || keyCode == Controller::Key::JOYSTICK_LEFT_Y)
    {
        float axisX = controller->getKeyStatus(Controller::Key::JOYSTICK_LEFT_X).value;
        float axisY = controller->getKeyStatus(Controller::Key::JOYSTICK_LEFT_Y).value;

        if (axisX > 0.5)
        {
            player->setRotateSide(2);
        }
        else if (axisX < -0.5)
        {
            player->setRotateSide(1);
        }
        else if (axisY > 0.5)
        {
            player->setMoveDirection(2);
        }
        else if (axisY < -0.5)
        {
            player->setMoveDirection(1);
        }
        else
        {
            player->stopMoving();
        }
    }
}

void HelloWorld::update(float delta)
{
    switch (gameState)
    {
    case GameState::init:
    {
        gameState = GameState::update;
        break;
    }

    case GameState::update:
    {
        /////////////////////////////
        // Add your codes below...like....
        //
        // UpdateJoyStick();
        // UpdatePlayer();
        // UpdatePhysics();
        // ...

        // player
        player->updateAll(delta);

        // camera
        Vec2 playerPosition = player->getPosition();
        Vec3 currentCameraPosition = gameCamera->getPosition3D();
        Vec3 targetCameraPosition = Vec3(playerPosition.x, playerPosition.y, currentCameraPosition.z);

        // Uso de interpolação linear para movimento suave da câmera
        float lerpFactor = 0.2f;
        Vec3 smoothedPosition = Vec3{
            currentCameraPosition.x + (targetCameraPosition.x - currentCameraPosition.x) * lerpFactor,
            currentCameraPosition.y + (targetCameraPosition.y - currentCameraPosition.y) * lerpFactor,
            currentCameraPosition.z,
        };

        gameCamera->setPosition3D(smoothedPosition);

        break;
    }

    case GameState::pause:
    {
        /////////////////////////////
        // Add your codes below...like....
        //
        // anyPauseStuff()

        break;
    }

    case GameState::menu1:
    { /////////////////////////////
        // Add your codes below...like....
        //
        // UpdateMenu1();
        break;
    }

    case GameState::menu2:
    { /////////////////////////////
        // Add your codes below...like....
        //
        // UpdateMenu2();
        break;
    }

    case GameState::end:
    { /////////////////////////////
        // Add your codes below...like....
        //
        // CleanUpMyCrap();
        menuCloseCallback(this);
        break;
    }

    } // switch
}

void HelloWorld::menuCloseCallback(Ref *sender)
{
    // Close the axmol game scene and quit the application
    _director->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use
     * _director->end() as given above,instead trigger a custom event created in RootViewController.mm
     * as below*/

    // EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

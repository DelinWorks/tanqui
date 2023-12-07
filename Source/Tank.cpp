#include "Tank.h"
#include "World.h"

Tank *Tank::createTank(const std::string &filename)
{
    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("spritesheets/" + filename + ".plist", "spritesheets/" + filename + ".png");

    auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("tankRed_outline.png");
    Tank *tank = static_cast<Tank *>(Tank::createWithSpriteFrame(spriteFrame));

    if (tank && spriteFrame)
    {
        auto physicsBody = PhysicsBody::createBox(tank->getContentSize(), PhysicsMaterial(1.0f, 0.1f, 1.0f));
        physicsBody->setDynamic(true);
        physicsBody->setMass(1.0f);
        physicsBody->setCategoryBitmask(0x01);
        physicsBody->setCollisionBitmask(0x02);
        physicsBody->setGravityEnable(false);
        physicsBody->setRotationEnable(false);
        tank->addComponent(physicsBody);

        tank->setVelocity(12);
        tank->setAnchorPoint(Vec2(0.5f, 0.5f));

        tank->autorelease();
        tank->retain();

        return tank;
    }

    AX_SAFE_DELETE(tank);

    return nullptr;
}

bool Tank::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    return true;
}

void Tank::updateAll(float dt)
{
    if (moveDirection == 1)
    {
        moveForward(dt);
    }
    else if (moveDirection == 2)
    {
        moveBackward(dt);
    }
    else if (rotateSide == 1)
    {
        rotate(getRotation() - 60 * dt);
    }
    else if (rotateSide == 2)
    {
        rotate(getRotation() + 60 * dt);
    }
}

void Tank::setVelocity(float velocity)
{
    this->velocity = velocity;
}

void Tank::rotate(float angle)
{
    if (angle > 360.0f)
    {
        angle -= 360.0f;
    }

    if (angle < 0.0f)
    {
        angle += 360.0f;
    }

    this->setRotation(angle);
}

void Tank::moveForward(float dt)
{
    float angleRadians = AX_DEGREES_TO_RADIANS(getRotation());
    Vec2 direction = Vec2(sin(angleRadians), cos(angleRadians));
    direction.normalize();
    this->getPhysicsBody()->setVelocity(direction * velocity);
}

void Tank::moveBackward(float dt)
{
    float angleRadians = AX_DEGREES_TO_RADIANS(getRotation());
    Vec2 direction = Vec2(sin(angleRadians), cos(angleRadians));
    direction.normalize();
    this->getPhysicsBody()->setVelocity(direction * -velocity);
}

void Tank::stopRotatingSide()
{
    rotateSide = 0;
}

void Tank::stopMoving()
{
    moveDirection = 0;
    rotateSide = 0;
    this->getPhysicsBody()->setVelocity(Vec2::ZERO);
}

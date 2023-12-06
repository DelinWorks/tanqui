#ifndef __TANK_H__
#define __TANK_H__

#include "axmol-ext.h"
#include "axmol.h"

USING_NS_AX;
USING_NS_AX_EXT;

class Tank : public Sprite
{
public:
    static Tank *createTank(const std::string &filename);

    virtual bool init() override;
    void updateAll(float dt);

    void setVelocity(float velocity);
    void rotate(float angle);
    void moveForward(float dt);
    void moveBackward(float dt);
    void stopRotatingSide();
    void stopMoving();

    void setRotateSide(int value)
    {
        rotateSide = value;
    }

    void setMoveDirection(int value)
    {
        moveDirection = value;
    }

private:
    float velocity;
    int rotateSide = 0;    // 0 = none, 1 = left, 2 = right
    int moveDirection = 0; // 0 = none, 1 = forward, 2 = backward

    Vec2 calculateForce(float dt, bool forward);
};

#endif // __TANK_H__

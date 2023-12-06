#ifndef __WORLD_H__
#define __WORLD_H__

#include "box2d/box2d.h"

constexpr const float PTM_RATIO = 32.f;

class World
{
public:
    static World &getInstance()
    {
        static World instance;
        return instance;
    }

    World(World const &) = delete;
    void operator=(World const &) = delete;

    b2World *world;

    void reset()
    {
        delete world;
        world = new b2World(gravity);
        world->SetAllowSleeping(true);
        world->SetContinuousPhysics(true);
    }

    ~World()
    {
        delete world;
    }

    b2World *getWorld() const
    {
        return world;
    }

    DrawNode *getDebugDrawNode() const
    {
        return debugDrawNode;
    }

private:
    b2Vec2 gravity;
    DrawNode *debugDrawNode;
    PhysicsDebugNodeBox2D debugNodeBox;

    World()
        : gravity(0.0f, -0.0f)
    {
        //        world = new b2World(gravity);
        //        world->SetAllowSleeping(true);
        //        world->SetContinuousPhysics(true);
        //        //world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
        //
        //        uint32 flags = 0;
        //        flags += 1 * b2Draw::e_shapeBit;
        //        flags += 1 * b2Draw::e_jointBit;
        //        flags += 0 * b2Draw::e_aabbBit;
        //        flags += 0 * b2Draw::e_centerOfMassBit;
        //
        //        debugNodeBox.SetFlags(flags);
        //        debugNodeBox.mRatio = PTM_RATIO;
        //        debugNodeBox.debugNodeOffset = {0, 0};
        //
        //        world->SetDebugDraw(&debugNodeBox);
        //
        //        debugDrawNode = debugNodeBox.GetDrawNode();
        // debugDrawNode->setOpacity(150);
    }
};

#endif

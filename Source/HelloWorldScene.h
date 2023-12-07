/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2021 Bytedance Inc.

 https://axmolengine.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "Tank.h"
#include "axmol.h"
USING_NS_AX;

class HelloWorld : public Scene
{
    enum class GameState
    {
        init = 0,
        update,
        pause,
        end,
        menu1,
        menu2,
    };

public:
    bool init() override;
    void update(float delta) override;

private:
    Vec2 winSize;
    Vec2 visibleSize;
    Vec2 origin;
    Rect safeArea;
    Vec2 safeOrigin;

    GameState gameState = GameState::init;

    Tank *player;

    Layer *gameLayer;
    Camera *gameCamera;

    void setupGame();
    void setupPhysics();
    void setupPlayer();
    void setupCamera();
    void setupBackground();
    void setupControls();
    void setupMap();
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
    void onControllerButtonDown(Controller *controller, int keyCode, Event *event);
    void onControllerButtonUp(Controller *controller, int keyCode, Event *event);
    void menuCloseCallback(Ref *sender);
    void onControllerAxis(Controller *controller, int keyCode, Event *event);
    bool onPhysicsContact(PhysicsContact &contact);
};

#endif // __HELLOWORLD_SCENE_H__

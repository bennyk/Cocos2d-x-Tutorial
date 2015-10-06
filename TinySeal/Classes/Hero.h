//
//  Hero.hpp
//  TinySeal
//
//  Created by Benny Khoo on 10/4/15.
//
//

#ifndef Hero_h
#define Hero_h

#include <stdio.h>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "App.h"

#define NUM_PREV_VELS   5

NS_APP_BEGIN

using namespace cocos2d;
class Hero : public Sprite {
public:
    Hero();
    Hero(b2World *world);
    virtual ~Hero();
    
public:
    static Hero* create();
    static Hero *createWithWorld(b2World *world);
    virtual bool init() override;
    
    bool isAwake() { return _awake; }
    void wake();
    void dive();
    void limitVelocity();
    
    void update();
    
    void nodive();
    void runForceAnimation();
    void runNormalAnimation();
    
private:
    void createBody();
    
private:
    bool _awake;
    
    b2World *_world;
    b2Body *_body;
    
    b2Vec2 _prevVels[NUM_PREV_VELS];
    int _nextVel;
    
    Animation *_normalAnim;
    Action *_normalAnimate;
};

NS_APP_END

#endif /* Hero_hpp */

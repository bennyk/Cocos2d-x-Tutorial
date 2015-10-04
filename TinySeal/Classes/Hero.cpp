//
//  Hero.cpp
//  TinySeal
//
//  Created by Benny Khoo on 10/4/15.
//
//

#include "Hero.h"

NS_APP_BEGIN

using namespace cocos2d;

Hero *Hero::create()
{
    Hero *node = new (std::nothrow) Hero();
    if (node)
    {
        node->init();
        node->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(node);
    }
    return node;
}

bool Hero::init()
{
    if (Sprite::initWithSpriteFrameName("seal1.png")) {
        
        this->createBody();
        return true;
    }
    
    return false;
}

void Hero::createBody()
{
    float radius = 16.0f;
    auto body = PhysicsBody::createCircle(radius, PhysicsMaterial {1.0f / CC_CONTENT_SCALE_FACTOR(), 0, -0.2f});
    body->setLinearDamping(.1f);
    body->setRotationEnable(false);
    this->setPhysicsBody(body);
    
    // set initial position
    Size winSize = Director::getInstance()->getWinSize();
    this->setPosition(Vec2 {0,  winSize.height / 2 + radius});
}

NS_APP_END
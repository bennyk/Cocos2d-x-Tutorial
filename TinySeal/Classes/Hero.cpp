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

Hero::Hero() : _awake {false}
{}

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

void Hero::wake()
{
    _awake = true;
    auto body = this->getPhysicsBody();
    body->setResting(false);
    body->applyImpulse(Vec2 {1, 2}, body->getPosition());
}

void Hero::dive()
{
    auto body = this->getPhysicsBody();
    body->applyImpulse(Vec2 {5, -50}, body->getPosition());

}

void Hero::limitVelocity()
{
    if (!_awake) return;
    
    const float minVelocityX = 5;
    const float minVelocityY = -40;
    
    auto body = this->getPhysicsBody();
    Vec2 vel = body->getVelocity();
    if (vel.x < minVelocityX) {
        vel.x = minVelocityX;
    }
    if (vel.y < minVelocityY) {
        vel.y = minVelocityY;
    }
    body->setVelocity(vel);

}

NS_APP_END
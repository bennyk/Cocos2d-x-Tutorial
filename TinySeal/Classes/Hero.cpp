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

Hero::Hero() : _awake {false}, _world {nullptr}
{}

Hero::Hero(b2World *world) : _awake {false}, _world {world}
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

Hero *Hero::createWithWorld(b2World *world)
{
    Hero *node = new (std::nothrow) Hero(world);
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
    Size winSize = Director::getInstance()->getWinSize();
    int screenH = winSize.height;
    
    Vec2 startPosition = Vec2 {0, screenH/2+radius};
    
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.linearDamping = 0.1f;
    bd.fixedRotation = true;
    bd.position.Set(startPosition.x/PTM_RATIO, startPosition.y/PTM_RATIO);
    _body = _world->CreateBody(&bd);
    
    b2CircleShape shape;
    shape.m_radius = radius/PTM_RATIO;
    
    b2FixtureDef fd;
    fd.shape = &shape;
    fd.density = 1.0f / CC_CONTENT_SCALE_FACTOR();
    fd.restitution = 0.0f;
    fd.friction = 0.2;
    
    _body->CreateFixture(&fd);
}

void Hero::wake()
{
    _awake = true;
    _body->SetActive(true);
    _body->ApplyLinearImpulse(b2Vec2(1,2), _body->GetPosition(), true);
}

void Hero::dive()
{
    _body->ApplyForce(b2Vec2(5,-50),_body->GetPosition(), true);

}

void Hero::limitVelocity()
{
    if (!_awake) return;
    
    const float minVelocityX = 5;
    const float minVelocityY = -40;
    b2Vec2 vel = _body->GetLinearVelocity();
    if (vel.x < minVelocityX) {
        vel.x = minVelocityX;
    }
    if (vel.y < minVelocityY) {
        vel.y = minVelocityY;
    }
    _body->SetLinearVelocity(vel);

}

void Hero::update()
{
    this->setPosition(Vec2 {static_cast<float>(_body->GetPosition().x*PTM_RATIO), static_cast<float>(_body->GetPosition().y*PTM_RATIO)});
    b2Vec2 vel = _body->GetLinearVelocity();
//    b2Vec2 weightedVel = vel;
    Vec2 v = Vec2 {vel.x, vel.y};
    float angle = v.getAngle();
    if (_awake) {
        this->setRotation(-1 * CC_RADIANS_TO_DEGREES(angle));
    }
}


NS_APP_END
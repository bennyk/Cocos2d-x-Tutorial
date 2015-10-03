//
//  Terrain.cpp
//  TinySeal
//
//  Created by Benny Khoo on 10/2/15.
//
//

#include "Terrain.h"


NS_APP_BEGIN

using namespace cocos2d;

Terrain::Terrain() {}

Terrain::~Terrain()
{
    if (_stripes != nullptr) {
        _stripes->release();
    }
}

Terrain *Terrain::create()
{
    Terrain *node = new (std::nothrow) Terrain();
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

bool Terrain::init()
{
    DrawNode::init();
    this->generateHills();
    return true;
}

void Terrain::generateHills()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    float minDX = 160;
    float minDY = 60;
    int rangeDX = 80;
    int rangeDY = 40;
    
    float x = -minDX;
    float y = winSize.height/2;
    
    float dy, ny;
    float sign = 1; // +1 - going up, -1 - going  down
    float paddingTop = 20;
    float paddingBottom = 20;
    
    for (int i=0; i<kMaxHillKeyPoints; i++) {
        _hillKeyPoints[i] = Vec2 {x, y};
        if (i == 0) {
            x = 0;
            y = winSize.height/2;
        } else {
            x += rand()%rangeDX+minDX;
            while(true) {
                dy = rand()%rangeDY+minDY;
                ny = y + dy*sign;
                if(ny < winSize.height-paddingTop && ny > paddingBottom) {
                    break;
                }
            }
            y = ny;
        }
        sign *= -1;
    }
    
    return;
}

void Terrain::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    DrawNode::clear();
    
    for(int i = 1; i < kMaxHillKeyPoints; ++i) {
        this->drawLine(_hillKeyPoints[i-1], _hillKeyPoints[i], Color4F {1.0, 1.0, 1.0, 1.0});
    }
    
    DrawNode::draw(renderer, transform, flags);
}

void Terrain::setOffsetX(float newOffsetX)
{
    _offsetX = newOffsetX;
    this->setPosition(-_offsetX* this->getScale(), 0);
}


NS_APP_END

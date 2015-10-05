//
//  Terrain.hpp
//  TinySeal
//
//  Created by Benny Khoo on 10/2/15.
//
//

#ifndef Terrain_h
#define Terrain_h

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GLES-Render.h"

#define kMaxHillKeyPoints 1000
#define kHillSegmentWidth 5

#define kMaxHillVertices 4000
#define kMaxBorderVertices 800

NS_APP_BEGIN

using namespace cocos2d;
class Terrain : public DrawNode
{
public:
    static Terrain* create();
    static Terrain* createWithWorld(b2World *world);
    
    Terrain();
    Terrain(b2World *world);
    virtual ~Terrain();
    
    virtual bool init() override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
public:
    void setOffsetX(float newOffsetX);
    
    void setStripes(Sprite *stripes) {
        stripes->retain();
        _stripes = stripes;
    }
    
private:
    void generateHills();
    void resetHillVertices();
    void resetPhysics();
    
private:
    int _offsetX;
    Vec2 _hillKeyPoints[kMaxHillKeyPoints];
    Sprite *_stripes;
    
    CustomCommand _customCommand;
    
    int _fromKeyPointI, _toKeyPointI;
    
    int _nHillVertices;
    Vec2 _hillVertices[kMaxHillVertices];
    Vec2 _hillTexCoords[kMaxHillVertices];
    int _nBorderVertices;
    Vec2 _borderVertices[kMaxBorderVertices];
    
    SpriteBatchNode *_batchNode;
    
    b2World *_world;
    b2Body *_body;
    GLESDebugDraw * _debugDraw;
};
    
NS_APP_END

#endif /* Terrain_h */

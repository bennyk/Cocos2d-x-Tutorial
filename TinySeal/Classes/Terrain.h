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

#define kMaxHillKeyPoints 1000
#define kHillSegmentWidth 10

NS_APP_BEGIN

using namespace cocos2d;
class Terrain : public DrawNode
{
public:
    static Terrain* create();
    
    Terrain();
    virtual ~Terrain();
    
    virtual bool init() override;
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
public:
    void setOffsetX(float newOffsetX);
    
    void setStripes(Sprite *stripes) {
        _stripes = stripes;
    }
    
private:
    void generateHills();
    void resetHillVertices();
    
private:
    int _offsetX;
    Vec2 _hillKeyPoints[kMaxHillKeyPoints];
    Sprite *_stripes;
    
    CustomCommand _customCommand;
    
    int _fromKeyPointI, _toKeyPointI;
};
    
NS_APP_END

#endif /* Terrain_h */

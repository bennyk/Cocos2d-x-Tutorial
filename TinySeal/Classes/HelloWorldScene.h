#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Terrain.h"
#include "Hero.h"

#include "Box2D/Box2D.h"

NS_APP_BEGIN

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    virtual void onEnter() override;
    virtual void update(float delta) override;
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    
private:
    Sprite *spriteWithColor(Color4F color, float texWidth, float texHeight);
    Sprite *spriteWithColor1(Color4F color1, Color4F color2, float texWidth, float texHeight, int nStripes);
    void createTestBodyAtPostition(Vec2 position);
    void setupWorld();
    
    Color4F randomBrightColor();
    void genBackground();
    
private:
    
    Sprite *_background;
    CustomCommand _customCommand;
    
    Terrain *_terrain;
    Hero *_hero;
    bool _tapDown;
    
    b2World * _world;
};

NS_APP_END

#endif // __HELLOWORLD_SCENE_H__

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Terrain.h"
#include "Hero.h"

NS_APP_BEGIN

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    virtual void onEnter();
    virtual void update(float delta);
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
private:
    Sprite *spriteWithColor(Color4F color, float texWidth, float texHeight);
    Sprite *spriteWithColor1(Color4F color1, Color4F color2, float texWidth, float texHeight, int nStripes);
    void createTestBodyAtPostition(Vec2 position);
    
    Color4F randomBrightColor();
    void genBackground();
    
private:
    
    Sprite *_background;
    CustomCommand _customCommand;
    
    Terrain *_terrain;
    Hero *_hero;
};

NS_APP_END

#endif // __HELLOWORLD_SCENE_H__

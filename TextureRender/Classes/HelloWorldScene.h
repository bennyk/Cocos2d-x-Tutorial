#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

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
    
    Color4F randomBrightColor();
    void genBackground();
    
private:
    
    Sprite *_background;
    CustomCommand _customCommand;
};

#endif // __HELLOWORLD_SCENE_H__

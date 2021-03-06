#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    /*
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
     */
    
//    this->genBackground();
    
    auto eventListener = EventListenerTouchOneByOne::create();
    eventListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
    
    return true;
}

Sprite *HelloWorld::spriteWithColor(Color4F color, float texWidth, float texHeight)
{
    RenderTexture *rt = RenderTexture::create(texWidth, texHeight);
    rt->beginWithClear(color.r, color.g, color.b, color.a);
    
    // 3: Draw into the texture
    // You'll add this later
    
    setGLProgramState(cocos2d::GLProgramState::getOrCreateWithGLProgramName(cocos2d::GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
    
    _customCommand.init(_globalZOrder);
    _customCommand.func = [texWidth, texHeight, this]() {
        float gradientAlpha = 0.7f;
        Vec2 vertices[4];
        Color4F colors[4];
        int nVertices = 0;
        
        vertices[nVertices] = Vec2 {0, 0};
        colors[nVertices++] = Color4F {0, 0, 0, 0 };
        vertices[nVertices] = Vec2 {texWidth, 0};
        colors[nVertices++] = Color4F {0, 0, 0, 0};
        vertices[nVertices] = Vec2 {0, texHeight};
        colors[nVertices++] = Color4F {0, 0, 0, gradientAlpha};
        vertices[nVertices] = Vec2 {texWidth, texHeight};
        colors[nVertices++] = Color4F {0, 0, 0, gradientAlpha};
        
        getGLProgram()->use();
        getGLProgram()->setUniformsForBuiltins();
        
        cocos2d::GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION | cocos2d::GL::VERTEX_ATTRIB_FLAG_COLOR);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
        glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, colors);
//        glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
        cocos2d::GL::blendFunc(CC_BLEND_SRC, CC_BLEND_DST);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);

    };
    
    auto renderer = Director::getInstance()->getRenderer();
    renderer->addCommand(&_customCommand);
    
    Sprite *noise = Sprite::create("Noise-iphone5hd.png");
    noise->setBlendFunc(BlendFunc {GL_DST_COLOR, GL_ZERO});
    noise->setPosition(texWidth/2, texHeight/2);
    noise->visit();
    
    rt->end();
    
    return Sprite::createWithTexture(rt->getSprite()->getTexture());
}

Sprite *HelloWorld::spriteWithColor1(Color4F color1, Color4F color2, float texWidth, float texHeight, int nStripes)
{
    RenderTexture *rt = RenderTexture::create(texWidth, texHeight);
    rt->beginWithClear(color1.r, color1.g, color1.b, color1.a);
    
    // 3: Draw into the texture
    // You'll add this later
    
    setGLProgramState(cocos2d::GLProgramState::getOrCreateWithGLProgramName(cocos2d::GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
    
    
    _customCommand.init(_globalZOrder);
    _customCommand.func = [texWidth, texHeight, nStripes, color2, this]() {
        Vec2 *vertices = new Vec2[6*nStripes];
        Color4F *colors = new Color4F[6*nStripes];
        
        int nVertices = 0;
        float x1 = -texHeight;
        float x2;
        float y1 = texHeight;
        float y2 = 0;
        float dx = texWidth / nStripes * 2;
        float stripeWidth = dx/2;
        for (int i=0; i<nStripes; i++) {
            x2 = x1 + texHeight;
            
            vertices[nVertices] = Vec2 {x1, y1};
            colors[nVertices++] = Color4F{color2.r, color2.g, color2.b, color2.a};
            
            vertices[nVertices] = Vec2 {x1+stripeWidth, y1};
            colors[nVertices++] = Color4F {color2.r, color2.g, color2.b, color2.a};
            
            vertices[nVertices] = Vec2 {x2, y2};
            colors[nVertices++] = Color4F {color2.r, color2.g, color2.b, color2.a};
            
            vertices[nVertices] = vertices[nVertices-2];
            colors[nVertices++] = Color4F {color2.r, color2.g, color2.b, color2.a};
            
            vertices[nVertices] = vertices[nVertices-2];
            colors[nVertices++] = Color4F {color2.r, color2.g, color2.b, color2.a};
            
            vertices[nVertices] = Vec2 {x2+stripeWidth, y2};
            colors[nVertices++] = Color4F {color2.r, color2.g, color2.b, color2.a};
            x1 += dx;
        }
        
        getGLProgram()->use();
        getGLProgram()->setUniformsForBuiltins();
        
        cocos2d::GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION | cocos2d::GL::VERTEX_ATTRIB_FLAG_COLOR);
        
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
        glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_TRUE, 0, colors);
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)nVertices);
        
        float gradientAlpha = 0.7f;
        nVertices = 0;
        
        vertices[nVertices] = Vec2 {0, 0};
        colors[nVertices++] = Color4F {0, 0, 0, 0 };
        vertices[nVertices] = Vec2 {texWidth, 0};
        colors[nVertices++] = Color4F {0, 0, 0, 0};
        vertices[nVertices] = Vec2 {0, texHeight};
        colors[nVertices++] = Color4F {0, 0, 0, gradientAlpha};
        vertices[nVertices] = Vec2 {texWidth, texHeight};
        colors[nVertices++] = Color4F {0, 0, 0, gradientAlpha};
        
        glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
        glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, colors);

//        glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
        cocos2d::GL::blendFunc(CC_BLEND_SRC, CC_BLEND_DST);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);
        
        
        // layer 3: top highlight
        float borderHeight = texHeight/16;
        float borderAlpha = 0.3f;
        nVertices = 0;
        
        vertices[nVertices] = Vec2 {0, 0};
        colors[nVertices++] = Color4F {1, 1, 1, borderAlpha};
        
        vertices[nVertices] = Vec2 {texWidth, 0};
        colors[nVertices++] = Color4F {1, 1, 1, borderAlpha};
        
        vertices[nVertices] = Vec2 {0, borderHeight};
        colors[nVertices++] = Color4F {0, 0, 0, 0};
        
        vertices[nVertices] = Vec2 {texWidth, borderHeight};
        colors[nVertices++] = Color4F {0, 0, 0, 0};
        
        glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
        glVertexAttribPointer(cocos2d::GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, colors);
        glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);
        
        CC_SAFE_DELETE_ARRAY(vertices);
        CC_SAFE_DELETE_ARRAY(colors);
        
    };
    
    auto renderer = Director::getInstance()->getRenderer();
    renderer->addCommand(&_customCommand);
    
    Sprite *noise = Sprite::create("Noise-iphone5hd.png");
    noise->setBlendFunc(BlendFunc {GL_DST_COLOR, GL_ZERO});
    noise->setPosition(texWidth/2, texHeight/2);
    noise->visit();
    
    rt->end();
    
    return Sprite::createWithTexture(rt->getSprite()->getTexture());

}

Color4F HelloWorld::randomBrightColor()
{
    while (true) {
        float requiredBrightness = 192;
        Color4B randomColor = Color4B(arc4random() % 255,
             arc4random() % 255,
             arc4random() % 255,
             255);
        if (randomColor.r > requiredBrightness ||
            randomColor.g > requiredBrightness ||
            randomColor.b > requiredBrightness) {
            return Color4F::Color4F(randomColor);
        }
    }

}

void HelloWorld::genBackground()
{
//    CCLOGINFO("scale factor %d", );
    
    if (_background != nullptr) {
        _background->removeFromParentAndCleanup(true);
    }
    
    Color4F bgColor = this->randomBrightColor();
    Size winSize = Director::getInstance()->getWinSize();
//    _background = this->spriteWithColor(bgColor, winSize.width, winSize.height);
    
    Color4F color2 = this->randomBrightColor();
    
    int nStripes = ((arc4random() % 4) + 1) * 2;
    _background = this->spriteWithColor1(bgColor, color2, 512, 512, nStripes);
    this->setScale(.5);
    
    _background->setPosition(Vec2(winSize.width/2, winSize.height/2));

    _background->getTexture()->setTexParameters(Texture2D::TexParams {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT});
    this->addChild(_background, -1);
    
//    _background->addChild(_background);
}

void HelloWorld::onEnter()
{
    Layer::onEnter();
    
    this->genBackground();
//    this->setTouchEnabled(true);
    
    this->scheduleUpdate();
}

void HelloWorld::update(float delta)
{
    float PIXELS_PER_SECOND = 100;
    static float offset = 0;
    offset += PIXELS_PER_SECOND * delta;
    
    Size textureSize = _background->getTextureRect().size;
    _background->setTextureRect(Rect {offset, 0, textureSize.width, textureSize.height});

}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    this->genBackground();
    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

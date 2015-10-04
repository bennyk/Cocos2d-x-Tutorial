//
//  Hero.hpp
//  TinySeal
//
//  Created by Benny Khoo on 10/4/15.
//
//

#ifndef Hero_h
#define Hero_h

#include <stdio.h>
#include "cocos2d.h"

NS_APP_BEGIN

using namespace cocos2d;
class Hero : public Sprite {
public:
    static Hero* create();
    virtual bool init() override;
    
private:
    void createBody();
};

NS_APP_END

#endif /* Hero_hpp */
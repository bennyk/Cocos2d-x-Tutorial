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

Terrain::Terrain()
: _offsetX {0}, _stripes {nullptr}, _fromKeyPointI {0}, _toKeyPointI {0} {}

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
    
    // we're going to use texture in this node.
    setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE));
    
    this->generateHills();
    this->resetHillVertices();
    
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

void Terrain::resetHillVertices()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    static int prevFromKeyPointI = -1;
    static int prevToKeyPointI = -1;
    
    // key points interval for drawing
    while (_hillKeyPoints[_fromKeyPointI+1].x < _offsetX-winSize.width/8/this->getScale()) {
        _fromKeyPointI++;
    }
    while (_hillKeyPoints[_toKeyPointI].x < _offsetX+winSize.width*12/8/this->getScale()) {
        _toKeyPointI++;
    }
    
    float minY = 0;
    if (winSize.height > 480) {
        minY = (1136 - 1024)/4;
    }
    if (prevFromKeyPointI != _fromKeyPointI || prevToKeyPointI != _toKeyPointI) {
        
        // vertices for visible area
        _nHillVertices = 0;
        _nBorderVertices = 0;
        Vec2 p0, p1, pt0, pt1;
        p0 = _hillKeyPoints[_fromKeyPointI];
        for (int i=_fromKeyPointI+1; i<_toKeyPointI+1; i++) {
            p1 = _hillKeyPoints[i];
            
            // triangle strip between p0 and p1
            int hSegments = floorf((p1.x-p0.x)/kHillSegmentWidth);
            float dx = (p1.x - p0.x) / hSegments;
            float da = M_PI / hSegments;
            float ymid = (p0.y + p1.y) / 2;
            float ampl = (p0.y - p1.y) / 2;
            pt0 = p0;
            _borderVertices[_nBorderVertices++] = pt0;
            for (int j=1; j<hSegments+1; j++) {
                pt1.x = p0.x + j*dx;
                pt1.y = ymid + ampl * cosf(da*j);
                _borderVertices[_nBorderVertices++] = pt1;
                
                _hillVertices[_nHillVertices] = Vec2(pt0.x, 0 + minY);
                _hillTexCoords[_nHillVertices++] = Vec2(pt0.x/512, 1.0f);
                _hillVertices[_nHillVertices] = Vec2(pt1.x, 0 + minY);
                _hillTexCoords[_nHillVertices++] = Vec2(pt1.x/512, 1.0f);
                
                _hillVertices[_nHillVertices] = Vec2(pt0.x, pt0.y);
                _hillTexCoords[_nHillVertices++] = Vec2(pt0.x/512, 0);
                _hillVertices[_nHillVertices] = Vec2(pt1.x, pt1.y);
                _hillTexCoords[_nHillVertices++] = Vec2(pt1.x/512, 0);
                
                pt0 = pt1;
            }
            
            p0 = p1;
        }
        
        prevFromKeyPointI = _fromKeyPointI;
        prevToKeyPointI = _toKeyPointI;        
    }

}

void Terrain::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    DrawNode::clear();
    
    _customCommand.init(_globalZOrder);
    _customCommand.func = [this, transform]() {
        
        auto glProgram = getGLProgram();
        glProgram->use();
        glProgram->setUniformsForBuiltins(transform);
        
        GL::bindTexture2D(_stripes->getTexture()->getName());
        GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
        
//    ccDrawColor4F(1.0f, 1.0f, 1.0f, 1.0f);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, _hillVertices);
        glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, _hillTexCoords);
        
        glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)_nHillVertices);
        
    };
    renderer->addCommand(&_customCommand);
    
    for(int i = MAX(_fromKeyPointI, 1); i <= _toKeyPointI; ++i) {
        this->drawLine(_hillKeyPoints[i-1], _hillKeyPoints[i], Color4F {1.0, 0.0, 0.0, 1.0});
        
        Vec2 p0 = _hillKeyPoints[i-1];
        Vec2 p1 = _hillKeyPoints[i];
        int hSegments = floorf((p1.x-p0.x)/kHillSegmentWidth);
        float dx = (p1.x - p0.x) / hSegments;
        float da = M_PI / hSegments;
        float ymid = (p0.y + p1.y) / 2;
        float ampl = (p0.y - p1.y) / 2;
        
        Vec2 pt0, pt1;
        pt0 = p0;
        for (int j = 0; j < hSegments+1; ++j) {
            
            pt1.x = p0.x + j*dx;
            pt1.y = ymid + ampl * cosf(da*j);
            
            this->drawLine(pt0, pt1, Color4F {1.0, 1.0, 1.0, 1.0});
            pt0 = pt1;
        }
    }
    
    DrawNode::draw(renderer, transform, flags);
}

void Terrain::setOffsetX(float newOffsetX)
{
    _offsetX = newOffsetX;
    this->setPosition(-_offsetX* this->getScale(), 0);
    this->resetHillVertices();
}


NS_APP_END

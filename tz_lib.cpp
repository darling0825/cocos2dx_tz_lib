/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013      佐耳云儿.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "tz_lib.h"

NS_TZ_BEGIN

// TouchSprite
// ------------------------------------------------------------------------
TouchSprite::TouchSprite()
:_touchListener(nullptr),
_swallowsTouches(false),
_touchEnabled(false) {
	setTouchEnabled(true);
}

TouchSprite::~TouchSprite() {
	_eventDispatcher->removeEventListener(_touchListener);
}

TouchSprite* TouchSprite::create(const std::string& filename) {
	TouchSprite *sprite = new TouchSprite();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}
TouchSprite* TouchSprite::create(const std::string& filename,const Rect& rect) {
	TouchSprite *sprite = new TouchSprite();
	if (sprite && sprite->initWithFile(filename, rect))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}
TouchSprite* TouchSprite::createWithTexture(Texture2D *texture) {
	TouchSprite *sprite = new TouchSprite();
	if (sprite && sprite->initWithTexture(texture))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}
TouchSprite* TouchSprite::createWithTexture(Texture2D *texture,const Rect& rect) {
	TouchSprite *sprite = new TouchSprite();
	if (sprite && sprite->initWithTexture(texture, rect))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}
TouchSprite* TouchSprite::createWithSpriteFrame(SpriteFrame *spriteFrame) {
	TouchSprite *sprite = new TouchSprite();
	if (spriteFrame && sprite && sprite->initWithSpriteFrame(spriteFrame)) {
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}
TouchSprite* TouchSprite::createWithSpriteFrameName(const std::string& spriteFrameName) {
	SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
#if COCOS2D_DEBUG > 0
	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName.c_str());
	CCASSERT(frame != NULL, msg);
#endif
	return createWithSpriteFrame(frame);
}

void TouchSprite::setCallBack(const function<void()>& call_fun) {
	_call_fun = call_fun;
}

void TouchSprite::setTouchEnabled(bool enabled) {
	if (_touchEnabled != enabled) {
		_touchEnabled = enabled;
		if (enabled) {
			if (_touchListener != nullptr)
				return;

			auto listener = EventListenerTouchOneByOne::create();
			listener->setSwallowTouches(_swallowsTouches);

			listener->onTouchBegan = 
				CC_CALLBACK_2(TouchSprite::onTouchBegan, this);
			listener->onTouchEnded = 
				CC_CALLBACK_2(TouchSprite::onTouchEnded, this);

			_eventDispatcher->
				addEventListenerWithSceneGraphPriority(listener, this);
			_touchListener = listener;
		} else {
			_eventDispatcher->removeEventListener(_touchListener);
			_touchListener = nullptr;
		}
	}
}

void TouchSprite::setSwallowsTouches(bool swallowsTouches) {
	if (_swallowsTouches != swallowsTouches) {
		_swallowsTouches = swallowsTouches;
		if ( _touchEnabled) {
			setTouchEnabled(false);
			setTouchEnabled(true);
		}
	}
}

bool TouchSprite::onTouchBegan(Touch* touch, Event*) {
	_touch = SpriteTouch(touch);
	return true;
}
void TouchSprite::onTouchEnded(Touch* touch, Event*) {
	if (_touch && SpriteTouch(touch)) {
		if (_call_fun) {
			_call_fun();
		}
	}
}

bool TouchSprite::SpriteTouch(Touch *touch) {
	Point touchLocation = touch->getLocation();

	if (isVisible() && _touchEnabled) {
		Point local = convertToNodeSpace(touchLocation);
		Rect r = this->rect();
		r.origin = Point::ZERO;

		if (r.containsPoint(local))
		{
			return true;
		}
	}
	return false;
}

Rect TouchSprite::rect() const {
	return Rect( _position.x - _contentSize.width * _anchorPoint.x,
		_position.y - _contentSize.height * _anchorPoint.y,
		_contentSize.width, _contentSize.height);
}
// ------------------------------------------------------------------------

NS_TZ_END

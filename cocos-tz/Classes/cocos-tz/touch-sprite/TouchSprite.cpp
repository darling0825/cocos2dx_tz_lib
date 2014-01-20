#include "TouchSprite.h"

USING_NS_CC;
using namespace std;

NS_TZ_BEGIN

TouchSprite::TouchSprite()
	:_touchListener(nullptr),
	_swallowsTouches(false),
	_touchEnabled(false)
{

}

TouchSprite::~TouchSprite()
{

}

void TouchSprite::onExit()
{
	_eventDispatcher->removeEventListener(_touchListener);
	_touchListener = nullptr;
	Node::onExit();
}

void TouchSprite::onEnter()
{
	Sprite::onEnter();
	setTouchEnabled(true);
}

TouchSprite* TouchSprite::create(const string& filename)
{
	TouchSprite *sprite = new TouchSprite();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

TouchSprite* TouchSprite::create(const string& filename,const Rect& rect)
{
	TouchSprite *sprite = new TouchSprite();
	if (sprite && sprite->initWithFile(filename, rect))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

TouchSprite* TouchSprite::createWithTexture(Texture2D *texture)
{
	TouchSprite *sprite = new TouchSprite();
	if (sprite && sprite->initWithTexture(texture))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}
TouchSprite* TouchSprite::createWithTexture(Texture2D *texture,const Rect& rect)
{
	TouchSprite *sprite = new TouchSprite();
	if (sprite && sprite->initWithTexture(texture, rect))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}
TouchSprite* TouchSprite::createWithSpriteFrame(SpriteFrame *spriteFrame)
{
	TouchSprite *sprite = new TouchSprite();
	if (spriteFrame && sprite && sprite->initWithSpriteFrame(spriteFrame))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}
TouchSprite* TouchSprite::createWithSpriteFrameName(const char* spriteFrameName)
{
	SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
#if COCOS2D_DEBUG > 0
	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", spriteFrameName);
	CCASSERT(frame != NULL, msg);
#endif
	return createWithSpriteFrame(frame);
}

void TouchSprite::setCallback(const function<void(Object*)>& call_fun)
{
	_call_fun = call_fun;
}

void TouchSprite::setTouchEnabled(bool enabled)
{
	if (_touchEnabled != enabled)
	{
		_touchEnabled = enabled;
		if (enabled)
		{
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
		}
		else
		{
			_eventDispatcher->removeEventListener(_touchListener);
			_touchListener = nullptr;
		}
	}
}

void TouchSprite::setSwallowsTouches(bool swallowsTouches)
{
	if (_swallowsTouches != swallowsTouches)
	{
		_swallowsTouches = swallowsTouches;
		if ( _touchEnabled)
		{
			setTouchEnabled(false);
			setTouchEnabled(true);
		}
	}
}

bool TouchSprite::onTouchBegan(Touch* touch, Event*)
{
	_touch = SpriteTouch(touch);
	return _touch;
}
void TouchSprite::onTouchEnded(Touch* touch, Event*)
{
	if (_touch && SpriteTouch(touch))
	{
		if (_call_fun)
		{
			_call_fun(this);
		}
	}
}

bool TouchSprite::SpriteTouch(Touch *touch)
{
	Point touchLocation = touch->getLocation();

	if (isVisible() && _touchEnabled)
	{
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

Rect TouchSprite::rect() const
{
	return Rect( _position.x - _contentSize.width * _anchorPoint.x,
		_position.y - _contentSize.height * _anchorPoint.y,
		_contentSize.width, _contentSize.height);
}
NS_TZ_END
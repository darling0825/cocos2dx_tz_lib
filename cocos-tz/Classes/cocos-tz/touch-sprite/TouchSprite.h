#pragma once

#include "cocos2d.h"
#include "../config.h"

NS_TZ_BEGIN

class TouchSprite :public cocos2d::Sprite {
public:
	TouchSprite();
	virtual ~TouchSprite();

	static TouchSprite* create(const std::string& filename);
	static TouchSprite* create(const std::string& filename,const cocos2d::Rect& rect);
	static TouchSprite* createWithTexture(cocos2d::Texture2D *texture);
	static TouchSprite* createWithTexture(cocos2d::Texture2D *texture,const cocos2d::Rect& rect);
	static TouchSprite* createWithSpriteFrame(cocos2d::SpriteFrame *pSpriteFrame);
	static TouchSprite* createWithSpriteFrameName(const char* spriteFrameName);

	void setCallback(const std::function<void(cocos2d::Object*)>& call_fun);
	void setSwallowsTouches(bool swallowsTouches);
	void setTouchEnabled(bool enabled);
	bool isTouchEnabled() const { return _touchEnabled; }
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event*);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event*);
	cocos2d::Rect rect() const;
	CREATE_FUNC(TouchSprite);
private:
	virtual void onEnter();
	virtual void onExit();
	bool SpriteTouch(cocos2d::Touch *touch);
	cocos2d::EventListener* _touchListener;
	bool _swallowsTouches;
	bool _touchEnabled;
	std::function<void(cocos2d::Object*)> _call_fun;
	bool _touch;
};
NS_TZ_END
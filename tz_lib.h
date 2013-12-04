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

#pragma once
#ifndef _TZ_LIB_H_
#define _TZ_LIB_H_

#include "cocos2d.h"

#define NS_TZ_BEGIN namespace tz {
#define NS_TZ_END }

NS_TZ_BEGIN

using namespace std;
using namespace cocos2d;

// string
inline int atoi(const string& str) {
	return atoi(str.c_str());
}
inline string itoa(int _int) {
	string str;
	stringstream _str;
	_str<<_int;
	_str>>str;
	return str;
}
#define  c_itoa(_NUM_) toString(_NUM_).c_str()

// make_ttf
inline LabelTTF* make_ttf(const string& str) {
	return LabelTTF::create(str,"Arial",24);
}
inline LabelTTF* make_ttf(const string& str,int num) {
	return LabelTTF::create(str,"Arial",num);
}
inline LabelTTF* make_ttf(const string& str,const string& name) {
	return LabelTTF::create(str,name,24);
}
inline LabelTTF* make_ttf(const string& str,const string& name,int num) {
	return LabelTTF::create(str,name,num);
}

// make_sprite
inline Sprite* make_sprite(const string& path) {
	auto sprite = Sprite::create(path + ".png");
	return sprite;
}
inline Sprite* make_sprite(const string& path,const Point& point) {
	auto sprite = make_sprite(path);
	sprite->setPosition(point);
	return sprite;
}
inline Sprite* make_sprite(const string& path,Node* parent) {
	auto sprite = make_sprite(path);
	parent->addChild(sprite);
	return sprite;
}
inline Sprite* make_sprite(const string& path,
						   const Point& point,Node* parent) {
	auto sprite = make_sprite(path);
	sprite->setPosition(point);
	parent->addChild(sprite);
	return sprite;
}

// make_item
inline MenuItemImage* make_item(const string& path) {
	auto item = MenuItemImage::create(
		path + "_1" + ".png",path + "_2" + ".png");
	return item;
}
inline MenuItemImage* make_item(const string& path,
								function<void(Object*)> call_fun) {
	auto item = MenuItemImage::create(
		path + "_1" + ".png",path + "_2" + ".png",call_fun);
	return item;
}

// 
#define CREATE_FUNC_ADD(__TYPE__) \
	CREATE_FUNC(__TYPE__) \
	static __TYPE__* createAdd(Node* node) \
{ \
	__TYPE__ *pRet = new __TYPE__(); \
	if (pRet && pRet->init()) \
{ \
	pRet->autorelease(); \
	node->addChild(pRet); \
	return pRet; \
} \
	else \
{ \
	delete pRet; \
	pRet = NULL; \
	return NULL; \
} \
}

// TouchSprite
// ------------------------------------------------------------------------
class TouchSprite :public Sprite {
public:
	TouchSprite();
	virtual ~TouchSprite();

	static TouchSprite* create(const std::string& filename);
	static TouchSprite* create(const std::string& filename,const Rect& rect);
	static TouchSprite* createWithTexture(Texture2D *texture);
	static TouchSprite* createWithTexture(Texture2D *texture,const Rect& rect);
	static TouchSprite* createWithSpriteFrame(SpriteFrame *pSpriteFrame);
	static TouchSprite* createWithSpriteFrameName(const std::string& spriteFrameName);

	void setCallBack(const function<void()>& call_fun);
	void setSwallowsTouches(bool swallowsTouches);
	void setTouchEnabled(bool enabled);
	bool isTouchEnabled() const { return _touchEnabled; }
	bool onTouchBegan(Touch* touch, Event*);
	void onTouchEnded(Touch* touch, Event*);
	Rect rect() const;
	CREATE_FUNC(TouchSprite);
private:
	bool SpriteTouch(Touch *touch);
	EventListener* _touchListener;
	bool _swallowsTouches;
	bool _touchEnabled;
	function<void()> _call_fun;
	bool _touch;
};

// make_touch_sprite
inline TouchSprite* make_touch_sprite(const string& path) {
	auto sprite = TouchSprite::create(path + ".png");
	return sprite;
}
inline TouchSprite* make_touch_sprite(const string& path,const Point& point) {
	auto sprite = make_touch_sprite(path);
	sprite->setPosition(point);
	return sprite;
}
inline TouchSprite* make_touch_sprite(const string& path,Node* parent) {
	auto sprite = make_touch_sprite(path);
	parent->addChild(sprite);
	return sprite;
}
inline TouchSprite* make_touch_sprite(const string& path,const Point& point,Node* parent) {
	auto sprite = make_touch_sprite(path);
	sprite->setPosition(point);
	parent->addChild(sprite);
	return sprite;
}
inline TouchSprite* make_touch_sprite(const string& path,const function<void()>& call_fun) {
	auto sprite = TouchSprite::create(path + ".png");
	sprite->setCallBack(call_fun);
	return sprite;
}
inline TouchSprite* make_touch_sprite(const string& path,const Point& point,const function<void()>& call_fun) {
	auto sprite = make_touch_sprite(path,call_fun);
	sprite->setPosition(point);
	return sprite;
}
inline TouchSprite* make_touch_sprite(const string& path,Node* parent,const function<void()>& call_fun) {
	auto sprite = make_touch_sprite(path,call_fun);
	parent->addChild(sprite);
	return sprite;
}
inline TouchSprite* make_touch_sprite(const string& path,const Point& point,Node* parent,const function<void()>& call_fun) {
	auto sprite = make_touch_sprite(path,call_fun);
	sprite->setPosition(point);
	parent->addChild(sprite);
	return sprite;
}
// ------------------------------------------------------------------------
NS_TZ_END
#endif
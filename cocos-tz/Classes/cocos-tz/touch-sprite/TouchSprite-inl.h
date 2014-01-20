#include "TouchSprite.h"

NS_TZ_BEGIN

inline TouchSprite* make_touch_sprite(const std::string& path) {
		auto sprite = TouchSprite::create(path + ".png");
		return sprite;
}

inline TouchSprite* make_touch_sprite(
	const std::string& path,const cocos2d::Point& point) {
		auto sprite = make_touch_sprite(path);
		sprite->setPosition(point);
		return sprite;
}

inline TouchSprite* make_touch_sprite(const std::string& path,cocos2d::Node* parent) {
	auto sprite = make_touch_sprite(path);
	parent->addChild(sprite);
	return sprite;
}

inline TouchSprite* make_touch_sprite(
	const std::string& path,const cocos2d::Point& point,cocos2d::Node* parent) {
		auto sprite = make_touch_sprite(path);
		sprite->setPosition(point);
		parent->addChild(sprite);
		return sprite;
}

inline TouchSprite* make_touch_sprite(
	const std::string& path,const std::function<void(cocos2d::Object*)>& call_fun) {
		auto sprite = TouchSprite::create(path + ".png");
		sprite->setCallback(call_fun);
		return sprite;
}

inline TouchSprite* make_touch_sprite(
	const std::string& path,const cocos2d::Point& point,const std::function<void(cocos2d::Object*)>& call_fun) {
		auto sprite = make_touch_sprite(path,call_fun);
		sprite->setPosition(point);
		return sprite;
}

inline TouchSprite* make_touch_sprite(
	const std::string& path,cocos2d::Node* parent,const std::function<void(cocos2d::Object*)>& call_fun) {
		auto sprite = make_touch_sprite(path,call_fun);
		parent->addChild(sprite);
		return sprite;
}

inline TouchSprite* make_touch_sprite(
	const std::string& path,const cocos2d::Point& point,
	cocos2d::Node* parent,const std::function<void(cocos2d::Object*)>& call_fun) {
		auto sprite = make_touch_sprite(path,call_fun);
		sprite->setPosition(point);
		parent->addChild(sprite);
		return sprite;
}
NS_TZ_END
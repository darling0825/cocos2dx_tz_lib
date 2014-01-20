#pragma once

#include "cocos2d.h"
#include "../config.h"

inline cocos2d::Sprite* make_sprite(const std::string& path)
{
	auto sprite = cocos2d::Sprite::create(path + ".png");
	return sprite;
}

inline cocos2d::Sprite* make_sprite(const std::string& path,const cocos2d::Point& point)
{
	auto sprite = make_sprite(path);
	sprite->setPosition(point);
	return sprite;
}

inline cocos2d::Sprite* make_sprite(const std::string& path,cocos2d::Node* parent)
{
	auto sprite = make_sprite(path);
	parent->addChild(sprite);
	return sprite;
}

inline cocos2d::Sprite* make_sprite(const std::string& path,
									const cocos2d::Point& point,cocos2d::Node* parent)
{
		auto sprite = make_sprite(path);
		sprite->setPosition(point);
		parent->addChild(sprite);
		return sprite;
}

inline void sprite_change_imge(cocos2d::Sprite* sprite,const std::string& str)
{
	auto frame = cocos2d::Director::getInstance()->getTextureCache()->addImage(str);
	sprite->setTexture(frame);
}
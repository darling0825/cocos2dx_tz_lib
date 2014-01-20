#pragma once

#include "cocos2d.h"
#include "../config.h"

NS_TZ_BEGIN

inline cocos2d::Animate* make_animate(const std::string& name,int num,float time)
{
	auto animation = cocos2d::Animation::create();
	for (int i = 1;i <= num;++i)
	{
		auto str = name + itoa(i) +".png";
		animation->addSpriteFrameWithFile(str);
	}
	animation->setDelayPerUnit(time/num);
	animation->setRestoreOriginalFrame(true);
	auto animate = cocos2d::Animate::create(animation);
	return animate;
}

inline cocos2d::Sprite* make_animateSprite(const std::string& name,int num,float time)
{
	auto animate = make_animate(name,num,time);
	auto sprite = cocos2d::Sprite::create(name + itoa(1) +".png");
	sprite->runAction(cocos2d::RepeatForever::create(animate));
	return sprite;
}

NS_TZ_END
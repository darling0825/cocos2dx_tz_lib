#pragma once

#include "cocos2d.h"
#include "../config.h"

NS_TZ_BEGIN

inline cocos2d::LabelTTF* make_ttf(const std::string& str)
{
		return cocos2d::LabelTTF::create(str,"Arial",24);
}

inline cocos2d::LabelTTF* make_ttf(const std::string& str,float fontSize)
{
	return cocos2d::LabelTTF::create(str,"Arial",fontSize);
}

inline cocos2d::LabelTTF* make_ttf(const std::string& str,const std::string& fontName)
{
	return cocos2d::LabelTTF::create(str,fontName,24);
}

inline cocos2d::LabelTTF* make_ttf(const std::string& str,
						  const std::string& fontName,float fontSize)
{
		return cocos2d::LabelTTF::create(str,fontName,fontSize);
}

NS_TZ_END
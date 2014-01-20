#pragma once

#include "cocos2d.h"
#include "../config.h"

NS_TZ_BEGIN

inline cocos2d::MenuItemImage*
	make_item(const std::string& path)
{
		auto item = cocos2d::MenuItemImage::create(
			path + "1.png",path + "2.png");
		return item;
}

inline cocos2d::MenuItemImage*
	make_item(const std::string& path,
	std::function<void(cocos2d::Object*)> call_fun)
{
		auto item = cocos2d::MenuItemImage::create(
			path + "1.png",path + "2.png",call_fun);
		return item;
}

inline cocos2d::Menu* 
	make_menu_item(const std::string& path,
	std::function<void(cocos2d::Object*)> call_fun)
{
	auto item = make_item(path,call_fun);
	auto menu = cocos2d::Menu::create(item,nullptr);
	return menu;
}

NS_TZ_END
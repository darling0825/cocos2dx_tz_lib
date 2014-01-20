#include "test.h"
#include "cocos-tz/cocos-tz.h"

USING_NS_CC;

bool Test::init() {
	if (!Scene::init()) {
		return false;
	}
	auto str = tz::json_file_int("tips.json",9001,"id");
	log("%d",str);
	//JsonFileManagement::getInstance()->erease("tips.json");
	auto xx = tz::JsonFileManagement::getInstance()->getDocument("tips.json")[1]["id"].GetInt();
	auto xxx = tz::json_file_document("tips.json")[1]["id"].GetInt();
	return true;
}
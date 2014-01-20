#pragma once

#include "JsonFileManagement.h"

NS_TZ_BEGIN

inline std::string json_file_string(const std::string fileName,int id,const std::string& key)
{
	auto jsonMg = JsonFileManagement::getInstance();
	const auto& document = jsonMg->getDocument(fileName);
	const auto& mapId = jsonMg->getMapId(fileName);
	auto iter = mapId.find(id);
	CC_ASSERT(iter != mapId.end());
	return document[iter->second][key.c_str()].GetString();
}

inline int json_file_int(const std::string fileName,int id,const std::string& key)
{
	auto jsonMg = JsonFileManagement::getInstance();
	const auto& document = jsonMg->getDocument(fileName);
	const auto& mapId = jsonMg->getMapId(fileName);
	auto iter = mapId.find(id);
	CC_ASSERT(iter != mapId.end());
	return document[iter->second][key.c_str()].GetInt();
}

inline double json_file_double(const std::string fileName,int id,const std::string& key)
{
	auto jsonMg = JsonFileManagement::getInstance();
	const auto& document = jsonMg->getDocument(fileName);
	const auto& mapId = jsonMg->getMapId(fileName);
	auto iter = mapId.find(id);
	CC_ASSERT(iter != mapId.end());
	return document[iter->second][key.c_str()].GetDouble();
}

inline bool json_file_bool(const std::string fileName,int id,const std::string& key)
{
	auto jsonMg = JsonFileManagement::getInstance();
	const auto& document = jsonMg->getDocument(fileName);
	const auto& mapId = jsonMg->getMapId(fileName);
	auto iter = mapId.find(id);
	CC_ASSERT(iter != mapId.end());
	return document[iter->second][key.c_str()].GetBool();
}

inline const rapidjson::Document& json_file_document(const std::string fileName)
{
	return JsonFileManagement::getInstance()->getDocument(fileName);
}
NS_TZ_END
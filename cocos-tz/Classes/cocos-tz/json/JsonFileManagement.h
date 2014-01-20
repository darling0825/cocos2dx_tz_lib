#pragma once

#include "cocos2d.h"
#include "external/json/document.h"
#include "external/json/prettywriter.h"
#include "external/json/filestream.h"
#include "external/json/stringbuffer.h"
#include "../config.h"

NS_TZ_BEGIN

class JsonFileManagement
{
	typedef std::shared_ptr<rapidjson::Document> PtrDoc;
	typedef std::unordered_map<std::string,PtrDoc> MapDocument;

	typedef int Id;
	typedef std::map<Id,rapidjson::SizeType> MapId;
	typedef std::unordered_map<std::string,MapId> FileMapId;

public:
	static JsonFileManagement* getInstance();
	static void destroyInstance();

	void erease(const std::string& fileName);
	void clear();

	const rapidjson::Document& getDocument(const std::string& fileName);

	const MapId& getMapId(const std::string& fileName);

protected:

private:
	JsonFileManagement(){}
	~JsonFileManagement(){}

	static JsonFileManagement* _this;

	MapDocument _mapDocument;
	FileMapId _fileMapId;
};
NS_TZ_END
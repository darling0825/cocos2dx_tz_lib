#include "JsonFileManagement.h"

USING_NS_CC;
using namespace std;
using namespace rapidjson;

NS_TZ_BEGIN

JsonFileManagement* JsonFileManagement::_this = nullptr;

JsonFileManagement* JsonFileManagement::getInstance() 
{
	if (_this == nullptr) {
		_this = new JsonFileManagement;
	}
	return _this;
}

void JsonFileManagement::destroyInstance() 
{
	delete _this;
	_this = nullptr;
}

void JsonFileManagement::erease(const std::string& fileName)
{
	_mapDocument.erase(fileName);
	_fileMapId.erase(fileName);
}

void JsonFileManagement::clear()
{
	_mapDocument.clear();
	_fileMapId.clear();
}

const Document& JsonFileManagement::getDocument(const string& fileName) 
{
	auto iter = _mapDocument.find(fileName);
	if (iter == _mapDocument.end()) 
	{
		auto fileUtils = FileUtils::getInstance();
		auto pathFileName = fileUtils->fullPathForFilename(fileName);
		auto jsonStr = fileUtils->getStringFromFile(pathFileName);
		auto document = shared_ptr<Document>(new Document);
		document->Parse<0>(jsonStr.c_str());
		CC_ASSERT(!document->HasParseError());
		_mapDocument.insert(make_pair(fileName,document));
		return *document;
	}
	return *iter->second;
}

auto JsonFileManagement::getMapId(const string& fileName)->const MapId&
{
	auto iter = _fileMapId.find(fileName);
	if (iter == _fileMapId.end())
	{
		auto& mapId = _fileMapId.insert(make_pair(fileName,MapId())).first->second;
		auto& document = getDocument(fileName);
		for (SizeType i = 0; i < document.Size(); i++)
		{
			auto id = document[i]["id"].GetInt();
			auto idIter = mapId.find(id);
			CC_ASSERT(idIter == mapId.end());
			mapId.insert(make_pair(id,i));
		}
		return mapId;
	}
	return iter->second;
}
NS_TZ_END
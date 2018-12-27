#include "LocalizationManager.hpp"
#include "Filepaths.h"
#include <cstring>
#include <string>

LocalizationManager::LocalizationManager()
{
	this->m_languageCode = 0;
	this->m_gotSystemLanguage = true;
	this->m_texts = new std::map < std::string, std::string >();

	//Get system language.
	Result rc = setGetSystemLanguage(&this->m_languageCode);
	if (R_FAILED(rc))
		this->m_gotSystemLanguage = false;
	else
		ParseTexts();
}

LocalizationManager::~LocalizationManager()
{
	delete(this->m_texts);
}

void LocalizationManager::ParseTexts()
{
	this->m_canParse = true;
	this->m_currentLanguage = (char*)&this->m_languageCode;

	std::ifstream myReadFile(TEXT_FILE);

	if (myReadFile)
	{
		myReadFile >> this->m_json;

	
		for (auto & text : m_json[this->m_currentLanguage])
		{		
			m_texts->insert(std::pair<std::string, std::string>(text[0].get<std::string>(), text[1].get<std::string>()));
		}
		
	}
}

const char * LocalizationManager::GetText(char * _key)
{
	std::string keyStr = _key;
	return m_texts->find(keyStr)->second.c_str();
}
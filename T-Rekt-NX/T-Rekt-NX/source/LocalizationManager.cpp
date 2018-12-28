#include "LocalizationManager.hpp"
#include "Filepaths.h"
#include <cstring>
#include <string>

LocalizationManager::LocalizationManager()
{

	Result rc = setInitialize();

	if (R_SUCCEEDED(rc))
	{
		this->m_languageCode = 0;
		this->m_gotSystemLanguage = true;

		//Get system language.
		rc = setGetSystemLanguage(&this->m_languageCode);
		if (R_SUCCEEDED(rc))
		{
			ParseTexts();
		}
		else
		{
			this->m_gotSystemLanguage = false;
			this->m_canParse = false;
		}
	}
	else
	{
		this->m_gotSystemLanguage = false;
		this->m_canParse = false;
	}
}

LocalizationManager::~LocalizationManager()
{
	setExit();
}

bool LocalizationManager::Initialized()
{
	return this->m_gotSystemLanguage && this->m_canParse;
}

void LocalizationManager::ParseTexts()
{
	this->m_gotSystemLanguage = true;
	this->m_canParse = false;
	m_currentLanguage = std::string((char*)&this->m_languageCode);

	std::ifstream langFile((std::string(LOCALIZATION_TEXT_FOLDER)+m_currentLanguage+std::string(".localization")).c_str());
	if (langFile)
	{
		this->m_canParse = true;
		langFile >> this->m_json;
	}
	else
	{
		std::ifstream myReadFile(LOCALIZATION_TEXT_FILE);

		if (myReadFile)
		{
			this->m_canParse = true;
			myReadFile >> this->m_json;
		}
	}
}

const char * LocalizationManager::GetText(char * _key)
{	
	return this->m_json.at(_key).get<std::string>().c_str();
}
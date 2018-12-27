#include "SaveManager.hpp"
#include "Filepaths.h"

SaveManager::SaveManager()
{
	this->m_data = new SaveData();
}

SaveManager::~SaveManager()
{
	delete(this->m_data);
}

Settings * SaveManager::GetSettings()
{
	return this->m_data->m_settings;
}

void SaveManager::ParseData()
{
	std::ifstream myReadFile(DATA_FILE);
	
	if (myReadFile)
	{
		myReadFile >> this->m_json;
		this->m_data->m_settings->m_muted = this->m_json["muted"];
		this->m_data->m_settings->m_debugMode = this->m_json["debugMode"];
		this->m_data->m_bestScore = this->m_json["bestScore"];
	}
	else
	{
		this->m_json =
		{
			{ "muted", false },
			{ "debugMode", false },
			{ "bestScore", 0 },
		};

		std::ofstream outfile(DATA_FILE);
		outfile << this->m_json;
		outfile.close();

	}
}

void SaveManager::Save(int _score)
{
	if (this->m_data->m_bestScore < _score)
	{
		this->m_json["bestScore"] = _score;
	}
	
	this->m_json["muted"] = this->m_data->m_settings->m_muted;
	this->m_json["debugMode"] = this->m_data->m_settings->m_debugMode;

	std::ofstream outfile(DATA_FILE);
	outfile << this->m_json;
	outfile.close();
}
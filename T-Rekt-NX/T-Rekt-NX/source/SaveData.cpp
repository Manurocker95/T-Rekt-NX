#include "SaveData.hpp"

SaveData::SaveData()
{
	this->m_bestScore = 0;
	this->m_settings = new Settings();
}

SaveData::~SaveData()
{
	delete(this->m_settings);
}
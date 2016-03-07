#include "TypeChecker.h"

#include <algorithm>

TypeChecker::TypeChecker()
	: m_invalidType(_T("INVALID_TYPE"))
{
}


TypeChecker::~TypeChecker()
{
}

void TypeChecker::AddType(int objectID, const std::tstring & type)
{
	std::map<int, std::vector<std::tstring>>::iterator it = m_mapTypes.find(objectID);
	if (it == m_mapTypes.end()) m_mapTypes.insert(std::pair<int, std::vector<std::tstring>>(objectID, std::vector<std::tstring>()));

	m_mapTypes[objectID].push_back(type);
}

const std::tstring & TypeChecker::getType(int objectID)
{
	std::map<int, std::vector<std::tstring>>::iterator it = m_mapTypes.find(objectID);
	if (it == m_mapTypes.end()) {
		//Logger::Log("No object has been found");
		return m_invalidType;
	}

	int index = m_mapTypes[objectID].size() - 1;
	return m_mapTypes[objectID][index];
}

bool TypeChecker::isType(int objectID, const std::tstring & type)
{
	std::map<int, std::vector<std::tstring>>::iterator it = m_mapTypes.find(objectID);
	if (it == m_mapTypes.end()) {
		//Logger::Log("No object has been found");
		return false;
	}

	if (!TypeExists(type, false)) {
		//Logger::Log("No object has been found");
		return false;
	}

	int index = m_mapTypes[objectID].size() - 1;
	return m_mapTypes[objectID][index] == type;
}

bool TypeChecker::isType(const std::tstring & type, const std::tstring & isType)
{
	std::map<int, std::vector<std::tstring>>::iterator itmap_from = m_mapTypes.end();
	std::map<int, std::vector<std::tstring>>::iterator itmap_to = m_mapTypes.end();

	if (!TypeExists(type, itmap_from))
	{
		//Logger::Log("No object has been found");
		return false;
	}

	if (!TypeExists(type, itmap_to, false))
	{
		//Logger::Log("No object has been found");
		return false;
	}

	int index = m_mapTypes[(*itmap_from).first].size() - 1;
	return m_mapTypes[(*itmap_from).first][index] == type;
}

bool TypeChecker::isA(int objectID, const std::tstring & type)
{
	std::map<int, std::vector<std::tstring>>::iterator it = m_mapTypes.find(objectID);
	if (it == m_mapTypes.end()) {
		//Logger::Log("No object has been found");
		return false;
	}

	if (!TypeExists(type)) {
		//Logger::Log("No object has been found");
		return false;
	}

	std::vector<std::tstring>::iterator it_type = std::find(m_mapTypes[objectID].begin(), m_mapTypes[objectID].end(), type);
	return it_type != m_mapTypes[objectID].end();
}

bool TypeChecker::isA(const std::tstring & type, const std::tstring & isType)
{
	std::map<int, std::vector<std::tstring>>::iterator itmap_from = m_mapTypes.end();
	std::map<int, std::vector<std::tstring>>::iterator itmap_to = m_mapTypes.end();

	if (!TypeExists(type, itmap_from))
	{
		//Logger::Log("No object has been found");
		return false;
	}

	if (!TypeExists(type, itmap_to, false))
	{
		//Logger::Log("No object has been found");
		return false;
	}

	std::vector<std::tstring>::iterator it_type = std::find(m_mapTypes[(*itmap_from).first].begin(), m_mapTypes[(*itmap_from).first].end(), type);
	return it_type != m_mapTypes[(*itmap_from).first].end();
}

bool TypeChecker::TypeExists(const std::tstring & type, bool last)
{
	for (std::map<int, std::vector<std::tstring>>::iterator it = m_mapTypes.begin(); it != m_mapTypes.end(); ++it) 
	{
		std::vector<std::tstring>::iterator it_from = std::find((*it).second.begin(), (*it).second.end(), type);
		if (it_from != (*it).second.end())
		{
			if ((*it).second[(*it).second.size() - 1] == type || !last) return true;
		}
	}
	return false;
}

bool TypeChecker::TypeExists(const std::tstring & type, std::map<int, std::vector<std::tstring>>::iterator & ref_it, bool last)
{
	for (std::map<int, std::vector<std::tstring>>::iterator it = m_mapTypes.begin(); it != m_mapTypes.end(); ++it)
	{
		std::vector<std::tstring>::iterator it_from = std::find((*it).second.begin(), (*it).second.end(), type);
		if (it_from != (*it).second.end())
		{
			if ((*it).second[(*it).second.size() - 1] == type || !last) {
				ref_it = it;
				return true;
			}
		}
	}
	return false;
}


#ifndef _TYPECHECKER_H
#define _TYPECHECKER_H

#include <vector>
#include <map>

#ifndef _STRING_H
#include "string.h"
#endif

#ifndef _SINGLETON_H
#include "Singleton.h"
#endif // !_SINGLETON_H


class TypeChecker
{
public:
	TypeChecker();
	~TypeChecker();

	/*void* operator new(size_t size);
	void operator delete(void* pdelete);*/

	void AddType(int objectID, const std::tstring& type);
	const std::tstring& getType(int objectID);

	bool isType(int objectID, const std::tstring& type);
	bool isType(const std::tstring& type, const std::tstring& isType);
	bool isA(int objectID, const std::tstring& type);
	bool isA(const std::tstring& type, const std::tstring& isType);

protected:
	bool TypeExists(const std::tstring& type, bool last = true);
	bool TypeExists(const std::tstring& type, std::map<int, std::vector<std::tstring>>::iterator& ref_it, bool last = true);

	std::map<int, std::vector<std::tstring>> m_mapTypes;
	std::tstring m_invalidType;
};

#endif // !_TYPECHECKER_H
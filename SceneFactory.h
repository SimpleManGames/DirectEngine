#ifndef _SCENEFACTORY_H
#define _SCENEFACTORY_H

#ifndef _MAP_H
	#include <map>
#endif
#ifndef _STRING_H
	#include "string.h"
#endif

#include "Singleton.h"

//Forward Declares
class Scene;

class SceneFactory
{
public:
	SceneFactory();
	~SceneFactory();
};

class TypeRegister : public SceneFactory
{
public:


};

#endif
#ifndef _SCENE_H
#define _SCENE_H

#include "BaseObject.h"
#ifndef _CONTEXT_H
	#include "Context.h"
#endif
#ifndef _SCENE_H
	#include "string.h"
#endif
#ifndef _SCENEFACTORY_H
	#include "SceneFactory.h"
#endif

class Scene :
	public BaseObject
{
	TYPE_INIT(Scene);
public:
	Scene(const std::tstring& name);
	virtual ~Scene();

	virtual bool Initialize();
	virtual bool PostInitialize();
	virtual bool LoadContent();
	virtual bool PostLoadContent();
	virtual bool Update(Context& context);
	virtual bool Draw(Context& context);
	virtual bool DrawUI(Context& context);
	virtual bool ShutDown();

protected:

private:

};

#endif
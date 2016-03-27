#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H

// C Runtime Header Files
#ifndef _MAP_
	#include <map>
#endif

// Additional Include Files
#include "Singleton.h"

#ifndef _CONTEXT_H
	#include "Context.h"
#endif
#ifndef _STRING_H
	#include "string.h"
#endif

// Foward Declares
class Scene;
class LoadingScene;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	bool Initialize();
	bool LoadContent();
	bool Update(Context& context);
	bool Draw(Context& context);
	bool ShutDown();

	bool AddScene(Scene* scene);
	bool RemoveScene(const std::tstring& name);

	Scene* FindScene(const std::tstring& name);
	Scene* GetActiveScene();

	void ClearScenes();
	void SetActiveScene(const std::tstring& name);

protected:
	std::map<std::tstring, Scene*> m_mapScenes;
	Scene* m_pActiveScene;
	LoadingScene* m_pLoadingScene;

};

#endif // !_SCENEMANAGER_H
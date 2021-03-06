#include "WinMain.h"

#include "Engine.h"
#ifndef _STRING_H
	#include "string.h"
#endif
#ifndef _IOSTREAM_H
	#include "iostream.h"
#endif
#ifndef _DELETEMACRO_H
	#include "deletemacros.h"
#endif // !_DELETEMACRO_H
#ifndef _SINGLETON_H
	#include "Singleton.h"
#endif // !_SINGLETON_H
#ifndef _TYPECHECKER_H
	#include "TypeChecker.h"
#endif // !_TYPECHECKER_H
#ifndef _GRAPHICSDEVICEMANAGER_H
	#include "GraphicsDeviceManager.h"
#endif // !_GRAPHICSDEVICEMANAGER_H

#include "Logger.h"


#if defined (DEBUG) | defined(_DEBUG)
int _tmain(int argc, char* argv[]) 
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	Logger::Log(_T("Starting Program"), LOGTYPE_INFO, false);

	//Run winmain func
	WinMain((HINSTANCE)GetModuleHandle(NULL), 0, 0, SW_SHOW);
}
#endif

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

#if defined (DEBUG) | defined(_DEBUG)
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	// Enable run-time memory leak check for debug builds
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(0);

#endif

	// Create the engine
	Engine* pEngine = new Engine();

	//Kick of the game
	int result = pEngine->RunLoop();

	// Delete the engine
	SafeDelete(pEngine);

	// Destory the Graphic Manager
	Singleton<GraphicsDeviceManager>::DestoryInstance();

	// Destory singletons
	Singleton<TypeChecker>::DestoryInstance();

	return result;
}
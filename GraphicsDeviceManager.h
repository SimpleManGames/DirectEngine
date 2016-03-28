#ifndef _GRAPHICSDEVICEMANAGER_H
#define _GRAPHICSDEVICEMANAGER_H

// Gets the instance of the window
#define GETWINDOW Singleton<GraphicsDeviceManager>::GetInstance()->GetGraphics()->m_pWindow

// Foward Declaration
class Graphics;

// Graphics Device Manager class
class GraphicsDeviceManager
{
	friend class Engine;
public:
	// Default constructor
	GraphicsDeviceManager();
	// Default destructor
	~GraphicsDeviceManager();
	// Returns the graphics
	Graphics* GetGraphics() { return m_pGraphics; }

private:
	// Set the graphics
	// Takes in a graphic pointer
	void SetGraphics(Graphics* graphics) { m_pGraphics = graphics; }
	// Holds the pointer to graphics
	Graphics* m_pGraphics;
};

#endif // _GRAPHICSDEVICEMANAGER_H
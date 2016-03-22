#ifndef _GRAPHICSDEVICEMANAGER_H
#define _GRAPHICSDEVICEMANAGER_H

#define GETWINDOW Singleton<GraphicsDeviceManager>::GetInstance()->GetGraphics()->m_pWindow

// Foward Declaration
class Graphics;

class GraphicsDeviceManager
{
	friend class Engine;
public:
	GraphicsDeviceManager();
	~GraphicsDeviceManager();

	Graphics* GetGraphics() { return m_pGraphics; }

private:
	void SetGraphics(Graphics* graphics) { m_pGraphics = graphics; }

	Graphics* m_pGraphics;
};

#endif // _GRAPHICSDEVICEMANAGER_H
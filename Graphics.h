#ifndef _GRAPHICS_H
#define _GRAPHICS_H

// C Runtime Header Files

// Additional Header Files
#include "System.h"

//#ifndef _LOGGER_H
//#include "Logger.h"
//#endif

#ifndef _2DUTILL_H
#include "d2dutill.h"
#endif // !_2DUTILL_H

// Foward Declaration
class Window;

//Struct
struct GraphicsData : 
	public SystemData {
public:
	GraphicsData(Window* wnd = nullptr);

	Window* pWnd;
};

class Graphics :
	public System
{
	friend class Engine;
public:
	// Methods
	HRESULT OnResize(UINT width, UINT height);

	ID2D1HwndRenderTarget* GetRenderTarget() { return m_pRenderTarget; }
	IWICImagingFactory* GetImageFactory() { return m_pImageFactory; }
	ID2D1SolidColorBrush* GetColorBrush() { return m_pColorBrush; }
	ID2D1Factory* GetD2DFactory() { return m_pD2DFactory; }

protected:
	// Methods

	// Constructor & Destructor
	Graphics(const GraphicsData& data);
	virtual ~Graphics();

	// Copy Constructor & Default Assignment Operator
	Graphics(const Graphics& other);
	Graphics& operator=(const Graphics& ref);

	bool Initialize();
	bool ShutDown();

private:
	// Methods
	//void* operator new(size_t size);
	//void operator delete(void* pdelete);

	HRESULT CreateDeviceIndependentResources();
	HRESULT CreateDeviceDependentResoures();

	void DiscardDeviceResources();

	void BeginDraw();
	HRESULT EndDraw();

	// Members
	ID2D1HwndRenderTarget* m_pRenderTarget;
	IWICImagingFactory* m_pImageFactory;
	ID2D1SolidColorBrush* m_pColorBrush;
	ID2D1Factory* m_pD2DFactory;

	Window* m_pWindow;
};

#endif // _GRAPHICS_H
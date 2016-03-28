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

/// Foward Declaration
class Window;

/// Struct
struct GraphicsData : public SystemData 
{
public:
	/// Construtors & Deconstrutors

	// GraphicsData Construtor
	//Takes the current window, sets pWnd, default value is nullptr
	GraphicsData(Window* wnd = nullptr);

	/// Variables

	// The current window
	Window* pWnd;
};

class Graphics : public System
{
	friend class Engine;
public:
	/// Methods
	
	// Checks if we need to resize of window
	HRESULT OnResize(UINT width, UINT height);

	// Returns the RenderTarget
	ID2D1HwndRenderTarget* GetRenderTarget() { return m_pRenderTarget; }
	// Returns the Image Factory
	IWICImagingFactory* GetImageFactory() { return m_pImageFactory; }
	// Return the Color Brush
	ID2D1SolidColorBrush* GetColorBrush() { return m_pColorBrush; }
	// Returns the Direct2D Factory
	ID2D1Factory* GetD2DFactory() { return m_pD2DFactory; }

protected:	
	/// Constructor & Deconstructor

	// Graphics Construtor
	Graphics(const GraphicsData& data);
	// Default Graphics Deconstrutor
	virtual ~Graphics();

	// Copy Constructor & Default Assignment Operator
	Graphics(const Graphics& other);
	Graphics& operator=(const Graphics& ref);

	/// Methods

	// Inits the Graphics Class
	bool Initialize();
	// Shut down the Graphics Class
	bool ShutDown();

private:
	/// Methods
	//void* operator new(size_t size);
	//void operator delete(void* pdelete);

	// Create a independent Factory and returns it
	HRESULT CreateDeviceIndependentResources();
	// Create a dependent Render Target and sets the default values then returns it
	HRESULT CreateDeviceDependentResoures();

	// Deletes the Render Target
	void DiscardDeviceResources();
	// Begins the Draw
	void BeginDraw();
	// Ends the Draw
	HRESULT EndDraw();

	/// Members
	
	// Gets the Render Target
	ID2D1HwndRenderTarget* m_pRenderTarget;
	// Gets the Image Factory
	IWICImagingFactory* m_pImageFactory;
	// Get the Color Brush
	ID2D1SolidColorBrush* m_pColorBrush;
	// Gets the Direct2D Factory
	ID2D1Factory* m_pD2DFactory;

	// The current window
	Window* m_pWindow;
};

#endif // _GRAPHICS_H
#ifndef _WINDOW_H
#define _WINDOW_H

#include "System.h"

//C Runtime header files
#ifndef _WINDOWS_
#include <Windows.h>
#endif

//Additional include files
#ifndef _CONTEXT_H
#include "Context.h"
#endif
#ifndef _STRING_H
#include "string.h"
#endif

//Structs

// WindowData struct that inherits from SystemData
struct WindowData : public SystemData
{
	// Default constructor for WindowData
	// Sets the default values for SystemData
	WindowData();
	// Window Data constructor
	// Takes in a width, height, title, bits, and if its fullscreen
	WindowData(int w, int h, const std::tstring& title = _T("SimpleEngine V1.0"), int b = 32, bool fs = false);

	// Width of the window
	int width;
	// Height of the window
	int height;
	// Number of bits
	int bits;
	// Title of the window
	std::tstring windowTitle;
	// Bool for fullscreen
	bool fullscreen;
};

// ResizeData struct
struct ResizeData
{
	// Default constructor for ResizeData
	// Sets values to default
	ResizeData();
	// Constructor for ResizeData
	// Takes in a bool for if you want to resize, a new width and a new height
	ResizeData(bool resize, int nw, int nh);
	// Bool to see if we should change the window size
	bool mustResize;
	// New width for the window
	int newWidth;
	// New height for the window
	int newHeight;
};

// Window class that inherits from System
class Window : public System
{
	friend class Engine;
public:
	// Returns the width of the window
	int GetWidth();
	// Returns the height of the window
	int GetHeight();
	// Return the window
	HWND GetWindowHandle() { return m_hWindow; }
	// Return the device context
	HDC GetDeviceContext() { return m_hDC; }
	// Return the instance
	HINSTANCE GetInstance() { return m_hInst; }
	// Return the resize data
	ResizeData& GetResizeData() { return m_ResizeData; }

	LRESULT HandleEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lparam);

protected:
	// Window constructor
	// Takes in a ref to windowdata
	Window(const WindowData& data);
	// Default virtual destructor for window
	virtual ~Window();
	// Initialize the window
	virtual bool Initialize();
	// Udpate the window with the current context
	virtual bool Update(Context& context);
	// Shut down the window
	virtual bool ShutDown();

private:
	// Function to center the window
	bool CenterWindow();

	LRESULT CALLBACK Window_Procedure(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);

	//Members
	HWND m_hWindow;
	HDC m_hDC;
	HINSTANCE m_hInst;

	int m_Width;
	int m_Height;
	int m_Bits;

	bool m_bFullScreen;

	ResizeData m_ResizeData;

	std::tstring m_Title;
};

#endif
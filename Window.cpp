#include "Window.h"

#include "Logger.h"

WindowData::WindowData()
	:SystemData(_T(""), SystemType::Sys_Invalid)
	, width(-1)
	, height(-1)
	, bits(-1)
	, windowTitle(_T(""))
	, fullscreen(false)
{

}
WindowData::WindowData(int w, int h, const std::tstring& title, int b, bool fs)
	:SystemData(_T("Window"), SystemType::Sys_Window)
	, width(w)
	, height(h)
	, bits(b)
	, windowTitle(title)
	, fullscreen(fs)
{

}

ResizeData::ResizeData()
	: mustResize(false)
	, newWidth(-1)
	, newHeight(-1)
{

}
ResizeData::ResizeData(bool resize, int nw, int nh)
	: mustResize(resize)
	, newWidth(nw)
	, newHeight(nh)
{

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (msg == WM_CREATE)
	{
		// if the message is WM_CREATE, the lparam contains a pointer to a CREATESTRUCT
		// the CREATESTRUCT containes the " this " pointer from the CreateWindow method
		// the " this " pointer of our app is stored in the createstruct pcs->lpCreateParams
		CREATESTRUCT* pCS = (CREATESTRUCT*)lparam;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pCS->lpCreateParams);
	}
	else
	{
		//Retrieve the stored " this " pointer
		Window* pWindow = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if (pWindow) return pWindow->HandleEvent(hWnd, msg, wparam, lparam);
	}

	return DefWindowProc(hWnd, msg, wparam, lparam);
}
int Window::GetWidth() { return m_Width; }
int Window::GetHeight() { return m_Height; }
LRESULT Window::HandleEvent(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		case WM_ACTIVATE:
		{
			if (!HIWORD(wparam))
				this->Activate();
			else this->Deactivate();

			return 0;
		}
		case WM_SIZE:
		{
			UINT width = LOWORD(lparam);
			UINT height = HIWORD(lparam);

			m_ResizeData.mustResize = true;
			m_ResizeData.newWidth = width;
			m_ResizeData.newHeight = height;

			return 0;
		}
		case WM_DISPLAYCHANGE:
		{
			InvalidateRect(hWnd, NULL, FALSE);

			return 0;
		}
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hWnd, msg, wparam, lparam);
}

Window::Window(const WindowData& data)
	:System(data)
	, m_hWindow(NULL)
	, m_hDC(NULL)
	, m_hInst(NULL)

	, m_Width(data.width)
	, m_Height(data.height)
	, m_Bits(data.bits)

	, m_bFullScreen(data.fullscreen)

	, m_Title(data.windowTitle)

	, m_ResizeData()
{
}
Window::~Window()
{
	// TO DO: Deconstrutor
}

bool Window::Initialize()
{
	System::Initialize();

	unsigned int pixelFormat;           // Holds The Results After Searching For A Match

	DWORD dwExStyle;                    // Window Extended Style
	DWORD dwStyle;                      // Window Style

	RECT        wndRect;                // Grabs Rectangle Upper Left / Lower Right Values
	wndRect.left = (long)0;             // Set Left Value To 0
	wndRect.right = (long)m_Width;      // Set Right Value To Requested Width
	wndRect.top = (long)0;              // Set Top Value To 0
	wndRect.bottom = (long)m_Height;    // Set Bottom Value To Requested Height

	WNDCLASS wndClass;                  // Windows Class Structure
	std::tstring className = m_Title;   // Window title

	wndClass.style = CS_DBLCLKS | CS_DROPSHADOW | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = NULL;
	wndClass.cbWndExtra = NULL;
	wndClass.hInstance = (HINSTANCE)GetModuleHandle(NULL);
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO); 
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = NULL;
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = className.c_str();

	if (!RegisterClass(&wndClass))
	{
		Logger::Log(_T("Failed to register window"), LOGTYPE_ERROR, true);
		return false;
	}

	if (m_bFullScreen)
	{
		DEVMODE dmScreenSettings;                               // Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings)); // Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);     // Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = m_Width;                 // Selected Screen Width
		dmScreenSettings.dmPelsHeight = m_Height;               // Selected Screen Height
		dmScreenSettings.dmBitsPerPel = m_Bits;                 // Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			//// If The Mode Fails, Use Windowed Mode.
			Logger::Log(_T("The Requested Fullscreen Mode Is Not Supported By\nYour Video Card."), LOGTYPE_WARNING, true);

			dwExStyle = WS_EX_APPWINDOW;    // Window Extended Style
			dwStyle = WS_POPUP;             // Windows Style
											//ShowCursor(FALSE);            // Hide Mouse Pointer (Optional)
		}
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;         // Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;                          // Windows Style
	}

	AdjustWindowRectEx(&wndRect, dwStyle, FALSE, dwExStyle);        // Adjust Window To True Requested Size

	if (!(m_hWindow = CreateWindowEx(
		dwExStyle,
		className.c_str(),
		className.c_str(),
		dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		0, 0,
		wndRect.right - wndRect.left,   // Calculate Window Width
		wndRect.bottom - wndRect.top,   // Calculate Window Height
		NULL,
		NULL,
		m_hInst,
		this)))
	{
		Logger::Log(_T("Failed to window handle = NULL"), LOGTYPE_ERROR, true);
		return false;
	}

	static  PIXELFORMATDESCRIPTOR pfd =             // pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),              // Size Of This Pixel Format Descriptor
		1,                                          // Version Number
		PFD_DRAW_TO_WINDOW |                        // Format Must Support Window
		PFD_SUPPORT_OPENGL |                        // Format Must Support OpenGL
		PFD_DOUBLEBUFFER,                           // Must Support Double Buffering
		PFD_TYPE_RGBA,                              // Request An RGBA Format
		(BYTE)m_Bits,                               // Select Our Color Depth
		0, 0, 0, 0, 0, 0,                           // Color Bits Ignored
		0,                                          // No Alpha Buffer
		0,                                          // Shift Bit Ignored
		0,                                          // No Accumulation Buffer
		0, 0, 0, 0,                                 // Accumulation Bits Ignored
		16,                                         // 16Bit Z-Buffer (Depth Buffer)  
		0,                                          // No Stencil Buffer
		0,                                          // No Auxiliary Buffer
		PFD_MAIN_PLANE,                             // Main Drawing Layer
		0,                                          // Reserved
		0, 0, 0                                     // Layer Masks Ignored
	};

	if (!(m_hDC = GetDC(m_hWindow)))                // Did We Get A Device Context?
	{
		Logger::Log(_T("Can't create Device Context"), LOGTYPE_ERROR, true);
		return false;
	}
	if (!(pixelFormat = ChoosePixelFormat(m_hDC, &pfd)))
	{
		Logger::Log(_T("Can't Find A Suitable PixelFormat"), LOGTYPE_ERROR, true);
		return false;
	}
	if (!SetPixelFormat(m_hDC, pixelFormat, &pfd))
	{
		Logger::Log(_T("Can't Set The PixelFormat"), LOGTYPE_ERROR, true);
		return false;
	}

	ShowWindow(m_hWindow, SW_SHOW);
	SetForegroundWindow(m_hWindow);
	SetFocus(m_hWindow);
	//UpdateWindow(m_hWindow);

	m_ResizeData.mustResize = true;
	m_ResizeData.newWidth = m_Width;
	m_ResizeData.newHeight = m_Height;

	if (!this->CenterWindow())
	{
		Logger::Log(_T("Failed to center window"), LOGTYPE_ERROR, true);
		return false;
	}

	//Disable closing button debug window
	HWND hConsoleWnd = GetConsoleWindow();
	if (hConsoleWnd != NULL)
	{
		HMENU hConsoleMenu = GetSystemMenu(hConsoleWnd, FALSE);
		if (hConsoleMenu != 0)
		{
			BOOL bRet = RemoveMenu(hConsoleMenu, SC_CLOSE, MF_BYCOMMAND);
			if (!bRet)
			{
				Logger::Log(_T("Failed to remove close button"), LOGTYPE_ERROR, true);
				return false;
			}
		}
	}

	Logger::Log(_T("Window is initialized"), LOGTYPE_INFO, false);

	//Success
	return true;
}
bool Window::Update(Context& context)
{
	if (WINDOW != this)
		WINDOW = this;

	return true;
}
bool Window::ShutDown()
{
	if (m_bFullScreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(true);
	}

	//Are we able to release the DC
	//Set DC to null
	if (m_hDC && !ReleaseDC(m_hWindow, m_hDC))
	{
		Logger::Log(_T("Release DC failed"), LOGTYPE_WARNING, false);
		m_hDC = NULL;
		return false;
	}
	//Are we able to release the DC
	//Set DC to null
	if (m_hWindow && !DestroyWindow(m_hWindow))
	{
		Logger::Log(_T("Could not destroy the window"), LOGTYPE_WARNING, false);
		m_hWindow = NULL;
		return false;
	}
	//Are we able to release the DC
	//Set DC to null
	if (!UnregisterClass(m_Title.c_str(), m_hInst))
	{
		Logger::Log(_T("Could not unregister class"), LOGTYPE_WARNING, false);
		m_hInst = NULL;
		return false;
	}

	return true;
}
bool Window::CenterWindow()
{
	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;       // Window Extended Style
	DWORD dwStyle = WS_OVERLAPPEDWINDOW;					    // Windows Style

	RECT R = { 0, 0, m_Width, m_Height };

	// Calculates the required size of the window rectangle, based on the desired client-rectangle size. 
	// The window rectangle can then be passed to the CreateWindow function to create a window whose client area is the desired size.

	AdjustWindowRectEx(&R, dwStyle, false, dwExStyle);

	int windowwidth = R.right - R.left;
	int windowheight = R.bottom - R.top;

	// GetSystemMetrics: 
	// Retrieves the specified system metric or system configuration setting.

	// System Methics: 
	// To be DPI aware, an application can make no assumptions about the pixel sizes of various Windows screen elements, such as icon sizes or border widths. 
	// Windows Mobile 6.5 provides a number of system metrics that offer information about the user's system. These can be queried via the GetSystemMetrics Windows Embedded CE-based function.

	int posx = GetSystemMetrics(SM_CXSCREEN) / 2 - windowwidth / 2;
	int posy = GetSystemMetrics(SM_CYSCREEN) / 2 - windowheight / 2;

	// Changes the size, position, and Z order of a child, pop - up, or top - level window.
	// These windows are ordered according to their appearance on the screen.
	// The topmost window receives the highest rank and is the first window in the Z order.

	if (SetWindowPos(m_hWindow, NULL, posx, posy, windowwidth, windowheight, SWP_SHOWWINDOW) == NULL)
		return false;

	return true;
}
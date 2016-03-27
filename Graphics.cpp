#include "Graphics.h"

#include "Window.h"

#ifndef _DELETEMACROS_H
	#include "deletemacros.h"
#endif

#include "Logger.h"

// Struct
GraphicsData::GraphicsData(Window* wnd) 
	: SystemData(_T("Graphics"), SystemType::Sys_Graphics)
	, pWnd(wnd) 
{

}

// Class Graphics
Graphics::Graphics(const GraphicsData& data) 
	: System(data)
	, m_pRenderTarget(nullptr)
	, m_pD2DFactory(nullptr)
	, m_pColorBrush(nullptr)
	, m_pImageFactory(nullptr)
	, m_pWindow(data.pWnd)
{

}

// Deconstructor
Graphics::~Graphics() { }

// Resizes the current RenderTargets window
HRESULT Graphics::OnResize(UINT width, UINT height) { return (m_pRenderTarget) ? m_pRenderTarget->Resize(D2D1::SizeU(width, height)) : S_FALSE; }

// Init the graphics
bool Graphics::Initialize() 
{
	System::Initialize();

	// Call CreateDeviceIndependentResources to init the default values
	HRESULT hr = CreateDeviceIndependentResources();
	if (FAILED(hr)) return false;
	// Call CreateDeviceDependentResoures to init the default values
	hr = CreateDeviceDependentResoures();
	if (FAILED(hr)) return false;

	Logger::Log(_T("Graphics is initialized"), LOGTYPE_INFO, false);
	return true;
}

// Shut down the graphics
bool Graphics::ShutDown() 
{
	System::ShutDown();

	SafeRelease(m_pD2DFactory);
	SafeRelease(m_pColorBrush);
	//SafeRelease(m_pImageFactory);
	SafeRelease(m_pRenderTarget);

	return true;
}

// Create a independent Factory and returns it
HRESULT Graphics::CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;

	// Create a Direct2D factory
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&m_pImageFactory);

	return hr;
}

// Create a dependent Render Target and sets the default values then returns it
HRESULT Graphics::CreateDeviceDependentResoures()
{
	// Init the results to a neutral value
	HRESULT hr = S_OK;
	if (!m_pRenderTarget) 
	{
		// Get the window handle
		HWND hWnd = m_pWindow->GetWindowHandle();

		// Get the size of the window
		RECT rc;
		GetClientRect(hWnd, &rc);
		D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

		// Create Render Target
		hr = m_pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, size), &m_pRenderTarget);
		if (FAILED(hr)) return hr;

		// Create the brush for Render Target
		hr = m_pRenderTarget->CreateSolidColorBrush((D2D1::ColorF) D2D1::ColorF::Black, &m_pColorBrush);
		if (FAILED(hr)) return hr;
	}
	// Return the result
	return hr;
}

// Deletes the Render Target
void Graphics::DiscardDeviceResources() { SafeRelease(m_pRenderTarget); }

// Begins the Draw
void Graphics::BeginDraw() 
{
	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
}

// Ends the Draw
HRESULT Graphics::EndDraw() { return m_pRenderTarget->EndDraw(); }
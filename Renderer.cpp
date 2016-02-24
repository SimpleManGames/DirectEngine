#include "Renderer.h"

// Additional Include Files

#include "Graphics.h"
#include "GraphicsDeviceManager.h"


Renderer::Renderer() :
	m_InterpolationMode(D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR)
	{ }
Renderer::~Renderer() { }

void Renderer::SetColor(const Color& c) { GRAPHICSDEVICEMANAGER->GetGraphics()->GetColorBrush()->SetColor(D2D1::ColorF(c.red, c.green, c.blue, c.alpha)); }
void Renderer::SetColor(float r, float g, float b, float a) { SetColor(Color(r, g, b, a)); }

void Renderer::DrawLine(const Vector2D & v1, const Vector2D & v2, float lineWidth) {
	D2D1_POINT_2F p1, p2;
	p1.x = (FLOAT)v1.x; p1.y = (FLOAT)v1.y;
	p2.x = (FLOAT)v2.x; p2.y = (FLOAT)v2.y;

	GRAPHICSDEVICEMANAGER->GetGraphics()->GetRenderTarget()->DrawLine(p1, p2, GRAPHICSDEVICEMANAGER->GetGraphics()->GetColorBrush(), lineWidth);
}
void Renderer::DrawLine(float x1, float y1, float x2, float y2, float lineWidth) {
	Vector2D v1(x1, y1);
	Vector2D v2(x2, y2);

	DrawLine(v1, v2, lineWidth);
}
void Renderer::DrawLine(const Ray &ray, float lineWidth) { 
	Vector2D v1(ray.p);
	Vector2D v2(ray.p + ray.d * ray.l);

	DrawLine(v1, v2, lineWidth);
}

void Renderer::DrawRect(double left, double top, double width, double height, float lineWidth) { DrawRect(Rect2D(left, top, left + width, top + height), lineWidth); }
void Renderer::DrawRect(const Vector2D& lefttop, const Vector2D& rightbottom, float lineWidth) { DrawRect(Rect2D(lefttop, rightbottom), lineWidth); }
void Renderer::DrawRect(const Rect2D& rect, float lineWidth) {
	D2D1_RECT_F d2dRect = D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom);
	GRAPHICSDEVICEMANAGER->GetGraphics()->GetRenderTarget()->DrawRectangle(d2dRect, GRAPHICSDEVICEMANAGER->GetGraphics()->GetColorBrush(), lineWidth);
}
void Renderer::DrawRect(const AABB& rect, float lineWidth) { DrawRect(Rect2D(rect.minv(), rect.maxv()), lineWidth); }

void Renderer::DrawCircle(double xcenter, double ycenter, double r, float lineWidth) {
	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2((FLOAT)xcenter, (FLOAT)ycenter), (FLOAT)r, (FLOAT)r);
	GRAPHICSDEVICEMANAGER->GetGraphics()->GetRenderTarget()->DrawEllipse(ellipse, GRAPHICSDEVICEMANAGER->GetGraphics()->GetColorBrush(), lineWidth);
}
void Renderer::DrawCircle(const Vector2D & center, double r, float lineWidth) { DrawCircle(center.x, center.y, lineWidth); }
void Renderer::DrawCircle(const Circle &cir, float lineWidth) { DrawCircle(cir.p.x, cir.p.y, cir.r, lineWidth); }

void Renderer::DrawPolygon(const std::vector<Vector2D> vecPoints, bool close, float lineWidth) {
	Vector2D* points = new Vector2D[(int)vecPoints.size()];
	for (int i = 0; i < (int)vecPoints.size(); ++i) points[i] = vecPoints[i];

	DrawPolygon(points, vecPoints.size(), close, lineWidth);
}
void Renderer::DrawPolygon(Vector2D * points, int size, bool close, float lineWidth) {
	if (size < 3) return;
	for (int countLoop = 0; countLoop < size - 1; ++countLoop) DrawLine(points[countLoop], points[countLoop + 1], lineWidth);
	if (close) DrawLine(points[0], points[size - 1], lineWidth);
}

void Renderer::FillRect(double left, double top, double width, double height) { FillRect(Rect2D(left, top, left + width, top + height)); }
void Renderer::FillRect(const Vector2D& lefttop, const Vector2D& rightbottom) { FillRect(Rect2D(lefttop, rightbottom)); }
void Renderer::FillRect(const Rect2D& rect){
	D2D1_RECT_F d2dRect = D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom);
	GRAPHICSDEVICEMANAGER->GetGraphics()->GetRenderTarget()->FillRectangle(d2dRect, GRAPHICSDEVICEMANAGER->GetGraphics()->GetColorBrush());
}
void Renderer::FillRect(const AABB& rect) { FillRect(Rect2D(rect)); }

void Renderer::FillCircle(const Vector2D & center, double r) { FillCircle(center.x, center.y, r); }
void Renderer::FillCircle(double xcenter, double ycenter, double r) {
	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2((FLOAT)xcenter, (FLOAT)ycenter), (FLOAT)r, (FLOAT)r);
	GRAPHICSDEVICEMANAGER->GetGraphics()->GetRenderTarget()->FillEllipse(ellipse, GRAPHICSDEVICEMANAGER->GetGraphics()->GetColorBrush());
}
void Renderer::FillCircle(const Circle& cir) { FillCircle(cir.p.x, cir.p.y, cir.r); }

void Renderer::FillPolygon(const std::vector<Vector2D> vecPoints, bool close) {
	Vector2D* points = new Vector2D[(int)vecPoints.size()];
	for (int i = 0; i < (int)vecPoints.size(); ++i) points[i] = vecPoints[i];

	FillPolygon(points, vecPoints.size(), close);
}
void Renderer::FillPolygon(Vector2D * points, int size, bool close) {
	if (size < 3) return;
	HRESULT hr;

	ID2D1PathGeometry* pGeometry;
	hr = GRAPHICSDEVICEMANAGER->GetGraphics()->GetD2DFactory()->CreatePathGeometry(&pGeometry);
	if (FAILED(hr)) {
		SafeRelease(pGeometry);
		//Logger::Log(_T("Failed to create path geometry"), LOGTYPE_WARNING, false);
		return;
	}

	// Write to path geometry using the geometry sink
	ID2D1GeometrySink* pGeometrySink = nullptr;
	hr = pGeometry->Open(&pGeometrySink);
	if (FAILED(hr)) {
		SafeRelease(pGeometrySink);
		SafeRelease(pGeometry);
		//Logger::Log(_T("Failed to create geometry sink"), LOGTYPE_WARNING, false);
		return;
	}

	if (SUCCEEDED(hr)) {
		pGeometrySink->BeginFigure(D2D1::Point2F((FLOAT)points[0].x, (FLOAT)points[0].y), D2D1_FIGURE_BEGIN_FILLED);

		for (int i = 0; i < size; ++i) pGeometrySink->AddLine(D2D1::Point2F((FLOAT)points[i].x, (FLOAT)points[i].y));

		pGeometrySink->EndFigure(D2D1_FIGURE_END_CLOSED);

		hr = pGeometrySink->Close();
		SafeRelease(pGeometrySink);
	}

	if (SUCCEEDED(hr)) {
		GRAPHICSDEVICEMANAGER->GetGraphics()->GetRenderTarget()->FillGeometry(pGeometry, GRAPHICSDEVICEMANAGER->GetGraphics()->GetColorBrush());
		SafeRelease(pGeometry);
		return;
	}
	SafeRelease(pGeometry);
}


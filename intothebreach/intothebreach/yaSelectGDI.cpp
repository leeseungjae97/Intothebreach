#include "yaSelectGDI.h"
#include "yaApplication.h"
extern ya::Application application;
SelectGDI::SelectGDI(HDC _dc, PEN_TYPE ePenType)
	: m_hDC(_dc)
	, m_hDefaultPen(nullptr)
	, m_hDefaultBrush(nullptr) {
	HPEN hPen = application.GetPen(ePenType);
	m_hDefaultPen = (HPEN)SelectObject(_dc, hPen);
}

SelectGDI::SelectGDI(HDC _dc, BRUSH_TYPE eBrushType)
	: m_hDC(_dc)
	, m_hDefaultPen(nullptr)
	, m_hDefaultBrush(nullptr) {
	HBRUSH hBrush = application.GetBrush(eBrushType);
	m_hDefaultBrush = (HBRUSH)SelectObject(_dc, hBrush);
}

SelectGDI::~SelectGDI() {
	SelectObject(m_hDC, m_hDefaultPen);
	SelectObject(m_hDC, m_hDefaultBrush);
}

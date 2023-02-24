#pragma once
#include "YamYamEngine.h"
class SelectGDI {
private:
	HDC m_hDC;
	HPEN m_hDefaultPen;
	HBRUSH m_hDefaultBrush;
public:
	SelectGDI(HDC _dc, PEN_TYPE ePenType);
	SelectGDI(HDC _dc, BRUSH_TYPE eBrushType);
	~SelectGDI();
};


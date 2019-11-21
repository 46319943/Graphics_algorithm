#include "stdafx.h"
#include "GeoPolygon.h"


void CGeoPolygon::Draw(CDC * pDC)
{
	if (ctPt.x == 0 && ctPt.y == 0) {
		pDC->Polygon(pts.GetData(), pts.GetSize());
	}
	else {
		// 默认使用白色填充，黑色边界
		pDC->Polygon(pts.GetData(), pts.GetSize());
		FillByFlood(pDC);
	}
}

void CGeoPolygon::addPoint(CPoint pt)
{
	pts.Add(pt);
}

CGeoPolygon::CGeoPolygon()
	: ctPt(0, 0)
{
}


CGeoPolygon::~CGeoPolygon()
{
}


// 使用种子法填充平面
void CGeoPolygon::FillByFlood(CDC* pDC)
{
	int x, y;
	CPoint pt;
	CArray<CPoint, CPoint>seeds;
	seeds.Add(ctPt);
	while (seeds.GetSize() > 0) {
		pt = seeds.GetAt(seeds.GetSize() - 1);
		seeds.RemoveAt(seeds.GetSize() - 1);
		x = pt.x;
		y = pt.y;
		pDC->SetPixel(x, y, color);
		if (pDC->GetPixel(x + 1, y) == RGB(255, 255, 255))
			seeds.Add(CPoint(x + 1, y));
		if (pDC->GetPixel(x, y + 1) == RGB(255, 255, 255))
			seeds.Add(CPoint(x, y + 1));
		if (pDC->GetPixel(x - 1, y) == RGB(255, 255, 255))
			seeds.Add(CPoint(x - 1, y));
		if (pDC->GetPixel(x, y - 1) == RGB(255, 255, 255))
			seeds.Add(CPoint(x, y - 1));
	}

}

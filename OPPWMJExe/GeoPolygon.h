#pragma once
#include "GeoObject.h"
#include "afxtempl.h"
#include "atltypes.h"
class CGeoPolygon :
	public CGeoObject
{
public:
	void Draw(CDC *pDC);
	void addPoint(CPoint pt);
	CArray<CPoint, CPoint>pts;

	CGeoPolygon();
	virtual ~CGeoPolygon();
	// 使用种子法填充平面
	void FillByFlood(CDC* pDC);
	// 初始种子点
	CPoint ctPt;
	// 种子填充时平面的颜色
	COLORREF color;

};


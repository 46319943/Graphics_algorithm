// GeoPolyline.h: interface for the CGeoPolyline class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEOPOLYLINE_H__FF9631AB_314A_44E3_8D71_A48E919F423D__INCLUDED_)
#define AFX_GEOPOLYLINE_H__FF9631AB_314A_44E3_8D71_A48E919F423D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "geoObject.h"
#include "afxtempl.h"

class CGeoPolyline : public CGeoObject 
{
public:	
	void Draw(CDC *pDC);
	void addPoint(CPoint pt);
	CArray<CPoint,CPoint>pts;
	CArray<CPoint, CPoint>geoPts;

	CGeoPolyline();
	virtual ~CGeoPolyline();

	// 使用数值微分法画线
	void DrawByDDA(CDC* pDC);
	// 返回点的Code值
	int GetCode(CRect rect, CPoint pt);
	void Clip(CRect rect);
	// 裁切的点
	CArray<CPoint, CPoint> clpPts;
	// 画贝塞尔曲线，根据点的数量来调用二次或三次贝塞尔曲线
	void Bezier(CDC * pDC);
	// 用4个点画3次贝塞尔曲线
	void Bezier3(CDC * pDC, CPoint p0, CPoint p1, CPoint p2, CPoint p3);
	// 用3个点画2次贝塞尔曲线
	void Bezier2(CDC * pDC, CPoint p0, CPoint p1, CPoint p2);
	// 画裁剪的点
	void DrawClip(CDC * pDC);

	// 根据投影变换规则画图
	void Draw(CDC *pDC, CMapProjection * mapPrj);
};

#endif // !defined(AFX_GEOPOLYLINE_H__FF9631AB_314A_44E3_8D71_A48E919F423D__INCLUDED_)

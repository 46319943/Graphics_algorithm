// GeoLayer.h: interface for the CGeoLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEOLAYER_H__C79B87B9_B91A_4880_B7DD_7A44CB0921E0__INCLUDED_)
#define AFX_GEOLAYER_H__C79B87B9_B91A_4880_B7DD_7A44CB0921E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "afxtempl.h"
#include "geoPoint.h"
#include "GeoPolyline.h"
#include "GeoPolygon.h"
#include "GeoAnotation.h"
class CGeoLayer  
{
private:
	//CArray<CGeoPoint,CGeoPoint>objs;
	//CArray<CGeoPolyline*,CGeoPolyline*>polys;
	CArray<CGeoObject *,CGeoObject *>objs;
public:
	void addObject(CGeoObject *obj);
	//void addObject(CGeoPolyline *polyline);
	void Draw(CDC *pDC);
	//void addObject(CGeoPoint pt);
	CGeoLayer();
	virtual ~CGeoLayer();

	// ͼ������
	CString name;
	// ͼ�㻭��
	CPen * pen;
	// ͼ�㻭ˢ
	CBrush * brush;
	void Clip(CRect rect);

	// ����ͶӰ�任����ͼ
	void Draw(CDC *pDC, CMapProjection * mapPrj);
};

#endif // !defined(AFX_GEOLAYER_H__C79B87B9_B91A_4880_B7DD_7A44CB0921E0__INCLUDED_)

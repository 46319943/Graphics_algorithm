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
	// ʹ�����ӷ����ƽ��
	void FillByFlood(CDC* pDC);
	// ��ʼ���ӵ�
	CPoint ctPt;
	// �������ʱƽ�����ɫ
	COLORREF color;

};


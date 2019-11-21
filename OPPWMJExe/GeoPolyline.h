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

	// ʹ����ֵ΢�ַ�����
	void DrawByDDA(CDC* pDC);
	// ���ص��Codeֵ
	int GetCode(CRect rect, CPoint pt);
	void Clip(CRect rect);
	// ���еĵ�
	CArray<CPoint, CPoint> clpPts;
	// �����������ߣ����ݵ�����������ö��λ����α���������
	void Bezier(CDC * pDC);
	// ��4���㻭3�α���������
	void Bezier3(CDC * pDC, CPoint p0, CPoint p1, CPoint p2, CPoint p3);
	// ��3���㻭2�α���������
	void Bezier2(CDC * pDC, CPoint p0, CPoint p1, CPoint p2);
	// ���ü��ĵ�
	void DrawClip(CDC * pDC);

	// ����ͶӰ�任����ͼ
	void Draw(CDC *pDC, CMapProjection * mapPrj);
};

#endif // !defined(AFX_GEOPOLYLINE_H__FF9631AB_314A_44E3_8D71_A48E919F423D__INCLUDED_)

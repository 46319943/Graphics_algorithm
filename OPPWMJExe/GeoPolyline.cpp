// GeoPolyline.cpp: implementation of the CGeoPolyline class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OPPWMJExe.h"
#include "GeoPolyline.h"

#include<iostream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGeoPolyline::CGeoPolyline()
{

}

CGeoPolyline::~CGeoPolyline()
{

}

void CGeoPolyline::addPoint(CPoint pt)
{
	pts.Add(pt);
}


void CGeoPolyline::Draw(CDC *pDC)
{
	// DrawByDDA(pDC);

	// �������е�������

	/*
	int size = pts.GetSize();
	for (int i = 0; i < size; i++)
	{
		if (i == 0) pDC->MoveTo(pts[i]);
		else pDC->LineTo(pts[i]);
	}
	*/

	Bezier(pDC);

	DrawClip(pDC);

	//pDC->Polyline(pts.GetData(),size);
}


// ʹ����ֵ΢�ַ�����
void CGeoPolyline::DrawByDDA(CDC* pDC)
{
	// һ���߾�ֻ�������㡣һ���һ�յ�
	float x = pts[0].x;
	float y = pts[0].y;
	float dx = pts[1].x - pts[0].x;
	float dy = pts[1].y - pts[0].y;

	// ȡ��ֵ
	int n = abs((int)dx) > abs((int)dy) ? abs((int)dx) : abs((int)dy);
	dx = dx / n;
	dy = dy / n;

	x = x + 650;

	for (int i = 0; i < n; i++) {
		pDC->SetPixel(x, y, RGB(255, 0, 0));
		x = x + dx;
		y = y + dy;
	}
}


// ���ص��Codeֵ
int CGeoPolyline::GetCode(CRect rect, CPoint pt)
{
	int code = 0;
	if (pt.x < rect.left) {
		code += 1;
	}
	else if (pt.x > rect.right) {
		code += 2;
	}
	if (pt.y < rect.bottom) {
		code += 4;
	}
	else if (pt.y > rect.top) {
		code += 8;
	}

	return code;
}


void CGeoPolyline::Clip(CRect rect)
{
	clpPts.RemoveAll();
	CPoint pt1, pt2;
	int x, y;
	int code1, code2, code;

	// ���geoPts�д��ڵ㣬��˵��ʹ����ͶӰ����Ӧ����geoPts�еĵ�
	CArray<CPoint, CPoint> * pts;
	pts = geoPts.GetSize() == 0 ? &(this->pts) : &geoPts;
	int size = pts->GetSize();

	for (int i = 0; i < size - 1; i++) {
		pt1 = (*pts)[i];
		pt2 = (*pts)[i + 1];

		code1 = GetCode(rect, pt1);
		code2 = GetCode(rect, pt2);

		// �� code1 & code != 0 ���ų����������ھ�������ͬһ�ߵ����
		while ((code1 & code2) == 0) {
			// �����㶼�ھ����ڲ�
			if (code1 == 0 & code2 == 0) {
				clpPts.Add(pt1);
				clpPts.Add(pt2);
				break;
			}
			// ��������ƶ�֮���ٴ��жϵ�������
			else if ((code1 & code2) != 0)
			{
				break;
			}
			// ���е���ƶ������ڱ���ĵ��������Ƶ����ϣ��Ӷ��ж����ڲ��ھ����ڲ�
			else
			{
				code = code1 != 0 ? code1 : code2;
				if ((code & 1) != 0) {
					x = rect.left;
					y = pt1.y + (pt2.y - pt1.y)*1.0 / (pt2.x - pt1.x) * (x - pt1.x);
				}
				if ((code & 2) != 0) {
					x = rect.right;
					y = pt1.y + (pt2.y - pt1.y)*1.0 / (pt2.x - pt1.x) * (x - pt1.x);
				}
				if ((code & 4) != 0) {
					y = rect.bottom;
					x = pt1.x + (pt2.x - pt1.x)*1.0 / (pt2.y - pt1.y) * (y - pt1.y);
				}
				if ((code & 8) != 0) {
					y = rect.top;
					x = pt1.x + (pt2.x - pt1.x)*1.0 / (pt2.y - pt1.y) * (y - pt1.y);
				}

				if (code == code1) {
					pt1 = CPoint(x, y);
					code1 = GetCode(rect, pt1);
				}
				else
				{
					pt2 = CPoint(x, y);
					code2 = GetCode(rect, pt2);
				}
			}
		}
	}

}

// ���ü��ĵ�
void CGeoPolyline::DrawClip(CDC * pDC)
{
	// ���ض�����ɫ����clpPts�ڲü���Χ֮�ڵĵ�
	int size = clpPts.GetSize();

	const COLORREF PEN_COLOR = RGB(255, 0, 0);
	CPen * newPen = new CPen(PS_SOLID, 1, PEN_COLOR);
	CPen * oldPen = pDC->SelectObject(newPen);


	for (int i = 0; i < size; i += 2) {
		pDC->MoveTo(clpPts[i]);
		pDC->LineTo(clpPts[i + 1]);
	}

	pDC->SelectObject(oldPen);

	// ע��һ��Ҫ�ͷŶ��е���Դ
	delete newPen;
}

void CGeoPolyline::Draw(CDC * pDC, CMapProjection * mapPrj)
{

	if (!geoPts.GetSize())
	{
		// ����γ��ת��Ϊƽ�����꣬����geoPts��
		double L, B;
		float x, y;
		int count = pts.GetSize();
		for (int i = 0; i < count; i++)
		{
			CPoint p = pts.GetAt(i);
			L = p.x;
			B = p.y;
			L = L / POINT_SCALE;
			B = B / POINT_SCALE;
			mapPrj->getXY(L, B, &x, &y);
			geoPts.Add(CPoint(x, y));
		}
	}

	int size = geoPts.GetSize();
	for (int i = 0; i < size; i++)
	{
		if (i == 0) pDC->MoveTo(geoPts[i]);
		else pDC->LineTo(geoPts[i]);
	}

	DrawClip(pDC);
}


// �����������ߣ����ݵ�����������ö��λ����α���������
void CGeoPolyline::Bezier(CDC * pDC)
{
	int size = pts.GetSize();

	// ��������ֻ��������Ļ�����Ҫ�Ȱѻ����Ƶ���һ�����λ��
	pDC->MoveTo(pts[0]);


	for (int i = 0; i < size - 3; i += 3) {
		Bezier3(pDC, pts[i], pts[i + 1], pts[i + 2], pts[i + 3]);
	}

	// �����α���������֮�󣬻���ʣ�¼�����
	if ((size % 3) == 2) {
		pDC->LineTo(pts[size - 1]);
	}
	else if ((size % 3) == 0) {
		Bezier2(pDC, pts[size - 3], pts[size - 2], pts[size - 1]);
	}
}


// ��4���㻭3�α���������
void CGeoPolyline::Bezier3(CDC * pDC, CPoint p0, CPoint p1, CPoint p2, CPoint p3)
{
	int x, y;
	float t, delt = 0.20;
	float dist = 0.0;

	dist += sqrt((p0.x - p1.x) * 1.0 * (p0.x - p1.x) + (p0.y - p1.y) * (p0.y - p1.y));
	dist += sqrt((p1.x - p2.x) * 1.0 * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	dist += sqrt((p2.x - p3.x) * 1.0 * (p2.x - p3.x) + (p2.y - p3.y) * (p2.y - p3.y));
	dist += sqrt((p0.x - p3.x) * 1.0 * (p0.x - p3.x) + (p0.y - p3.y) * (p0.y - p3.y));
	dist = dist / 2;

	CSize size1(3, 3);
	pDC->DPtoLP(&size1);
	if (dist != 0) {
		delt = size1.cx / dist;
	}
	else
	{
		delt = 0.5;
	}

	pDC->MoveTo(p0);
	for (t = delt; t <= 1.0; t = t + delt) {
		x = (1 - t)*(1 - t)*(1 - t)*p0.x + 3 * (1 - t)*(1 - t)*t*p1.x + 3 * (1 - t)*t*t*p2.x + t*t*t*p3.x;
		y = (1 - t)*(1 - t)*(1 - t)*p0.y + 3 * (1 - t)*(1 - t)*t*p1.y + 3 * (1 - t)*t*t*p2.y + t*t*t*p3.y;
		pDC->LineTo(x, y);
	}
	pDC->LineTo(p3);

}


void CGeoPolyline::Bezier2(CDC * pDC, CPoint p0, CPoint p1, CPoint p2)
{
	int x, y;
	float t, delt = 0.05;
	float dist = 0.0;
	pDC->MoveTo(p0);
	for (t = 0; t < 1.0; t = t + delt) {
		x = (1 - t)*(1 - t)*p0.x + 2 * (1 - t)*t*p1.x + t*t*p2.x;
		y = (1 - t)*(1 - t)*p0.y + 2 * (1 - t)*t*p1.y + t*t*p2.y;
		pDC->LineTo(x, y);
	}
	pDC->LineTo(p2);
}



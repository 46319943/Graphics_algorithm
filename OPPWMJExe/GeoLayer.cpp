// GeoLayer.cpp: implementation of the CGeoLayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OPPWMJExe.h"
#include "GeoLayer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGeoLayer::CGeoLayer()
{
	pen = NULL;
	brush = NULL;
}

CGeoLayer::~CGeoLayer()
{
	/*	int size = polys.GetSize();
		for(int i=0;i<size;i++)
		  delete polys.ElementAt(i);
		  */
	int size = objs.GetSize();
	for (int i = 0; i < size; i++)
		delete objs.ElementAt(i);
	delete pen;
	delete brush;
}
void CGeoLayer::addObject(CGeoObject *obj)
{
	objs.Add(obj);
}
/*
void CGeoLayer::addObject(CGeoPoint pt)
{
	objs.Add(pt);
}
*/
void CGeoLayer::Draw(CDC *pDC)
{
	/*int size = objs.GetSize();
	for(int i=0;i<size;i++)
	  objs[i].Draw(pDC);
	size = polys.GetSize();
	for(i=0;i<size;i++)
	  polys[i]->Draw(pDC);*/
	  // CPen * oldPen = pDC->GetCurrentPen();
	  // CBrush * oldBrush = pDC->GetCurrentBrush();
	CPen * oldPen;
	CBrush * oldBrush;
	if (pen) {
		oldPen = pDC->SelectObject(pen);
	}
	if (brush) {
		oldBrush = pDC->SelectObject(brush);
	}
	int size = objs.GetSize();
	for (int i = 0; i < size; i++) {
		objs[i]->Draw(pDC);
	}


	if (pen) {
		pDC->SelectObject(oldPen);
	}
	if (brush) {
		pDC->SelectObject(oldBrush);
	}


}
/*
void CGeoLayer::addObject(CGeoPolyline *polyline)
{
	polys.Add(polyline);
}
*/

void CGeoLayer::Clip(CRect rect)
{
	int size = objs.GetSize();
	for (int i = 0; i < size; i++) {
		objs[i]->Clip(rect);
	}
}

void CGeoLayer::Draw(CDC * pDC, CMapProjection * mapPrj)
{
	int size = objs.GetSize();
	for (int i = 0; i < size; i++) {
		objs[i]->Draw(pDC, mapPrj);
	}
}

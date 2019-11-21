#include "stdafx.h"
#include "GeoAnotation.h"

void CGeoAnotation::Draw(CDC *pDC)
{
	CFont font;
	font.CreatePointFont(300000, "ºÚÌå");
	pDC->SetBkMode(TRANSPARENT);
	pDC->SelectObject(font);
	pDC->TextOut(pt.x, pt.y, name);
	
	
}

void CGeoAnotation::setPoint(CPoint pt)
{
	this->pt = pt;
}

CGeoAnotation::CGeoAnotation()
{
}


CGeoAnotation::~CGeoAnotation()
{

}

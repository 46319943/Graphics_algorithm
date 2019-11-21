// GeoPoint.cpp: implementation of the CGeoPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OPPWMJExe.h"
#include "GeoPoint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGeoPoint::CGeoPoint()
{

}

CGeoPoint::CGeoPoint(double L, double B)
{
	this->L = L;
	this->B = B;
}

void CGeoPoint::getLB(double * L, double * B)
{
	*L = this->L;
	*B = this->B;
}

void CGeoPoint::setLB(double L, double B)
{
	this->L = L;
	this->B = B;
}

CGeoPoint::~CGeoPoint()
{

}

void CGeoPoint::Draw(CDC *pDC)
{
	pDC->SetPixel(pt.x,pt.y,RGB(255,0,0));
}

void CGeoPoint::setPoint(CPoint pt)
{
	this->pt = pt;
}

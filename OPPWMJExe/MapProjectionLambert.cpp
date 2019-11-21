#include "stdafx.h"
#include "MapProjectionLambert.h"


const double PI = 3.1415926;

CMapProjectionLambert::CMapProjectionLambert(float a) :CMapProjection(a)
{

}

CMapProjectionLambert::CMapProjectionLambert(float L0, float L1, float B0, float B1, float a) : CMapProjection(L0, L1, B0, B1, a)
{

}


CMapProjectionLambert::~CMapProjectionLambert()
{
}

void CMapProjectionLambert::getXY(float L, float B, float * x, float * y)
{
	*x = a * (L * PI /180);
	// *y = a * log(tan(PI / 4 + B / 180 * PI / 2));
	*y = a * log(tan(PI / 4 + B * PI / 360));
}

void CMapProjectionLambert::getLB(float x, float y, float * L, float * B)
{


}

void CMapProjectionLambert::Draw(CDC * pDC)
{
}

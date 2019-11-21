#pragma once
#include "MapProjection.h"
class CMapProjectionLambert :
	public CMapProjection
{
public:
	CMapProjectionLambert(float a = EARTH_RADIUS);
	CMapProjectionLambert(float L0, float L1, float B0, float B1, float a = EARTH_RADIUS);
	~CMapProjectionLambert();
	// ���ص�ͼͶӰ��XY����
	virtual void getXY(float L, float B, float *x, float *y);
	// ���ص�ǰXY����ϵ��L��B
	virtual void getLB(float x, float y, float *L, float *B);
	// ���ƾ�γ��
	virtual void Draw(CDC *pDC);
};


#pragma once
#include "MapProjection.h"
class CMapProjectionLambert :
	public CMapProjection
{
public:
	CMapProjectionLambert(float a = EARTH_RADIUS);
	CMapProjectionLambert(float L0, float L1, float B0, float B1, float a = EARTH_RADIUS);
	~CMapProjectionLambert();
	// 返回地图投影后XY坐标
	virtual void getXY(float L, float B, float *x, float *y);
	// 返回当前XY坐标系的L，B
	virtual void getLB(float x, float y, float *L, float *B);
	// 绘制经纬网
	virtual void Draw(CDC *pDC);
};


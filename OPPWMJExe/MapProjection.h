#pragma once

#include <math.h>

// 因为点类型只能保存int数据，所以在存经纬度的double时会丢失小数。所以把它乘以一个数之后再存
// #define POINT_SCALE 10000
const int POINT_SCALE = 10000;

const int EARTH_RADIUS = 6371000;

class CMapProjection
{
public:
	CMapProjection(float a);
	CMapProjection(float L0, float L1, float B0, float B1, float a);
	virtual ~CMapProjection();
	// 最小经度
	float L0;
	// 最大经度
	float L1;
	// 最小纬度
	float B0;
	// 最大纬度
	float B1;
	// 长半径
	float a;
	// 扁率
	float e;
	// 返回地图投影后XY坐标
	virtual void getXY(float L, float B, float *x, float *y)=0;
	// 返回当前XY坐标系的L，B
	virtual void getLB(float x, float y, float *L, float *B)=0;
	// 绘制经纬网
	virtual void Draw(CDC *pDC, double delta = 0.1, int interval = 5);
};


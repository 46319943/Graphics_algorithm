#pragma once

#include <math.h>

// ��Ϊ������ֻ�ܱ���int���ݣ������ڴ澭γ�ȵ�doubleʱ�ᶪʧС�������԰�������һ����֮���ٴ�
// #define POINT_SCALE 10000
const int POINT_SCALE = 10000;

const int EARTH_RADIUS = 6371000;

class CMapProjection
{
public:
	CMapProjection(float a);
	CMapProjection(float L0, float L1, float B0, float B1, float a);
	virtual ~CMapProjection();
	// ��С����
	float L0;
	// ��󾭶�
	float L1;
	// ��Сγ��
	float B0;
	// ���γ��
	float B1;
	// ���뾶
	float a;
	// ����
	float e;
	// ���ص�ͼͶӰ��XY����
	virtual void getXY(float L, float B, float *x, float *y)=0;
	// ���ص�ǰXY����ϵ��L��B
	virtual void getLB(float x, float y, float *L, float *B)=0;
	// ���ƾ�γ��
	virtual void Draw(CDC *pDC, double delta = 0.1, int interval = 5);
};


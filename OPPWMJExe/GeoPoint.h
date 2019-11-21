// GeoPoint.h: interface for the CGeoPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEOPOINT_H__286AAF88_14EE_48F6_AFDA_ECC5475E924F__INCLUDED_)
#define AFX_GEOPOINT_H__286AAF88_14EE_48F6_AFDA_ECC5475E924F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "geoObject.h"

class CGeoPoint :public CGeoObject
{
private:
	CPoint pt;
	// 经度
	double L;
	// 纬度
	double B;
public:
	void setPoint(CPoint pt);
	void Draw(CDC *pDC);
	CGeoPoint();

	// 根据经纬度生成点
	CGeoPoint(double L, double B);
	// 返回经纬度坐标
	void getLB(double * L, double * B);
	// 设置经纬度坐标
	void setLB(double L, double B);

	virtual ~CGeoPoint();

};

#endif // !defined(AFX_GEOPOINT_H__286AAF88_14EE_48F6_AFDA_ECC5475E924F__INCLUDED_)

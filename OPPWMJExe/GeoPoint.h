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
	// ����
	double L;
	// γ��
	double B;
public:
	void setPoint(CPoint pt);
	void Draw(CDC *pDC);
	CGeoPoint();

	// ���ݾ�γ�����ɵ�
	CGeoPoint(double L, double B);
	// ���ؾ�γ������
	void getLB(double * L, double * B);
	// ���þ�γ������
	void setLB(double L, double B);

	virtual ~CGeoPoint();

};

#endif // !defined(AFX_GEOPOINT_H__286AAF88_14EE_48F6_AFDA_ECC5475E924F__INCLUDED_)

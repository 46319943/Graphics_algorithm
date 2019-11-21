// GeoObject.h: interface for the CGeoObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEOOBJECT_H__4AEC010F_B660_4E9F_B27E_EE783720138B__INCLUDED_)
#define AFX_GEOOBJECT_H__4AEC010F_B660_4E9F_B27E_EE783720138B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MapProjection.h"

class CGeoObject  
{
public:
	
	virtual void Draw(CDC *pDC)=0;

	// 根据投影变换规则画图
	virtual void Draw(CDC *pDC, CMapProjection * mapPrj);

	CGeoObject();
	virtual ~CGeoObject();

	virtual void Clip(CRect rect)
	{
	}
};

#endif // !defined(AFX_GEOOBJECT_H__4AEC010F_B660_4E9F_B27E_EE783720138B__INCLUDED_)

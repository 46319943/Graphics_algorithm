// GeoMap.h: interface for the CGeoMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEOMAP_H__42D008B0_32C6_4117_9125_21B030AC491A__INCLUDED_)
#define AFX_GEOMAP_H__42D008B0_32C6_4117_9125_21B030AC491A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxtempl.h"
#include "geoLayer.h"
#include "atltypes.h"
#include "MapProjectionLambert.h"



class CGeoMap  
{
private:
	int mapScale;
	CString mapName;
	//int minx,miny,maxx,maxy;
	const int mapType;

	CArray<CGeoLayer *,CGeoLayer *>geoLayers;

public:
	void addLayer(CGeoLayer *layer);
	/*int getMapScale();
	void getMapScale(int &mapScale);
	void getMapScale(int *mapScale);
	void setMapScale(int mapScale);
	*/
	CGeoMap(CString mapName="",int mapScale=1);
	CGeoMap(const CGeoMap &map);
	virtual ~CGeoMap();

	// 地图的边界，也就是全图显示时的显示区域
	CRect wcRect;
	// 根据图层名获取图层
	CGeoLayer * getLayerByName(CString name);
	// 裁剪
	void Clip(CRect rect);
	// 根据投影变换规则画图
	void Draw(CDC *pDC, CMapProjection * mapPrj);
};

#endif // !defined(AFX_GEOMAP_H__42D008B0_32C6_4117_9125_21B030AC491A__INCLUDED_)

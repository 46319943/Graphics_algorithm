// GeoMap.cpp: implementation of the CGeoMap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OPPWMJExe.h"
#include "GeoMap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CGeoMap::CGeoMap(CString mapName1, int mapScale1) :mapType(1)
{
	wcRect = NULL;
	mapName = mapName1;
	mapScale = mapScale1;

}
CGeoMap::CGeoMap(const CGeoMap &map) :mapType(map.mapType)
{
	mapScale = map.mapScale;
	//mapType = map.mapType;
	//wcRect = map.wcRect;
	mapName = map.mapName;
	int size = map.geoLayers.GetSize();
	//
}

CGeoMap::~CGeoMap()
{
	int size = geoLayers.GetSize();
	for (int i = 0; i < size; i++)
		delete geoLayers.ElementAt(i);


}
/*
void CGeoMap::setMapScale(int mapScale)
{
	this->mapScale=mapScale;
	/*int a=getMapScale();
	int b;
	getMapScale(b);
	getMapScale(&b);

}

int CGeoMap::getMapScale()
{
	return mapScale;
}
void CGeoMap::getMapScale(int &mapScale)
{
	mapScale = this->mapScale;
}
void CGeoMap::getMapScale(int *mapScale)
{
	*mapScale = (this->mapScale);
}
*/
void CGeoMap::addLayer(CGeoLayer *layer)
{
	geoLayers.Add(layer);
}



// ����ͼ������ȡͼ��
CGeoLayer * CGeoMap::getLayerByName(CString name)
{
	int size = geoLayers.GetSize();
	for (int i = 0; i < size; i++) {
		// ����ͼ��Ƚ����ƣ���Ⱦͷ���
		if (name == geoLayers[i]->name) {
			return geoLayers[i];
		}
	}
	// ���û��ƥ�䣬�ͷ��ؿ�
	return NULL;
}


// �ü�
void CGeoMap::Clip(CRect rect)
{
	int size = geoLayers.GetSize();
	for (int i = 0; i < size; i++) {
		geoLayers[i]->Clip(rect);
	}

}

void CGeoMap::Draw(CDC * pDC, CMapProjection * mapPrj = NULL)
{
	int size = geoLayers.GetSize();

	if (mapPrj == NULL)
	{
		for (int i = 0; i < size; i++) {
			geoLayers[i]->Draw(pDC);
		}
		return;
	}

	for (int i = 0; i < size; i++) {
		geoLayers[i]->Draw(pDC, mapPrj);
	}
	mapPrj->Draw(pDC);
}

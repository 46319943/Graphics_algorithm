// OPPWMJExeView.cpp : implementation of the COPPWMJExeView class
//

#include "stdafx.h"
#include "OPPWMJExe.h"

#include "OPPWMJExeDoc.h"
#include "OPPWMJExeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COPPWMJExeView

IMPLEMENT_DYNCREATE(COPPWMJExeView, CView)

BEGIN_MESSAGE_MAP(COPPWMJExeView, CView)
	//{{AFX_MSG_MAP(COPPWMJExeView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ZOOM_IN, &COPPWMJExeView::OnZoomIn)
	ON_UPDATE_COMMAND_UI(ZOOM_IN, &COPPWMJExeView::OnUpdateZoomIn)
	ON_COMMAND(ZOOM_FULL, &COPPWMJExeView::OnZoomFull)
	ON_COMMAND(ID_FILE_NEW, &COPPWMJExeView::OnFileNew)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ZOOM_CLIP, &COPPWMJExeView::OnZoomClip)
	ON_UPDATE_COMMAND_UI(ZOOM_CLIP, &COPPWMJExeView::OnUpdateZoomClip)
	ON_WM_SIZE()
	ON_COMMAND(ZOOM_MOVE, &COPPWMJExeView::OnZoomMove)
	ON_UPDATE_COMMAND_UI(ZOOM_MOVE, &COPPWMJExeView::OnUpdateZoomMove)
	ON_COMMAND(ZOOM_TRANS, &COPPWMJExeView::OnZoomTrans)
	ON_UPDATE_COMMAND_UI(ZOOM_TRANS, &COPPWMJExeView::OnUpdateZoomTrans)
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COPPWMJExeView construction/destruction

COPPWMJExeView::COPPWMJExeView()
	: isMapLoaded(false)
	, mouseState(MOUSE_ZOOM_NONE)
	, hasMouseLeftPressed(false)
	, mouseDownPoint(0)
	, mouseUpPoint(0)
	, mouseMovePoint(0)
	, dcMen(NULL)
	, projection(NULL)
{
	// TODO: add construction code here
	//int a  =map.mapScale;
	map = NULL;

}

COPPWMJExeView::~COPPWMJExeView()
{
	if (map != NULL)
		delete map;
	if (dcMen != NULL) {
		dcMen->DeleteDC();
		bmp.DeleteObject();
		delete dcMen;
	}
}

BOOL COPPWMJExeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COPPWMJExeView drawing

void COPPWMJExeView::OnDraw(CDC* pDC)
{
	COPPWMJExeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if (map == NULL)
		return;

	CRect rect;
	GetClientRect(&rect);
	if (dcMen == NULL) {
		dcMen = new CDC();
		dcMen->CreateCompatibleDC(pDC);
		bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
		dcMen->SelectObject(&bmp);
	}
	pDC->DPtoLP(&rect);
	OnPrepareDC(dcMen);
	dcMen->FillSolidRect(rect, pDC->GetBkColor());

	// map->Draw(dcMen);
	map->Draw(dcMen, this->projection);

	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), dcMen, rect.left, rect.top, SRCCOPY);


	//map->Draw(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// COPPWMJExeView printing

BOOL COPPWMJExeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COPPWMJExeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COPPWMJExeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COPPWMJExeView diagnostics

#ifdef _DEBUG
void COPPWMJExeView::AssertValid() const
{
	CView::AssertValid();
}

void COPPWMJExeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COPPWMJExeDoc* COPPWMJExeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COPPWMJExeDoc)));
	return (COPPWMJExeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COPPWMJExeView message handlers

void COPPWMJExeView::OnFileOpen()
{
	// TODO: Add your command handler code here
	CFileDialog fDlg(true);
	if (fDlg.DoModal() != IDOK) return;
	CString fileName = fDlg.GetPathName();
	FILE *fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		MessageBox("File Open Failed!");
		return;
	}
	if (fileName.Right(9) == "wuhan.txt") //读取武汉线状
		readWHData(fp);
	else if (fileName.Right(10) == "china1.txt")
		readCHData(fp);
	else if (fileName.Right(10) == "china1.dat")
		readCH1Data(fp);
	else if (fileName.Find("chnFillTest.txt") != -1)
		readCFTData(fp);
	else if (fileName.Find("clipData.txt") != -1)
		readCPData(fp);
	else if (fileName.Find(".mif") != -1)
		readMIFData(fp);

	fclose(fp);
	Invalidate();
}

void COPPWMJExeView::readWHData(FILE *fp)
{
	int x1, y1, x2, y2;
	if (map != NULL)
		delete map;
	map = new CGeoMap();
	CGeoLayer *layer = new CGeoLayer;
	map->addLayer(layer);
	while (!feof(fp))
	{
		CGeoObject *obj = new CGeoPolyline;
		fscanf(fp, "%d%d%d%d", &x1, &y1, &x2, &y2);
		x1 = x1;
		x2 = x2;
		((CGeoPolyline*)obj)->addPoint(CPoint(x1, y1));
		((CGeoPolyline*)obj)->addPoint(CPoint(x2, y2));
		layer->addObject(obj);
	}
}

void COPPWMJExeView::readCHData(FILE *fp)
{
	int x, y;
	if (map != NULL)
		delete map;
	map = new CGeoMap();
	CGeoLayer *layer = new CGeoLayer;
	map->addLayer(layer);
	while (!feof(fp))
	{
		CGeoObject *obj = new CGeoPoint;
		fscanf(fp, "%d%d", &x, &y);
		((CGeoPoint *)obj)->setPoint(CPoint(x, y));
		layer->addObject(obj);
	}
}
//
void COPPWMJExeView::readCH1Data(FILE *fp)
{
	isMapLoaded = true;
	// 地图显示区域点
	int xMin, xMax, yMin, yMax;
	// 图层的数量
	int layerCount;
	int x, y;
	// 删除并创建地图
	if (map != NULL)
		delete map;
	map = new CGeoMap();


	// 读取地图显示的范围
	fscanf(fp, "%d,%d%d,%d", &xMin, &yMax, &xMax, &yMin);
	// 创建一个显示矩形
	CRect wcRect = CRect(xMin, yMax, xMax, yMin);
	// 设置地图的显示区域
	map->wcRect = wcRect;
	// 将窗口显示区域设置成地图区域，即显示全图
	this->wcRect = wcRect;
	// 读取图层数量
	fscanf(fp, "%d", &layerCount);


	// 读取图层
	for (int i = 0; i < layerCount; i++) {
		// 图层名字长度
		int nameLenght;
		fscanf(fp, "%d", &nameLenght);
		// 图层名字
		char name[20];
		fscanf(fp, "%s", name);
		// 转为CString类型
		CString str;
		str.Format("%s", name);

		// 创建并添加图层
		CGeoLayer * layer = new CGeoLayer();
		layer->name = str;
		map->addLayer(layer);


		// 目标数量
		int objectCount;
		fscanf(fp, "%d", &objectCount);
		// 读取目标
		for (int j = 0; j < objectCount; j++) {
			// 目标类型
			int objectType;
			fscanf(fp, "%d", &objectType);
			// 根据目标类型创建并添加一个目标
			if (objectType == 2) {
				CGeoPolygon * polygon = new CGeoPolygon();
				layer->addObject(polygon);
				while (true)
				{
					// 读取一个点
					fscanf(fp, "%d,%d", &x, &y);
					// 如果结束就跳出
					if (x == -99999 && y == -99999) {
						break;
					}
					// 创建点
					CPoint point = CPoint(x, y);
					// 添加点到面目标中
					polygon->addPoint(point);
				}

			}
			else if (objectType == 1) {
				CGeoPolyline * polyline = new CGeoPolyline();
				layer->addObject(polyline);
				while (true)
				{
					fscanf(fp, "%d,%d", &x, &y);
					if (x == -99999 && y == -99999) {
						break;
					}
					CPoint point = CPoint(x, y);
					polyline->addPoint(point);
				}
			}
		}
	}
	readOption();
	readAnotation();
}

// 根据成员wcRect来进行坐标变化
void COPPWMJExeView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class

	//添加一个bool变量，控制是否是最新需要变换的这个数据加载，如果没有加载，则不需要坐标变换
	if (!isMapLoaded)
		return;
	CSize size;
	CPoint pt;
	CRect rectD;

	this->GetClientRect(&rectD);//取得客户区矩形区域大小
	size = rectD.Size();
	pt = rectD.CenterPoint();//取得客户区矩形区域中心点坐标

	pDC->SetMapMode(MM_ISOTROPIC); //设置指定设备环境的映射方式
	pDC->SetViewportExt(size);  //设定视口尺寸
	pDC->SetViewportOrg(pt); //设置视口中心为坐标系原点

	size = wcRect.Size();  //设定窗口对应尺寸
	pt = wcRect.CenterPoint(); //设置窗口中心为对应原点

	pDC->SetWindowExt(size);   //设置窗口长宽
	pDC->SetWindowOrg(pt);	//设置窗口原点

	CView::OnPrepareDC(pDC, pInfo);
}


// 读取图层信息
void COPPWMJExeView::readOption()
{
	CFileDialog fDlg(true);
	if (fDlg.DoModal() != IDOK) return;
	CString fileName = fDlg.GetPathName();
	FILE *fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		MessageBox("File Open Failed!");
		return;
	}
	if (fileName.Right(10) != "china1.opt")
		return;

	int layerCount;
	fscanf(fp, "%d", &layerCount);
	for (int i = 0; i < layerCount; i++) {
		char name[20];
		fscanf(fp, "%s", name);
		CString str;
		str.Format("%s", name);

		CGeoLayer * layer = map->getLayerByName(str);
		if (layer == NULL) {
			return;
		}
		int hasPen, hasBrush;
		fscanf(fp, "%d", &hasPen);
		if (hasPen) {
			float width;
			int R, G, B;
			fscanf(fp, "%f", &width);
			fscanf(fp, "%d, %d, %d", &R, &G, &B);
			CPen * pen = new CPen(PS_SOLID, width, RGB(R, G, B));
			layer->pen = pen;
		}
		fscanf(fp, "%d", &hasBrush);
		if (hasBrush) {
			int R, G, B;
			fscanf(fp, "%d, %d, %d", &R, &G, &B);
			CBrush * brush = new CBrush(RGB(R, G, B));
			layer->brush = brush;
		}
	}
}


void COPPWMJExeView::OnZoomIn()
{
	// TODO: 在此添加命令处理程序代码

	mouseState = mouseState == MOUSE_ZOOM_IN ? MOUSE_ZOOM_NONE : MOUSE_ZOOM_IN;
}


void COPPWMJExeView::OnUpdateZoomIn(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mouseState == MOUSE_ZOOM_IN);

}


void COPPWMJExeView::OnZoomFull()
{
	// TODO: 在此添加命令处理程序代码
	wcRect = map->wcRect;
	Invalidate();
}


void COPPWMJExeView::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
	if (map != NULL) {
		delete map;
	}
	map = new CGeoMap;

	Invalidate();
}


void COPPWMJExeView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (hasMouseLeftPressed) {
		// 画出临时选择的矩形框

		CDC * dc = GetDC();
		// 设置绘制模式
		dc->SetROP2(R2_NOTXORPEN);
		// 擦掉上一个矩形
		dc->Rectangle(mouseDownPoint.x, mouseDownPoint.y, mouseMovePoint.x, mouseMovePoint.y);
		// 画新的矩形
		dc->Rectangle(mouseDownPoint.x, mouseDownPoint.y, point.x, point.y);

		if (mouseState == MOUSE_ZOOM_TRANS) {
			OnPrepareDC(dc);
			CPoint originPoint(mouseMovePoint), newPoint(point);
			dc->DPtoLP(&originPoint);
			dc->DPtoLP(&newPoint);
			this->wcRect.OffsetRect(originPoint - newPoint);
			Invalidate();
		}

		if (mouseState == MOUSE_ZOOM_MOVE) {
			OnPrepareDC(dc);

			CRect rect;
			GetClientRect(&rect);
			int width = rect.Width();
			int height = rect.Height();

			CPoint pt2(point), pt1(mouseDownPoint), p2(pt2), p1(pt1);
			dc->DPtoLP(&p2);
			dc->DPtoLP(&p1);
			CPoint p = p2 - p1;

			dc->DPtoLP(&rect);
			dc->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), dcMen, rect.left - p.x, rect.top - p.y, SRCCOPY);

			CRect rect1;
			if (p.x > 0) {
				rect1 = CRect(0, 0, pt2.x - pt1.x, height);
			}
			else
			{
				rect1 = CRect(width + (pt2.x - pt1.x), 0, width, height);
			}
			dc->DPtoLP(&rect1);
			dc->FillSolidRect(rect1, dc->GetBkColor());

			if (p.y > 0) {
				rect1 = CRect(0, height + (pt2.y - pt1.y), width, height);
			}
			else
			{
				rect1 = CRect(0, 0, width, pt2.y - pt1.y);
			}
			dc->DPtoLP(&rect1);
			dc->FillSolidRect(rect1, dc->GetBkColor());

			pt2 = point;
		}

	}
	mouseMovePoint = point;

	CView::OnMouseMove(nFlags, point);
}


void COPPWMJExeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	hasMouseLeftPressed = true;
	mouseDownPoint = point;
	mouseMovePoint = point;
	CView::OnLButtonDown(nFlags, point);
}


void COPPWMJExeView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	hasMouseLeftPressed = false;
	mouseUpPoint = point;

	CDC * dc = GetDC();

	// 坐标转换
	OnPrepareDC(dc);

	// 坐标转换。将窗口点转换到地图点
	dc->DPtoLP(&mouseDownPoint);
	dc->DPtoLP(&mouseUpPoint);

	// 获取选择的矩形
	int left, right, top, bottom;
	left = mouseDownPoint.x >= mouseUpPoint.x ? mouseUpPoint.x : mouseDownPoint.x;
	right = mouseDownPoint.x >= mouseUpPoint.x ? mouseDownPoint.x : mouseUpPoint.x;
	top = mouseDownPoint.y >= mouseUpPoint.y ? mouseUpPoint.y : mouseDownPoint.y;
	bottom = mouseDownPoint.y >= mouseUpPoint.y ? mouseDownPoint.y : mouseUpPoint.y;

	CRect wcRect = CRect(left, bottom, right, top);

	if (mouseState == MOUSE_ZOOM_IN) {
		this->wcRect = wcRect;
		Invalidate();
	}
	else if (mouseState == MOUSE_ZOOM_CLIP)
	{
		map->Clip(wcRect);
		Invalidate();
	}
	else if (mouseState == MOUSE_ZOOM_MOVE)
	{
		this->wcRect.OffsetRect(mouseDownPoint - mouseUpPoint);
		Invalidate();
	}
	else if (mouseState == MOUSE_ZOOM_TRANS)
	{
		//Invalidate();
	}
	else
	{
		dc->SetROP2(R2_NOTXORPEN);
		dc->Rectangle(mouseDownPoint.x, mouseDownPoint.y, mouseUpPoint.x, mouseUpPoint.y);
	}

	CView::OnLButtonUp(nFlags, point);
}


// 读取注记
void COPPWMJExeView::readAnotation()
{
	CFileDialog fDlg(true);
	if (fDlg.DoModal() != IDOK) return;
	CString fileName = fDlg.GetPathName();
	FILE *fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		MessageBox("File Open Failed!");
		return;
	}
	if (fileName.Right(11) != "chnCity.txt")
		return;


	CGeoLayer * layer = new CGeoLayer;
	map->addLayer(layer);
	while (!feof(fp))
	{
		char name[20];
		CString str;
		int x, y;
		fscanf(fp, "%s %d %d", name, &x, &y);
		str.Format("%s", name);

		CGeoAnotation * anotation = new CGeoAnotation;
		anotation->setPoint(CPoint(x, y));
		anotation->name = str;
		layer->addObject(anotation);
	}

}


// 读取种子点填充的数据
void COPPWMJExeView::readCFTData(FILE* fp)
{
	if (map != NULL)
		delete map;
	map = new CGeoMap();
	CGeoLayer *layer = new CGeoLayer;
	map->addLayer(layer);

	// 读取到文件末尾就结束
	while (!feof(fp))
	{
		// 读取绘图单位中存在的图形数量
		int unit;
		fscanf(fp, "%d", &unit);
		CArray<CGeoPolygon *, CGeoPolygon *> polygons;
		for (int i = 0; i < unit; i++) {
			CGeoPolygon * polygon = new CGeoPolygon();
			layer->addObject(polygon);
			polygons.Add(polygon);

			// 边的点的数量
			int count;
			fscanf(fp, "%d", &count);
			for (int j = 0; j < count; j++) {
				// 读取点，并且添加到图层中
				int x, y;
				fscanf(fp, "%d%d", &x, &y);
				polygon->addPoint(CPoint(x, y));
			}

		}
		// 种子点
		int seedX, seedY;
		fscanf(fp, "%d%d", &seedX, &seedY);

		// 最后读取颜色
		int color;
		fscanf(fp, "%d", &color);

		for (int i = 0; i < polygons.GetSize(); i++) {
			polygons.GetAt(i)->ctPt = CPoint(seedX, seedY);
			polygons.GetAt(i)->color = color;
		}



	}
}


// 读取裁剪数据
void COPPWMJExeView::readCPData(FILE * fp)
{
	isMapLoaded = true;
	// 地图显示区域点
	int xMin, xMax, yMin, yMax;
	// 图层的数量
	// 删除并创建地图
	if (map != NULL)
		delete map;
	map = new CGeoMap();

	// 读取地图显示的范围
	fscanf(fp, "%d%d%d%d", &xMin, &yMax, &xMax, &yMin);
	// 创建一个显示矩形
	CRect wcRect = new CRect(xMin, yMax, xMax, yMin);
	// 设置地图的显示区域
	map->wcRect = wcRect;
	// 将窗口显示区域设置成地图区域，即显示全图
	this->wcRect = wcRect;

	CGeoLayer *layer = new CGeoLayer;
	map->addLayer(layer);

	// 读取到文件末尾就结束
	while (!feof(fp))
	{
		CGeoPolyline * polyline = new CGeoPolyline();
		layer->addObject(polyline);
		// 读取绘图单位中存在的图形数量
		int unit;
		fscanf(fp, "%d", &unit);
		for (int i = 0; i < unit; i++) {

			// 读取点，并且添加到线状要素中
			int x, y;
			fscanf(fp, "%d%d", &x, &y);
			polyline->addPoint(CPoint(x, y));
		}
	}

}


// 读取经纬度表示的MIF数据
void COPPWMJExeView::readMIFData(FILE * fp)
{
	isMapLoaded = true;
	// 删除并创建地图
	if (map != NULL)
		delete map;
	map = new CGeoMap();

	// 创建图层
	CGeoLayer *layer = new CGeoLayer;
	map->addLayer(layer);

	// 读取文件中的区域Bounds
	float x1, x2, y1, y2;
	while (true)
	{
		// 字符串缓冲区
		char chs[1024];
		fscanf(fp, "%s", chs);
		// 将char[]转为CString从而进行字符串比较
		CString str;
		str.Format("%s", chs);
		// 没有读取到Bounds就一直读
		if (str.Find("Bounds") == -1) {
			continue;
		}
		// Bounds之后就到范围了
		// 注意有个空格。因为只是%s的话，会跳过空白字符。而自己写字符串，不会跳过
		fscanf(fp, " (%f,%f)", &x1, &y1);
		fscanf(fp, " (%f,%f)", &x2, &y2);
		// 读取完之后跳出循环
		break;
	}

	// 左下点 右上点
	this->projection = new CMapProjectionLambert(x1, x2, y1, y2);

	// 根据经纬度范围获取坐标范围
	float x1_, x2_, y1_, y2_;
	this->projection->getXY(x1, y1, &x1_, &y1_);
	this->projection->getXY(x2, y2, &x2_, &y2_);

	// 创建地图区域 top是y坐标大的那个
	CRect r = CRect(x1_, y2_, x2_, y1_);
	// 设置地图边界
	map->wcRect = r;
	// 设置显示区域
	this->wcRect = r;

	// 将指针移动到DATA区
	while (true)
	{
		// 字符串缓冲区
		char chs[1024];
		fscanf(fp, "%s", chs);
		// 将char[]转为CString从而进行字符串比较
		CString str;
		str.Format("%s", chs);
		// 没有读取到DATA就一直读
		if (str.Find("DATA") == -1) {
			continue;
		}
		// 读取到DATA之后说明已经到了，跳出循环
		break;
	}
	// 到数据域之后就一直读
	while (!feof(fp))
	{
		// 字符串缓冲区
		char chs[1024];
		fscanf(fp, "%s", chs);
		// 将char[]转为CString从而进行字符串比较
		CString str;
		str.Format("%s", chs);

		if (str.Find("PLINE") == 0) {
			CGeoPolyline * polyline = new CGeoPolyline();
			layer->addObject(polyline);
			// 线状要素的点数
			int count;
			fscanf(fp, "%d", &count);
			// 点坐标
			float x, y;
			for (int i = 0; i < count; i++)
			{
				fscanf(fp, "%f%f", &x, &y);
				polyline->addPoint(CPoint(x * POINT_SCALE, y * POINT_SCALE));
			}

		}
		else if (str.Find("LINE") == 0)
		{
			fscanf(fp, "%f%f%f%f", &x1, &y1, &x2, &y2);
			CGeoPolyline * polyline = new CGeoPolyline();
			layer->addObject(polyline);
			polyline->addPoint(CPoint(x1 * POINT_SCALE, y1 * POINT_SCALE));
			polyline->addPoint(CPoint(x2 * POINT_SCALE, y2 * POINT_SCALE));

		}

	}

}


void COPPWMJExeView::OnZoomClip()
{
	// TODO: 在此添加命令处理程序代码
	mouseState = mouseState == MOUSE_ZOOM_CLIP ? MOUSE_ZOOM_NONE : MOUSE_ZOOM_CLIP;
}


void COPPWMJExeView::OnUpdateZoomClip(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mouseState == MOUSE_ZOOM_CLIP);
}


void COPPWMJExeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (dcMen != NULL) {
		bmp.DeleteObject();
		CRect rect;
		GetClientRect(&rect);
		CDC *pDc = this->GetDC();
		bmp.CreateCompatibleBitmap(pDc, rect.Width(), rect.Height());
		dcMen->SelectObject(&bmp);
	}
}


void COPPWMJExeView::OnZoomMove()
{
	// TODO: 在此添加命令处理程序代码
	mouseState = mouseState == MOUSE_ZOOM_MOVE ? MOUSE_ZOOM_NONE : MOUSE_ZOOM_MOVE;
}


void COPPWMJExeView::OnUpdateZoomMove(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mouseState == MOUSE_ZOOM_MOVE);
}


void COPPWMJExeView::OnZoomTrans()
{
	// TODO: 在此添加命令处理程序代码
	mouseState = mouseState == MOUSE_ZOOM_TRANS ? MOUSE_ZOOM_NONE : MOUSE_ZOOM_TRANS;
}


void COPPWMJExeView::OnUpdateZoomTrans(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mouseState == MOUSE_ZOOM_TRANS);
}




BOOL COPPWMJExeView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 上滚，放大，缩小矩形
	if (zDelta > 0) {
		this->wcRect.DeflateRect(wcRect.Width()*0.1, wcRect.Height()*0.1);
	}
	else if (zDelta < 0) {
		this->wcRect.InflateRect(wcRect.Width()*0.1, wcRect.Height()*0.1);
	}
	Invalidate();


	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

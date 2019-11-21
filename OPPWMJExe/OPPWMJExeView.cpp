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
	if (fileName.Right(9) == "wuhan.txt") //��ȡ�人��״
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
	// ��ͼ��ʾ�����
	int xMin, xMax, yMin, yMax;
	// ͼ�������
	int layerCount;
	int x, y;
	// ɾ����������ͼ
	if (map != NULL)
		delete map;
	map = new CGeoMap();


	// ��ȡ��ͼ��ʾ�ķ�Χ
	fscanf(fp, "%d,%d%d,%d", &xMin, &yMax, &xMax, &yMin);
	// ����һ����ʾ����
	CRect wcRect = CRect(xMin, yMax, xMax, yMin);
	// ���õ�ͼ����ʾ����
	map->wcRect = wcRect;
	// ��������ʾ�������óɵ�ͼ���򣬼���ʾȫͼ
	this->wcRect = wcRect;
	// ��ȡͼ������
	fscanf(fp, "%d", &layerCount);


	// ��ȡͼ��
	for (int i = 0; i < layerCount; i++) {
		// ͼ�����ֳ���
		int nameLenght;
		fscanf(fp, "%d", &nameLenght);
		// ͼ������
		char name[20];
		fscanf(fp, "%s", name);
		// תΪCString����
		CString str;
		str.Format("%s", name);

		// ���������ͼ��
		CGeoLayer * layer = new CGeoLayer();
		layer->name = str;
		map->addLayer(layer);


		// Ŀ������
		int objectCount;
		fscanf(fp, "%d", &objectCount);
		// ��ȡĿ��
		for (int j = 0; j < objectCount; j++) {
			// Ŀ������
			int objectType;
			fscanf(fp, "%d", &objectType);
			// ����Ŀ�����ʹ��������һ��Ŀ��
			if (objectType == 2) {
				CGeoPolygon * polygon = new CGeoPolygon();
				layer->addObject(polygon);
				while (true)
				{
					// ��ȡһ����
					fscanf(fp, "%d,%d", &x, &y);
					// �������������
					if (x == -99999 && y == -99999) {
						break;
					}
					// ������
					CPoint point = CPoint(x, y);
					// ��ӵ㵽��Ŀ����
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

// ���ݳ�ԱwcRect����������仯
void COPPWMJExeView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class

	//���һ��bool�����������Ƿ���������Ҫ�任��������ݼ��أ����û�м��أ�����Ҫ����任
	if (!isMapLoaded)
		return;
	CSize size;
	CPoint pt;
	CRect rectD;

	this->GetClientRect(&rectD);//ȡ�ÿͻ������������С
	size = rectD.Size();
	pt = rectD.CenterPoint();//ȡ�ÿͻ��������������ĵ�����

	pDC->SetMapMode(MM_ISOTROPIC); //����ָ���豸������ӳ�䷽ʽ
	pDC->SetViewportExt(size);  //�趨�ӿڳߴ�
	pDC->SetViewportOrg(pt); //�����ӿ�����Ϊ����ϵԭ��

	size = wcRect.Size();  //�趨���ڶ�Ӧ�ߴ�
	pt = wcRect.CenterPoint(); //���ô�������Ϊ��Ӧԭ��

	pDC->SetWindowExt(size);   //���ô��ڳ���
	pDC->SetWindowOrg(pt);	//���ô���ԭ��

	CView::OnPrepareDC(pDC, pInfo);
}


// ��ȡͼ����Ϣ
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
	// TODO: �ڴ���������������

	mouseState = mouseState == MOUSE_ZOOM_IN ? MOUSE_ZOOM_NONE : MOUSE_ZOOM_IN;
}


void COPPWMJExeView::OnUpdateZoomIn(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(mouseState == MOUSE_ZOOM_IN);

}


void COPPWMJExeView::OnZoomFull()
{
	// TODO: �ڴ���������������
	wcRect = map->wcRect;
	Invalidate();
}


void COPPWMJExeView::OnFileNew()
{
	// TODO: �ڴ���������������
	if (map != NULL) {
		delete map;
	}
	map = new CGeoMap;

	Invalidate();
}


void COPPWMJExeView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (hasMouseLeftPressed) {
		// ������ʱѡ��ľ��ο�

		CDC * dc = GetDC();
		// ���û���ģʽ
		dc->SetROP2(R2_NOTXORPEN);
		// ������һ������
		dc->Rectangle(mouseDownPoint.x, mouseDownPoint.y, mouseMovePoint.x, mouseMovePoint.y);
		// ���µľ���
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	hasMouseLeftPressed = true;
	mouseDownPoint = point;
	mouseMovePoint = point;
	CView::OnLButtonDown(nFlags, point);
}


void COPPWMJExeView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	hasMouseLeftPressed = false;
	mouseUpPoint = point;

	CDC * dc = GetDC();

	// ����ת��
	OnPrepareDC(dc);

	// ����ת���������ڵ�ת������ͼ��
	dc->DPtoLP(&mouseDownPoint);
	dc->DPtoLP(&mouseUpPoint);

	// ��ȡѡ��ľ���
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


// ��ȡע��
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


// ��ȡ���ӵ���������
void COPPWMJExeView::readCFTData(FILE* fp)
{
	if (map != NULL)
		delete map;
	map = new CGeoMap();
	CGeoLayer *layer = new CGeoLayer;
	map->addLayer(layer);

	// ��ȡ���ļ�ĩβ�ͽ���
	while (!feof(fp))
	{
		// ��ȡ��ͼ��λ�д��ڵ�ͼ������
		int unit;
		fscanf(fp, "%d", &unit);
		CArray<CGeoPolygon *, CGeoPolygon *> polygons;
		for (int i = 0; i < unit; i++) {
			CGeoPolygon * polygon = new CGeoPolygon();
			layer->addObject(polygon);
			polygons.Add(polygon);

			// �ߵĵ������
			int count;
			fscanf(fp, "%d", &count);
			for (int j = 0; j < count; j++) {
				// ��ȡ�㣬������ӵ�ͼ����
				int x, y;
				fscanf(fp, "%d%d", &x, &y);
				polygon->addPoint(CPoint(x, y));
			}

		}
		// ���ӵ�
		int seedX, seedY;
		fscanf(fp, "%d%d", &seedX, &seedY);

		// ����ȡ��ɫ
		int color;
		fscanf(fp, "%d", &color);

		for (int i = 0; i < polygons.GetSize(); i++) {
			polygons.GetAt(i)->ctPt = CPoint(seedX, seedY);
			polygons.GetAt(i)->color = color;
		}



	}
}


// ��ȡ�ü�����
void COPPWMJExeView::readCPData(FILE * fp)
{
	isMapLoaded = true;
	// ��ͼ��ʾ�����
	int xMin, xMax, yMin, yMax;
	// ͼ�������
	// ɾ����������ͼ
	if (map != NULL)
		delete map;
	map = new CGeoMap();

	// ��ȡ��ͼ��ʾ�ķ�Χ
	fscanf(fp, "%d%d%d%d", &xMin, &yMax, &xMax, &yMin);
	// ����һ����ʾ����
	CRect wcRect = new CRect(xMin, yMax, xMax, yMin);
	// ���õ�ͼ����ʾ����
	map->wcRect = wcRect;
	// ��������ʾ�������óɵ�ͼ���򣬼���ʾȫͼ
	this->wcRect = wcRect;

	CGeoLayer *layer = new CGeoLayer;
	map->addLayer(layer);

	// ��ȡ���ļ�ĩβ�ͽ���
	while (!feof(fp))
	{
		CGeoPolyline * polyline = new CGeoPolyline();
		layer->addObject(polyline);
		// ��ȡ��ͼ��λ�д��ڵ�ͼ������
		int unit;
		fscanf(fp, "%d", &unit);
		for (int i = 0; i < unit; i++) {

			// ��ȡ�㣬������ӵ���״Ҫ����
			int x, y;
			fscanf(fp, "%d%d", &x, &y);
			polyline->addPoint(CPoint(x, y));
		}
	}

}


// ��ȡ��γ�ȱ�ʾ��MIF����
void COPPWMJExeView::readMIFData(FILE * fp)
{
	isMapLoaded = true;
	// ɾ����������ͼ
	if (map != NULL)
		delete map;
	map = new CGeoMap();

	// ����ͼ��
	CGeoLayer *layer = new CGeoLayer;
	map->addLayer(layer);

	// ��ȡ�ļ��е�����Bounds
	float x1, x2, y1, y2;
	while (true)
	{
		// �ַ���������
		char chs[1024];
		fscanf(fp, "%s", chs);
		// ��char[]תΪCString�Ӷ������ַ����Ƚ�
		CString str;
		str.Format("%s", chs);
		// û�ж�ȡ��Bounds��һֱ��
		if (str.Find("Bounds") == -1) {
			continue;
		}
		// Bounds֮��͵���Χ��
		// ע���и��ո���Ϊֻ��%s�Ļ����������հ��ַ������Լ�д�ַ�������������
		fscanf(fp, " (%f,%f)", &x1, &y1);
		fscanf(fp, " (%f,%f)", &x2, &y2);
		// ��ȡ��֮������ѭ��
		break;
	}

	// ���µ� ���ϵ�
	this->projection = new CMapProjectionLambert(x1, x2, y1, y2);

	// ���ݾ�γ�ȷ�Χ��ȡ���귶Χ
	float x1_, x2_, y1_, y2_;
	this->projection->getXY(x1, y1, &x1_, &y1_);
	this->projection->getXY(x2, y2, &x2_, &y2_);

	// ������ͼ���� top��y�������Ǹ�
	CRect r = CRect(x1_, y2_, x2_, y1_);
	// ���õ�ͼ�߽�
	map->wcRect = r;
	// ������ʾ����
	this->wcRect = r;

	// ��ָ���ƶ���DATA��
	while (true)
	{
		// �ַ���������
		char chs[1024];
		fscanf(fp, "%s", chs);
		// ��char[]תΪCString�Ӷ������ַ����Ƚ�
		CString str;
		str.Format("%s", chs);
		// û�ж�ȡ��DATA��һֱ��
		if (str.Find("DATA") == -1) {
			continue;
		}
		// ��ȡ��DATA֮��˵���Ѿ����ˣ�����ѭ��
		break;
	}
	// ��������֮���һֱ��
	while (!feof(fp))
	{
		// �ַ���������
		char chs[1024];
		fscanf(fp, "%s", chs);
		// ��char[]תΪCString�Ӷ������ַ����Ƚ�
		CString str;
		str.Format("%s", chs);

		if (str.Find("PLINE") == 0) {
			CGeoPolyline * polyline = new CGeoPolyline();
			layer->addObject(polyline);
			// ��״Ҫ�صĵ���
			int count;
			fscanf(fp, "%d", &count);
			// ������
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
	// TODO: �ڴ���������������
	mouseState = mouseState == MOUSE_ZOOM_CLIP ? MOUSE_ZOOM_NONE : MOUSE_ZOOM_CLIP;
}


void COPPWMJExeView::OnUpdateZoomClip(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(mouseState == MOUSE_ZOOM_CLIP);
}


void COPPWMJExeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
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
	// TODO: �ڴ���������������
	mouseState = mouseState == MOUSE_ZOOM_MOVE ? MOUSE_ZOOM_NONE : MOUSE_ZOOM_MOVE;
}


void COPPWMJExeView::OnUpdateZoomMove(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(mouseState == MOUSE_ZOOM_MOVE);
}


void COPPWMJExeView::OnZoomTrans()
{
	// TODO: �ڴ���������������
	mouseState = mouseState == MOUSE_ZOOM_TRANS ? MOUSE_ZOOM_NONE : MOUSE_ZOOM_TRANS;
}


void COPPWMJExeView::OnUpdateZoomTrans(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(mouseState == MOUSE_ZOOM_TRANS);
}




BOOL COPPWMJExeView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// �Ϲ����Ŵ���С����
	if (zDelta > 0) {
		this->wcRect.DeflateRect(wcRect.Width()*0.1, wcRect.Height()*0.1);
	}
	else if (zDelta < 0) {
		this->wcRect.InflateRect(wcRect.Width()*0.1, wcRect.Height()*0.1);
	}
	Invalidate();


	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

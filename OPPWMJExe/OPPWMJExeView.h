// OPPWMJExeView.h : interface of the COPPWMJExeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPPWMJEXEVIEW_H__779DF11B_DC94_41D4_BDD5_C1281AE35208__INCLUDED_)
#define AFX_OPPWMJEXEVIEW_H__779DF11B_DC94_41D4_BDD5_C1281AE35208__INCLUDED_

#include "GeoMap.h"	// Added by ClassView
#include "atltypes.h"
#include "afxwin.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MOUSE_ZOOM_NONE 0
#define MOUSE_ZOOM_IN 1
#define MOUSE_ZOOM_CLIP 2
#define MOUSE_ZOOM_MOVE 3
#define MOUSE_ZOOM_TRANS 4

class COPPWMJExeView : public CView
{
protected: // create from serialization only
	COPPWMJExeView();
	DECLARE_DYNCREATE(COPPWMJExeView)

// Attributes
public:
	COPPWMJExeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COPPWMJExeView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void readCHData(FILE *fp);
	void readCH1Data(FILE *fp);
	void readWHData(FILE *fp);

	CGeoMap *map;

	virtual ~COPPWMJExeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COPPWMJExeView)
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	// �ж�ͼ�Ƿ���أ��Ƿ���Ҫ����任
	bool isMapLoaded;
	// ��ȡͼ����Ϣ
	void readOption();
	afx_msg void OnZoomIn();
	afx_msg void OnUpdateZoomIn(CCmdUI *pCmdUI);
	afx_msg void OnZoomFull();
	afx_msg void OnFileNew();
	// ������ʾ�ľ�������
	CRect wcRect;
	// ������״̬
	int mouseState;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	// �������Ƿ���
	bool hasMouseLeftPressed;
	// ��갴������
	CPoint mouseDownPoint;
	// ����ͷ�����
	CPoint mouseUpPoint;
	// ��ȡע��
	void readAnotation();
	// �ϴ�����ƶ��¼��ĵ�
	CPoint mouseMovePoint;
	// ��ȡ���ӵ���������
	void readCFTData(FILE* fp);
	// ��ȡ�ü�����
	void readCPData(FILE * fp);
	afx_msg void OnZoomClip();
	afx_msg void OnUpdateZoomClip(CCmdUI *pCmdUI);
	// ����ƽ�Ƶ��ڴ��е�ͼƬ
	CBitmap bmp;
	// �ڴ�CDC
	CDC *dcMen;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnZoomMove();
	afx_msg void OnUpdateZoomMove(CCmdUI *pCmdUI);
	afx_msg void OnZoomTrans();
	afx_msg void OnUpdateZoomTrans(CCmdUI *pCmdUI);
	// ��ȡ��γ�ȱ�ʾ��MIF����
	void readMIFData(FILE * fp);
	// ʹ�õ�ͶӰ����
	CMapProjection * projection;
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // debug version in OPPWMJExeView.cpp
inline COPPWMJExeDoc* COPPWMJExeView::GetDocument()
   { return (COPPWMJExeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPPWMJEXEVIEW_H__779DF11B_DC94_41D4_BDD5_C1281AE35208__INCLUDED_)
